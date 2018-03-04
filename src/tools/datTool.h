//=======================================================================================
// datTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../core/datCore.h"

BEGIN_DAT_NAMESPACE

struct datViewTool;
struct datEditTool;

//=======================================================================================
// Base class for tools
//=======================================================================================
struct datTool : datNonCopyableClass {

friend struct datToolManager;

protected:
    datRenderer* m_pRenderer; // Renderer is set by tool manager when tool starts

protected:
    virtual void onStartTool() {}
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) {}
    virtual void onLeftMouseButtonUp(datMouseEvent const& ev) {}
    virtual void onRightMouseButtonDown(datMouseEvent const& ev) {}
    virtual void onRightMouseButtonUp(datMouseEvent const& ev) {}
    virtual void onMouseMotion(datMouseEvent const& ev) {}
    virtual void onKeyPressed(ofKeyEventArgs const& ev) {}
    virtual void onDraw() {}
    virtual void onExitTool() {}
    virtual void _ExitTool() = 0;

    virtual datViewTool* getAsViewTool() { return nullptr; }
    virtual datEditTool* getAsEditTool() { return nullptr; }
    datRenderer& GetRenderer() const { assert(nullptr != m_pRenderer); return *m_pRenderer; }

    datTool() : m_pRenderer(nullptr) {}

public:
    virtual ~datTool() {}
};

//=======================================================================================
struct datViewTool : datTool {

protected:
    virtual datViewTool* getAsViewTool() override final { return this; }
    virtual void _ExitTool() override final {} //&&AG needswork
    datViewTool() {}

public:
    virtual ~datViewTool() {}
};

//=======================================================================================
struct datEditTool : datTool {

protected:
    virtual datEditTool* getAsEditTool() override final { return this; }
    virtual void _ExitTool() override final {} //&&AG needswork
    datEditTool() {}

public:
    virtual ~datEditTool() {}
};

END_DAT_NAMESPACE
