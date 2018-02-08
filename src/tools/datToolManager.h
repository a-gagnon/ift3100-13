//=======================================================================================
// datToolManager.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datToolManager : NonCopyableClass {

private:
    std::unique_ptr<datTool> m_editTool;

public:
    datToolManager();
    ~datToolManager();

    datTool* GetActiveEditTool();

    // Starts the tool
    // @remarks takes ownership with a unique_ptr
    void StartTool(datTool* pTool);

    // Sends the mouse event to the active tool (if any)
    // @remarks returns true if the event is handled by the tool
    bool SendMouseEvent(ofMouseEventArgs const& ev) const;

    // Sends the keyboard event to the active tool (if any)
    // @remarks returns true if the vent is handled by the tool
    bool SendKeyEvent(ofKeyEventArgs const& ev) const;

    // Calls the active tool to draw, if any
    void DoDraw();
};

END_DAT_NAMESPACE
