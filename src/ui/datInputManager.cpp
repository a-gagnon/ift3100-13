//=======================================================================================
// datInputManager.cpp
// IFT3100-13
//=======================================================================================
#include "datInputManager.h"

USING_DAT_NAMESPACE

datInputManager::datInputManager() :
    m_focusedView(nullptr) {
    AddListeners();
}


datInputManager::~datInputManager() {
    RemoveListeners();
}


void datInputManager::AddListeners() {
    ofAddListener(ofEvents().draw, this, &datInputManager::OnDraw);
}


void datInputManager::RemoveListeners() {
    ofRemoveListener(ofEvents().draw, this, &datInputManager::OnDraw);
}


void datInputManager::OnDraw(ofEventArgs& ev) {

    for (auto const& view : m_views) {

        if (nullptr != view) {
            view->onDraw();
        }
    }
}


datInputView* datInputManager::FindHit(ofVec2f const& point) const {
    
    for (auto const& pView : m_views) {

        if (nullptr != pView && pView->IsPointInside(point)) {
            return pView.get();
        }
    }
    return nullptr;
}


bool datInputManager::SendMouseEvent(ofMouseEventArgs const& ev) {

    datInputView* pHit = FindHit(ev);

    // Invalid hit
    if (nullptr == pHit) {

        if (nullptr != m_focusedView) {
            m_focusedView->onBlur();
            m_focusedView = nullptr;
        }
        return false;
    }

    // Valid hit
    if (pHit != m_focusedView) {

        if (nullptr != m_focusedView) {
            m_focusedView->onBlur();
            m_focusedView = nullptr;
        }
        m_focusedView = pHit;
        m_focusedView->onHover();
    }

    if (ofMouseEventArgs::Type::Pressed == ev.type) {

        if (OF_MOUSE_BUTTON_LEFT == ev.button) {
            m_focusedView->onClick();
        }
    }

    return true;
}


void datInputManager::AddView(datInputView* pView) {
    
    if (nullptr == pView) {
        assert(0);
        return;
    }

    m_views.push_back(std::unique_ptr<datInputView>(pView));
}
