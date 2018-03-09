//=======================================================================================
// datEditAttributesTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datEditAttributesTool : datEditTool {

private:
    std::vector<std::unique_ptr<datGeometry>> m_geometries;
	std::vector<datTransform> m_originalTransforms;

    ofxPanel m_panel;
	ofxGuiGroup m_styleGroup;
    ofParameter<ofColor> m_paramLineColor;
    ofParameter<float> m_paramLineWidth;
    ofParameter<ofColor> m_paramFillColor;

	ofxGuiGroup m_geometryGroup;
	ofParameter<float> m_paramScale;
	ofParameter<ofVec2f> m_paramTranslate;
	ofParameter<float> m_paramRotate;

private:
    void onLineColorChanged(ofColor& color);
    void onLineWidthChanged(float& value);
    void onFillColorChanged(ofColor& color);
	void onScaleChanged(float& value);
	void onRotationChanged(float& value);
	void onTranslationChanged(ofVec2f& value);

	void applyTransforms();

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    virtual void onDraw() override;

public:
    datEditAttributesTool();
    virtual ~datEditAttributesTool();
};

END_DAT_NAMESPACE
