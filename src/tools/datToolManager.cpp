//=======================================================================================
// datToolManager.cpp
// IFT3100-13
//=======================================================================================
#include "datToolManager.h"
#include "../app/datApplication.h"

USING_DAT_NAMESPACE

//=======================================================================================
void datViewTool::_ExitTool() {
    datApplication::GetApp().GetToolManager().ExitViewTool();
}

//=======================================================================================
void datEditTool::_ExitTool() {
    datApplication::GetApp().GetToolManager().ExitEditTool();
}


datToolManager::datToolManager() :
    m_isStartingTool(false) {
}


datToolManager::~datToolManager() {

}


datViewTool* datToolManager::GetActiveViewTool() const {
    return m_viewTool.get();
}


datEditTool* datToolManager::GetActiveEditTool() const {
    return m_editTool.get();
}


datTool* datToolManager::GetToolForEvent() const {

    if (nullptr != m_viewTool)
        return m_viewTool.get();

    if (nullptr != m_editTool)
        return m_editTool.get();

    return nullptr;
}


void datToolManager::StartTool(datTool* pTool) {

    if (nullptr == pTool) {
        assert(false);
        return;
    }

    pTool->m_pRenderer = &datApplication::GetApp().GetRenderer();

    if (auto pEditTool = pTool->getAsEditTool()) {

        m_isStartingTool = true;
        ExitEditTool();
        m_editTool.reset(pEditTool);
        m_editTool->onStartTool();
        ofNotifyEvent(m_onEditToolStartedEvent, *m_editTool);
        m_isStartingTool = false;
    }
    else if (auto pViewTool = pTool->getAsViewTool()) {

        m_isStartingTool = true;
        ExitViewTool();
        m_viewTool.reset(pViewTool);
        m_viewTool->onStartTool();
        ofNotifyEvent(m_onViewToolStartedEvent, *m_viewTool);
        m_isStartingTool = false;
    }
}


void datToolManager::ExitViewTool() {

    if (nullptr != m_viewTool) {
        m_viewTool->onExitTool();
        m_viewTool.reset();
    }
}


void datToolManager::ExitEditTool() {

    if (nullptr != m_editTool) {
        m_editTool->onExitTool();
        m_editTool.reset();
    }

    if (!m_isStartingTool)
        ofNotifyEvent(m_onSupplyEditToolEvent);
}


bool datToolManager::SendMouseEvent(datMouseEvent ev) const {

    datTool* pTool = GetToolForEvent();
    if (nullptr == pTool)
        return false;

    if (ofMouseEventArgs::Type::Pressed == ev.type) {

        if (OF_MOUSE_BUTTON_LEFT == ev.button) {
            pTool->onLeftMouseButtonDown(ev);
            return true;
        }
        else if (OF_MOUSE_BUTTON_RIGHT == ev.button) {
            pTool->onRightMouseButtonDown(ev);
            return true;
        }
    }
    else if (ofMouseEventArgs::Type::Released == ev.type) {

        if (OF_MOUSE_BUTTON_LEFT == ev.button) {
            pTool->onLeftMouseButtonUp(ev);
            return true;
        }
        else if (OF_MOUSE_BUTTON_RIGHT == ev.button) {
            pTool->onRightMouseButtonUp(ev);
            return true;
        }
    }
    else if (ofMouseEventArgs::Type::Moved == ev.type || ofMouseEventArgs::Type::Dragged == ev.type) {

        pTool->onMouseMotion(ev);
        return true;
    }

    return false;
}


bool datToolManager::SendKeyEvent(ofKeyEventArgs const& ev) const {

    datTool* pTool = GetToolForEvent();

    if (nullptr != pTool && ofKeyEventArgs::Type::Pressed == ev.type) {
        pTool->onKeyPressed(ev);
        return true;
    }

    return false;
}


void datToolManager::DoDraw() {

    if (nullptr != m_editTool) {
        m_editTool->onDraw();
    }

    if (nullptr != m_viewTool) {
        m_viewTool->onDraw();
    }
}

