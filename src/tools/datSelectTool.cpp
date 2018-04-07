//=======================================================================================
// datSelectTool.cpp
// IFT3100-13
//=======================================================================================
#include "datSelectTool.h"
#include "../app/datApplication.h"

USING_DAT_NAMESPACE

namespace {

    void setCursorType1() { datApplication::GetApp().GetRenderer().SetActiveCursorType(datRenderer::CursorType::Normal); }
    void setCursorType2() { datApplication::GetApp().GetRenderer().SetActiveCursorType(datRenderer::CursorType::Circle); }
    void setCursorType3() { datApplication::GetApp().GetRenderer().SetActiveCursorType(datRenderer::CursorType::X); }
    void setCursorType4() { datApplication::GetApp().GetRenderer().SetActiveCursorType(datRenderer::CursorType::Cross); }
    void setCursorType5() { datApplication::GetApp().GetRenderer().SetActiveCursorType(datRenderer::CursorType::Triangle); }
    ofEvent<ofxButton> selectCursorTypeEvent;
};

datSelectTool::datSelectTool() :
    m_isMouseDrag(false),
    m_hasFirstPoint(false),
    m_color(ofColor::dodgerBlue),
    m_cursorTypeRadio1(setCursorType1, selectCursorTypeEvent),
    m_cursorTypeRadio2(setCursorType2, selectCursorTypeEvent),
    m_cursorTypeRadio3(setCursorType3, selectCursorTypeEvent),
    m_cursorTypeRadio4(setCursorType4, selectCursorTypeEvent),
    m_cursorTypeRadio5(setCursorType5, selectCursorTypeEvent) {
}


datSelectTool::~datSelectTool() {

}


void datSelectTool::selectObjectsAndClearState(datMouseEvent const& ev) {

    m_isMouseDrag = false;
    m_hasFirstPoint = false;

    size_t viewportIdx = GetRenderer().GetViewportIndex(ev.GetViewPoint());
    datViewport& vp = GetRenderer().GetViewport(viewportIdx);

    datBoundingBox selectionBox = vp.GetWorldBox(m_downPoint, ev.GetViewPoint());

    datScene& scene = GetRenderer().GetScene();
    std::vector<datElement const*> elements = scene.QueryElements(selectionBox, (SelectionMode::Window == m_mode));

    std::set<datId> selectedIds;
    for (auto const& element : elements)
        selectedIds.insert(element->GetId());

    scene.SetSelection(selectedIds);
}


void datSelectTool::updateRectangle(datMouseEvent const& ev) {

    assert(m_hasFirstPoint);

    ofPoint viewPoint = ev.GetViewPoint();
    ofPoint vpOrigin = m_downPointRect.getTopLeft();
    ofPoint vpCorner = m_downPointRect.getBottomRight();

    viewPoint.x = CLAMP(viewPoint.x, vpOrigin.x, vpCorner.x);
    viewPoint.y = CLAMP(viewPoint.y, vpOrigin.y, vpCorner.y);

    m_rectangle.x = std::min(m_downPoint.x, viewPoint.x);
    m_rectangle.y = std::min(m_downPoint.y, viewPoint.y);
    m_rectangle.width = std::abs(m_downPoint.x - viewPoint.x);
    m_rectangle.height = std::abs(m_downPoint.y - viewPoint.y);
}


void datSelectTool::updateSelectionMode(datMouseEvent const& ev) {

    assert(m_hasFirstPoint);

    if (2 > std::abs(ev.GetViewPoint().x - m_downPoint.x) + std::abs(ev.GetViewPoint().y - m_downPoint.y)) {
        m_mode = SelectionMode::Hit;
    }
    else
        m_mode = (m_downPoint.x > ev.GetViewPoint().x && m_downPoint.y > ev.GetViewPoint().y) ? SelectionMode::Crossing : SelectionMode::Window;
}


void datSelectTool::onStartTool() {

    m_panel.setup("Tool settings", "");
    m_panel.add(m_cursorTypeRadio1.setup(datLocalization::SelectTool_CursorNormal()));
    m_panel.add(m_cursorTypeRadio2.setup(datLocalization::SelectTool_CursorCircle()));
    m_panel.add(m_cursorTypeRadio3.setup(datLocalization::SelectTool_CursorX()));
    m_panel.add(m_cursorTypeRadio4.setup(datLocalization::SelectTool_CursorCross()));
    m_panel.add(m_cursorTypeRadio5.setup(datLocalization::SelectTool_CursorTriangle()));
    m_panel.add(m_appBackgroundColor.set(datLocalization::SelectTool_BackgroundColor(),
        GetRenderer().GetBackgroundColor(), ofColor(0, 0, 0), ofColor(255, 255, 255)));

    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);

    m_appBackgroundColor.addListener(this, &datSelectTool::setBackgroundColor);

    const datRenderer::CursorType currentCursorType = GetRenderer().GetActiveCursorType();
    switch (currentCursorType) {
        case datRenderer::CursorType::Normal:
            ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio1);
            break;
        case datRenderer::CursorType::Circle:
            ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio2);
            break;
        case datRenderer::CursorType::X:
            ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio3);
            break;
        case datRenderer::CursorType::Cross:
            ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio4);
            break;
        case datRenderer::CursorType::Triangle:
            ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio5);
            break;
    }
}


void datSelectTool::onExitTool() {
    m_appBackgroundColor.removeListener(this, &datSelectTool::setBackgroundColor);
}


void datSelectTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (m_hasFirstPoint) {

        updateRectangle(ev);
        updateSelectionMode(ev);
        selectObjectsAndClearState(ev);
        return;
    }

    m_downPoint = ev.GetViewPoint();
    m_downPointRect = ev.GetViewport().rect;
    m_hasFirstPoint = true;
}


void datSelectTool::onLeftMouseButtonUp(datMouseEvent const& ev) {

    if (m_hasFirstPoint) {
        updateRectangle(ev);
        updateSelectionMode(ev);
        selectObjectsAndClearState(ev);
    }
}


void datSelectTool::onMouseMotion(datMouseEvent const& ev) {

    if (!m_isMouseDrag && ev.IsDrag()) {
        m_isMouseDrag = true;
    }

    if (m_hasFirstPoint) {
        updateRectangle(ev);
        updateSelectionMode(ev);
    }
}


void datSelectTool::onKeyPressed(ofKeyEventArgs const& ev) {

    const datRenderer::CursorType activeCursorType = GetRenderer().GetActiveCursorType();
    datRenderer::CursorType cursorType = activeCursorType;

    const char key = static_cast<char>(ev.key);
    switch (key) {
    case '1':
        ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio1);
        break;
    case '2':
        ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio2);
        break;
    case '3':
        ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio3);
        break;
    case '4':
        ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio4);
        break;
    case '5':
        ofNotifyEvent(selectCursorTypeEvent, m_cursorTypeRadio5);
        break;
    default:
        break;
    }

    if (cursorType != activeCursorType) {
        GetRenderer().SetActiveCursorType(cursorType);
    }

}


void datSelectTool::onDraw() {

    if (m_hasFirstPoint && datEpsilon < m_rectangle.getArea()) {

        if (SelectionMode::Window != m_mode) {
            ofFill();
            ofColor color = m_color;
            color.a = 128;
            ofSetColor(color);
            ofDrawRectangle(m_rectangle);
        }

        ofSetColor(m_color);
        ofNoFill();
        ofDrawRectangle(m_rectangle);
    }

    m_panel.draw();
}
