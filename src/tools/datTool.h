//=======================================================================================
// datTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../datDefinitions.h"
#include "../geometry/datGeometry.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Base class for tools
//=======================================================================================
struct datTool : NonCopyableClass {

friend struct datToolManager;

protected:
    virtual void onStartTool() {}
    virtual void onLeftMouseButtonDown(ofVec2f const& point) {}
    virtual void onRightMouseButtonDown(ofVec2f const& point) {}
    virtual void onMouseMotion(ofVec2f const& point) {}
    virtual void onKeyPressed(ofKeyEventArgs const& ev) {}
    virtual void onDraw() {}
    virtual void onExitTool() {}
    datTool() {}

public:
    virtual ~datTool() {}
};


struct datSelectTool : datTool {
    datSelectTool() {}
};

END_DAT_NAMESPACE
