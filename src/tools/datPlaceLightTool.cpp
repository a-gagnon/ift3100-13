//=======================================================================================
// datPlaceLightTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceLightTool.h"

USING_DAT_NAMESPACE

namespace {

    static datPlaceLightTool* s_tool = nullptr;
    void onPointLightSelected() { s_tool->GetLightR().setPointLight(); s_tool->updateTransient(); }
    void onSpotLightSelected() { s_tool->GetLightR().setSpotlight(); s_tool->updateTransient(); }
    void onAreaLightSelected() { s_tool->GetLightR().setAreaLight(20, 50); s_tool->updateTransient(); }
    void onDirectionalLightSelected() { s_tool->GetLightR().setDirectional(); s_tool->updateTransient(); }

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
    m_light.enable();
}


datPlaceLightTool::~datPlaceLightTool() {
    s_tool = nullptr;
}


void datPlaceLightTool::onStartTool() {
    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_colorAmbient.set(datLocalization::PlaceLightTool_ColorAmbient(), m_light.getAmbientColor(), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.add(m_colorDiffuse.set(datLocalization::PlaceLightTool_ColorDiffuse(), m_light.getDiffuseColor(), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.add(m_colorSpecular.set(datLocalization::PlaceLightTool_ColorSpecular(), m_light.getSpecularColor(), ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.add(m_radioPointLight.setup(datLocalization::PlaceLightTool_Point()));
    m_panel.add(m_radioSpotLight.setup(datLocalization::PlaceLightTool_Spot()));
    m_panel.add(m_radioAreaLight.setup(datLocalization::PlaceLightTool_Area()));
    m_panel.add(m_radioDirectionalLight.setup(datLocalization::PlaceLightTool_Directional()));
    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);

    ofNotifyEvent(selectTypeEvent, m_radioPointLight);

    m_colorAmbient.addListener(this, &datPlaceLightTool::setColorAmbient);
    m_colorDiffuse.addListener(this, &datPlaceLightTool::setColorDiffuse);
    m_colorSpecular.addListener(this, &datPlaceLightTool::setColorSpecular);
}


void datPlaceLightTool::onExitTool() {
    m_colorAmbient.removeListener(this, &datPlaceLightTool::setColorAmbient);
    m_colorDiffuse.removeListener(this, &datPlaceLightTool::setColorDiffuse);
    m_colorSpecular .removeListener(this, &datPlaceLightTool::setColorSpecular);


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
}
