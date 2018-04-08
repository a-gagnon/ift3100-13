//=======================================================================================
// datEditAttributesTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"
#include "../ui/datofxRadioButton.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datEditAttributesTool : datEditTool {

private:
    std::vector<std::unique_ptr<datElement>> m_elements;
    std::vector<ofNode> m_originalTransforms;

    ofxPanel m_panel;
    ofxGuiGroup m_styleGroup;
    ofParameter<ofColor> m_paramLineColor;
    ofParameter<float> m_paramLineWidth;
    ofParameter<ofColor> m_paramFillColor;

    ofxGuiGroup m_geometryGroup;
    ofParameter<float> m_paramScale;
    ofParameter<ofVec3f> m_paramTranslate;
    ofParameter<float> m_paramRotate;

    ofxGuiGroup m_materialGroup;
    datofxRadioButton m_radioNoMaterial;
    datofxRadioButton m_radioMaterial1;
    datofxRadioButton m_radioMaterial2;
    datofxRadioButton m_radioMaterial3;


private:
    void onLineColorChanged(ofColor& color);
    void onLineWidthChanged(float& value);
    void onFillColorChanged(ofColor& color);
    void onScaleChanged(float& value);
    void onRotationChanged(float& value);
    void onTranslationChanged(ofVec3f& value);

    void applyTransforms();

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    virtual void onDraw() override;

public:
    datEditAttributesTool();
    virtual ~datEditAttributesTool();
    void applyMaterial(int value);
};

END_DAT_NAMESPACE
