//=======================================================================================
// datToolManager.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datToolManager : datNonCopyableClass {

private:
    std::unique_ptr<datViewTool> m_viewTool;
    std::unique_ptr<datEditTool> m_editTool;
    ofEvent<datEditTool> m_onEditToolStartedEvent;
    ofEvent<datViewTool> m_onViewToolStartedEvent;
    ofEvent<void> m_onSupplyEditToolEvent;
    bool m_isStartingTool;

private:
    // Determines which tool should get events
    datTool* GetToolForEvent() const;

public:
    datToolManager();
    ~datToolManager();

    datViewTool* GetActiveViewTool() const;
    datEditTool* GetActiveEditTool() const;

    ofEvent<datEditTool>& GetOnEditToolStartedEvent() { return m_onEditToolStartedEvent; }
    ofEvent<datViewTool>& GetOnViewToolStartedEvent() { return m_onViewToolStartedEvent; }
    ofEvent<void>& GetOnSupplyEditToolEvent() { return m_onSupplyEditToolEvent; }

    // Starts the tool
    // @remarks takes ownership with a unique_ptr
    void StartTool(datTool* pTool);
    void ExitViewTool();
    void ExitEditTool();

    // Sends the mouse event to the active tool (if any)
    // @remarks returns true if the event is handled by the tool
    bool SendMouseEvent(datMouseEvent ev) const;

    // Sends the keyboard event to the active tool (if any)
    // @remarks returns true if the vent is handled by the tool
    bool SendKeyEvent(ofKeyEventArgs const& ev) const;

    // Calls the available tools to draw
    void DoDraw(datRenderer& renderer);
};

END_DAT_NAMESPACE
