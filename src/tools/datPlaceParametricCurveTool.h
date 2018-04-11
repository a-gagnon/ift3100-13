//=======================================================================================
// datPlaceParametricCurveTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"
#include "../ui/datofxRadioButton.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datPlaceParametricCurveTool : datEditTool {

private:
    datParametricCurve::Type m_type;
    std::unique_ptr<datParametricCurve> m_transient;

    std::vector<ofPoint> m_controlPoints;

    ofxPanel m_panel;
    ofParameter<ofColor> m_paramLineColor;
    ofParameter<float> m_paramLineWidth;
    datofxRadioButton m_typeBezier;
    datofxRadioButton m_typeHermite;
    datofxRadioButton m_typeBSpline;
    datofxRadioButton m_typeCatmullRom;

private:
    void onLineColorChanged(ofColor& color) { GetRenderer().GetActiveDisplayParamsR().lineColor = color; updateStyle(); }
    void onLineWidthChanged(float& value) { GetRenderer().GetActiveDisplayParamsR().lineWidth = value; updateStyle(); }
    void updateTransient(datMouseEvent const* pMouseEvent = nullptr);
    void updateStyle();
    bool saveCurve(datMouseEvent const& ev);

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onRightMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onDraw() override;

public:
    datPlaceParametricCurveTool();
    virtual ~datPlaceParametricCurveTool();

    void SetType(datParametricCurve::Type type) { m_type = type; updateTransient(); }
};

END_DAT_NAMESPACE
