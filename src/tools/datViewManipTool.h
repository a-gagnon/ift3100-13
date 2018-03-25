//=======================================================================================
// datViewManipTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datViewManipTool : datViewTool {

private:
    bool m_isShiftKey;
    ofPoint m_anchorPoint;
    datViewport m_initialState;
    datViewport* m_vp;

protected:
    virtual void onStartTool() override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onRightMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMiddleMouseButtonUp(datMouseEvent const& ev) override;

public:
    datViewManipTool(datMouseEvent const& ev);
    virtual ~datViewManipTool();
};

END_DAT_NAMESPACE
