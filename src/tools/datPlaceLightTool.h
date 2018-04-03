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
    std::unique_ptr<datGeometry> m_transient;

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

private:
    void setColorAmbient(ofColor& color) { m_light.setAmbientColor(color); updateTransient(); }
    void setColorDiffuse(ofColor& color) { m_light.setDiffuseColor(color); updateTransient(); }
    void setColorSpecular(ofColor& color) { m_light.setSpecularColor(color); updateTransient(); }

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
    void updateTransient();
};

END_DAT_NAMESPACE
