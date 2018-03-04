//=======================================================================================
// datPlacePolylineTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datPlacePolylineTool : datEditTool {

private:
    ofPolyline m_polyline;

    ofxPanel m_panel;
    ofParameter<ofColor> m_paramLineColor;
    ofParameter<float> m_paramLineWidth;
    ofParameter<ofColor> m_paramFillColor;

private:
    void onLineColorChanged(ofColor& color) { GetRenderer().GetActiveDisplayParamsR().lineColor = color; }
    void onLineWidthChanged(float& value)   { GetRenderer().GetActiveDisplayParamsR().lineWidth = value; }
    void onFillColorChanged(ofColor& color) { GetRenderer().GetActiveDisplayParamsR().fillColor = color; }

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    void saveAndClearShape(bool closeShape);
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onRightMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onDraw() override;

public:
    datPlacePolylineTool();
    virtual ~datPlacePolylineTool();
};

END_DAT_NAMESPACE
