//=======================================================================================
// datPlaceCoonsSurfaceTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Tool to place a model inside the scene
//=======================================================================================
struct datPlaceCoonsSurfaceTool : datEditTool {

private:
    std::unique_ptr<datPolyline> m_transient;

    ofxPanel m_panel;
    ofParameter<uint32_t> m_paramLengthXY; // Length along the x-axis of the curves
    ofParameter<uint32_t> m_paramWidthXY;  // Length along the y-axis of the curves

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onRightMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onDraw() override;

    void onLengthOrWidthChanged(uint32_t& value);
    void updateTransient(datMouseEvent const* pEvent = nullptr);

public:
    datPlaceCoonsSurfaceTool();
    virtual ~datPlaceCoonsSurfaceTool();
};

END_DAT_NAMESPACE
