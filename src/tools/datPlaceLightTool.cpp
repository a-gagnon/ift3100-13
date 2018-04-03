//=======================================================================================
// datPlaceLightTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceLightTool.h"

USING_DAT_NAMESPACE

namespace {

    static datPlaceLightTool* s_tool = nullptr;
    void onPointLightSelected() { s_tool->GetLightR().setPointLight(); s_tool->onTypeSelected(); }
    void onSpotLightSelected() { s_tool->GetLightR().setSpotlight(); s_tool->onTypeSelected(); }
    void onAreaLightSelected() { s_tool->GetLightR().setAreaLight(20, 50);  s_tool->onTypeSelected(); }
    void onDirectionalLightSelected() { s_tool->GetLightR().setDirectional();  s_tool->onTypeSelected(); }

    ofEvent<ofxButton> selectTypeEvent;
}


datPlaceLightTool::datPlaceLightTool() :
    m_position(0, 0, 0),
    m_radioPointLight(onPointLightSelected, selectTypeEvent),
    m_radioSpotLight(onSpotLightSelected, selectTypeEvent),
    m_radioAreaLight(onAreaLightSelected, selectTypeEvent),
    m_radioDirectionalLight(onDirectionalLightSelected, selectTypeEvent),
    m_createdLight(false)
    {
    s_tool = this;
    m_light.setPointLight();
    m_light.setOrientation(ofVec3f(0, 0, 0));
    m_light.enable();

    m_areaWidth.set(50.0);
    m_areaHeight.set(50.0);
}


datPlaceLightTool::~datPlaceLightTool() {
    s_tool = nullptr;
}


void datPlaceLightTool::onStartTool() {
    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_colorAmbient.set(datLocalization::PlaceLightTool_ColorAmbient(), m_light.getAmbientColor(), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.add(m_colorDiffuse.set(datLocalization::PlaceLightTool_ColorDiffuse(), m_light.getDiffuseColor(), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.add(m_colorSpecular.set(datLocalization::PlaceLightTool_ColorSpecular(), m_light.getSpecularColor(), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.add(m_attenuationConstant.set(datLocalization::PlaceLightTool_AttenuationConstant(), m_light.getAttenuationConstant(), 0, 10.0));
    m_panel.add(m_attenuationLinear.set(datLocalization::PlaceLightTool_AttenuationLinear(), m_light.getAttenuationLinear(), 0, 0.1));
    m_panel.add(m_attenuationQuadratic.set(datLocalization::PlaceLightTool_AttenuationQuadratic(), m_light.getAttenuationQuadratic(), 0, 0.1));
    m_panel.add(m_direction.set(datLocalization::PlaceLightTool_Direction(), m_light.getOrientationEuler(), ofPoint(-90, -90, -90), ofPoint(90, 90, 90)));

    m_panel.add(m_radioPointLight.setup(datLocalization::PlaceLightTool_Point()));
    m_panel.add(m_radioSpotLight.setup(datLocalization::PlaceLightTool_Spot()));
    m_panel.add(m_radioAreaLight.setup(datLocalization::PlaceLightTool_Area()));
    m_panel.add(m_radioDirectionalLight.setup(datLocalization::PlaceLightTool_Directional()));
    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);

    m_panelSpot.setup("Spotlight parameters", "", 0.4 * ofGetWidth());
    m_panelSpot.add(m_spotCutOff.set(datLocalization::PlaceLightTool_SpotCutoff(), m_light.getSpotlightCutOff(), 0.0, 90.0));
    m_panelSpot.add(m_spotConcentration.set(datLocalization::PlaceLightTool_SpotConcentration(), m_light.getSpotConcentration(), 0.0, 120.0));


    m_panelArea.setup("Area parameters", "", 0.4 * ofGetWidth());
    m_panelArea.add(m_areaWidth.set(datLocalization::PlaceLightTool_Width(), m_areaWidth, 1.0, 100.0));
    m_panelArea.add(m_areaHeight.set(datLocalization::PlaceLightTool_Height(), m_areaHeight, 1.0, 100.0));



    ofNotifyEvent(selectTypeEvent, m_radioPointLight);

    m_colorAmbient.addListener(this, &datPlaceLightTool::setColorAmbient);
    m_colorDiffuse.addListener(this, &datPlaceLightTool::setColorDiffuse);
    m_colorSpecular.addListener(this, &datPlaceLightTool::setColorSpecular);
    m_attenuationConstant.addListener(this, &datPlaceLightTool::setAttenuation);
    m_attenuationLinear.addListener(this, &datPlaceLightTool::setAttenuation);
    m_attenuationQuadratic.addListener(this, &datPlaceLightTool::setAttenuation);
    m_spotCutOff.addListener(this, &datPlaceLightTool::setSpotCutoff);
    m_spotConcentration.addListener(this, &datPlaceLightTool::setSpotConcentration);
    m_direction.addListener(this, &datPlaceLightTool::setDirection);
    m_areaWidth.addListener(this, &datPlaceLightTool::setArea);
    m_areaHeight.addListener(this, &datPlaceLightTool::setArea);
}


void datPlaceLightTool::onExitTool() {
    m_colorAmbient.removeListener(this, &datPlaceLightTool::setColorAmbient);
    m_colorDiffuse.removeListener(this, &datPlaceLightTool::setColorDiffuse);
    m_colorSpecular.removeListener(this, &datPlaceLightTool::setColorSpecular);
    m_attenuationConstant.removeListener(this, &datPlaceLightTool::setAttenuation);
    m_attenuationLinear.removeListener(this, &datPlaceLightTool::setAttenuation);
    m_attenuationQuadratic.removeListener(this, &datPlaceLightTool::setAttenuation);
    m_spotCutOff.removeListener(this, &datPlaceLightTool::setSpotCutoff);
    m_spotConcentration.removeListener(this, &datPlaceLightTool::setSpotConcentration);
    m_direction.removeListener(this, &datPlaceLightTool::setDirection);
    m_areaWidth.removeListener(this, &datPlaceLightTool::setArea);
    m_areaHeight.removeListener(this, &datPlaceLightTool::setArea);


    if (!m_createdLight) {
        if (nullptr != m_transient)
            m_transient->GetAsLight().disable();

        m_light.disable();
    }

    GetRenderer().ClearTransients();
}

void datPlaceLightTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    m_light.setGlobalPosition(m_position);
    std::unique_ptr<datGeometry> geometry = datGeometry::Create(m_light);
    GetRenderer().GetScene().InsertGeometry(std::move(geometry));
    m_createdLight = true;
    _ExitTool();
}


void datPlaceLightTool::onMouseMotion(datMouseEvent const& ev) {
    m_position = ev.GetWorldPoint();
    m_light.setGlobalPosition(m_position);
    updateTransient();
}

void datPlaceLightTool::updateTransient() {

    if (nullptr == m_transient) {
        m_transient = datGeometry::Create(m_light);
        GetRenderer().AddTransient(m_transient.get());
    }

    m_transient->GetAsLight() = m_light;
}

void datPlaceLightTool::onDraw() {
    m_panel.draw();

    ofPoint pos = m_panel.getPosition();
    pos.y += (m_panel.getHeight() + 50.0);

    if (m_light.getIsAreaLight()) {
        m_panelArea.setPosition(pos);
        m_panelArea.draw();
    }
    else if (m_light.getIsSpotlight()) {
        m_panelSpot.setPosition(pos);
        m_panelSpot.draw();
    }
}
