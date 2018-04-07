//=======================================================================================
// datPlaceLightTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"
#include "../ui/datofxRadioButton.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datPlaceLightTool : datEditTool {

private:
    std::unique_ptr<datLight> m_transient;

    ofPoint m_position;
    ofLight m_light;
    bool m_createdLight;

    ofxPanel m_panel;
    datofxRadioButton m_radioPointLight;
    datofxRadioButton m_radioSpotLight;
    datofxRadioButton m_radioAreaLight;
    datofxRadioButton m_radioDirectionalLight;
    ofParameter<ofColor> m_colorAmbient;
    ofParameter<ofColor> m_colorDiffuse;
    ofParameter<ofColor> m_colorSpecular;
    ofParameter<float> m_attenuationConstant;
    ofParameter<float> m_attenuationLinear;
    ofParameter<float> m_attenuationQuadratic;
    ofParameter<ofVec3f> m_direction;


    //Spot light
    ofxPanel m_panelSpot;
    ofParameter<float> m_spotCutOff; // angle between 0-90 degrees
    ofParameter<float> m_spotConcentration; // range between 0-120
    
    // Area light
    ofxPanel m_panelArea;
    ofParameter<float> m_areaWidth;
    ofParameter<float> m_areaHeight;


private:
    void setColorAmbient(ofColor& color) { m_light.setAmbientColor(color); updateTransient(); }
    void setColorDiffuse(ofColor& color) { m_light.setDiffuseColor(color); updateTransient(); }
    void setColorSpecular(ofColor& color) { m_light.setSpecularColor(color); updateTransient(); }
    void setAttenuation(float&) { m_light.setAttenuation(m_attenuationConstant, m_attenuationLinear, m_attenuationQuadratic); updateTransient(); }
    void setSpotCutoff(float& value) { m_light.setSpotlightCutOff(value); updateTransient(); }
    void setSpotConcentration(float& value) { m_light.setSpotConcentration(value); updateTransient(); }
    void setDirection(ofPoint& point) { m_light.setOrientation(ofVec3f(point)); updateTransient(); }
    void setArea(float&) { m_light.setAreaLight(m_areaWidth, m_areaHeight); updateTransient(); }
    void updateTransient();

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onDraw() override;

public:
    datPlaceLightTool();
    virtual ~datPlaceLightTool();
    ofLight& GetLightR() { return m_light; }

    void onTypeSelected() { setDirection(ofPoint(m_direction)); updateTransient(); }

};

END_DAT_NAMESPACE
