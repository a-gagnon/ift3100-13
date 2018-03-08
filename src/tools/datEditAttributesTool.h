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
    std::set<datGeometry*> m_geometries;

    ofxPanel m_panel;
    ofParameter<ofColor> m_paramLineColor;
    ofParameter<float> m_paramLineWidth;
    ofParameter<ofColor> m_paramFillColor;

private:
    void onLineColorChanged(ofColor& color);
    void onLineWidthChanged(float& value);
    void onFillColorChanged(ofColor& color);

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    virtual void onDraw() override;

public:
    datEditAttributesTool();
    virtual ~datEditAttributesTool();
};

END_DAT_NAMESPACE
