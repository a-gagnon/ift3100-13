//=======================================================================================
// datView.cpp
// IFT3100-13
//=======================================================================================
#include "datView.h"

USING_DAT_NAMESPACE

datView::datView() :
    m_pParentView(nullptr),
    m_backgroundColor(ofColor(0, 0, 0, 0)),
    m_isVisible(true),
    m_isMouseInside(false) {
}


datView::datView(float x, float y, float width, float height) :
    T_Super(x, y, width, height),
    m_pParentView(nullptr),
    m_backgroundColor(ofColor(0, 0, 0, 0)),
    m_isVisible(true),
    m_isMouseInside(false) {
}


bool datView::onMouseMotion(datMouseEvent const& ev) {
    return false;
}


bool datView::onLeftMouseButtonDown(datMouseEvent const& ev) {
    return false;
}


bool datView::onLeftMouseButtonUp(datMouseEvent const& ev) {
    return false;
}


bool datView::onRightMouseButtonDown(datMouseEvent const& ev) {
    return false;
}


bool datView::onRightMouseButtonUp(datMouseEvent const& ev) {
    return false;
}


void datView::onHover() {

}


void datView::onBlur() {

}


void datView::onDraw() {

}


void datView::AddView(datView* pView) {

    if (nullptr != pView && nullptr == pView->GetParentView()) {
        pView->m_pParentView = this;
        m_views.push_back(std::unique_ptr<datView>(pView));
    }
}


void datView::RemoveView(datView* pView) {

    if (nullptr != pView && this == pView->GetParentView()) {

        for (int i = 0; i < m_views.size(); ++i) {

            if (m_views[i].get() == pView) {
                IViewRemovedListener::NotifyViewRemoved(*m_views[i]);
                m_views.erase(m_views.begin() + i);
                return;
            }
        }
    }
}


void datView::DropView() {
    assert(nullptr != m_pParentView);
    m_pParentView->RemoveView(this);
}


bool datView::IsVisible() const {

    // To be visible, parent must be visible too!
    return m_isVisible && (nullptr == m_pParentView || m_pParentView->IsVisible());
}


void datView::SetVisible(bool yesNo) {

    if (IsVisible() == yesNo)
        return;

    m_isVisible = yesNo;

    // Propagate to child views
    for (auto& view : m_views) {

        if (nullptr != view) {
            view->SetVisible(yesNo);
        }
    }
}


//=======================================================================================
static std::vector<IViewRemovedListener*> s_pListeners;

void IViewRemovedListener::AddListener(IViewRemovedListener* pListener) {
    assert(nullptr != pListener);
    s_pListeners.push_back(pListener);
}


void IViewRemovedListener::DropListener(IViewRemovedListener* pListener) {
    assert(nullptr != pListener);

    for (size_t i = 0; i < s_pListeners.size(); ++i){

        if (s_pListeners[i] == pListener) {
            s_pListeners.erase(s_pListeners.begin() + i);
            return;
        }
    }
}


void IViewRemovedListener::NotifyViewRemoved(datView& view) {

    for (auto const& pListener : s_pListeners) {
        pListener->_OnViewDropped(view);
    }
}
