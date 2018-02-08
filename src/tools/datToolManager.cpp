//=======================================================================================
// datToolManager.cpp
// IFT3100-13
//=======================================================================================
#include "datToolManager.h"

USING_DAT_NAMESPACE

datToolManager::datToolManager() {

}


datToolManager::~datToolManager() {

}


datTool* datToolManager::GetActiveEditTool() {
    return m_editTool.get();
}


void datToolManager::StartTool(datTool* pTool) {

    // Cleanup the current tool
    if (nullptr != m_editTool)
        m_editTool->onExitTool();

    // Assign a new tool (possibly nullptr)
    m_editTool.reset(pTool);

    // Notify the tool that it started
    if (nullptr != m_editTool)
        m_editTool->onStartTool();
}


bool datToolManager::SendMouseEvent(ofMouseEventArgs const& ev) const {

    if (nullptr == m_editTool)
        return false;

    if (ofMouseEventArgs::Type::Pressed == ev.type) {

        if (OF_MOUSE_BUTTON_LEFT == ev.button) {
            m_editTool->onLeftMouseButtonDown(ev);
            return true;
        }
        else if (OF_MOUSE_BUTTON_RIGHT == ev.button) {
            m_editTool->onRightMouseButtonDown(ev);
            return true;
        }
    }
    else if (ofMouseEventArgs::Type::Moved == ev.type) {

        m_editTool->onMouseMotion(ev);
        return true;
    }

    return false;
}


bool datToolManager::SendKeyEvent(ofKeyEventArgs const& ev) const {

    if (nullptr != m_editTool && ofKeyEventArgs::Type::Pressed == ev.type) {
        m_editTool->onKeyPressed(ev);
        return true;
    }

    return false;
}


void datToolManager::DoDraw() {

    if (nullptr != m_editTool)
        m_editTool->onDraw();
}

