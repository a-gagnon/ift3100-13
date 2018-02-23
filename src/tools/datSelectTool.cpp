//=======================================================================================
// datSelectTool.cpp
// IFT3100-13
//=======================================================================================
#include "datSelectTool.h"

USING_DAT_NAMESPACE

datSelectTool::datSelectTool() :
    m_isMouseDrag(false),
    m_hasFirstPoint(false),
    m_color(ofColor::dodgerBlue) {

}


datSelectTool::~datSelectTool() {

}


void datSelectTool::selectObjectsAndClearState() {

    //&&AG needswork select geometries using m_rectangle and m_mode
    m_isMouseDrag = false;
    m_hasFirstPoint = false;
}


void datSelectTool::updateRectangle(datMouseEvent const& ev) {

    assert(m_hasFirstPoint);
    m_rectangle.x = std::min(m_downPoint.x, ev.x);
    m_rectangle.y = std::min(m_downPoint.y, ev.y);
    m_rectangle.width = std::abs(m_downPoint.x - ev.x);
    m_rectangle.height = std::abs(m_downPoint.y - ev.y);
}


void datSelectTool::updateSelectionMode(datMouseEvent const& ev) {

    assert(m_hasFirstPoint);
    m_mode = (m_downPoint.x > ev.x && m_downPoint.y > ev.y) ? SelectionMode::Crossing : SelectionMode::Window;
}


void datSelectTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (m_hasFirstPoint) {

        updateRectangle(ev);
        updateSelectionMode(ev);
        selectObjectsAndClearState();
        return;
    }

    m_downPoint = ev;
    m_hasFirstPoint = true;
}


void datSelectTool::onLeftMouseButtonUp(datMouseEvent const& ev) {

    if (m_hasFirstPoint && m_isMouseDrag) {

        updateRectangle(ev);
        updateSelectionMode(ev);
        selectObjectsAndClearState();
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

    const datRenderer::CursorType activeCursorType = datRenderer::GetActiveRenderer().GetActiveCursorType();
    datRenderer::CursorType cursorType = activeCursorType;

    const char key = static_cast<char>(ev.key);
    switch (key) {
    case '1':
        cursorType = datRenderer::CursorType::Normal;
        break;
    case '2':
        cursorType = datRenderer::CursorType::Circle;
        break;
    case '3':
        cursorType = datRenderer::CursorType::X;
        break;
    case '4':
        cursorType = datRenderer::CursorType::Cross;
        break;
    case '5':
        cursorType = datRenderer::CursorType::Triangle;
        break;
    default:
        break;
    }

    if (cursorType != activeCursorType) {
        datRenderer::GetActiveRenderer().SetActiveCursorType(cursorType);
    }

}


void datSelectTool::onDraw() {

    if (m_hasFirstPoint && datEpsilon < m_rectangle.getArea()) {

        ofSetColor(m_color);
        ofNoFill();
        ofDrawRectangle(m_rectangle);
        ofFill();
    }
}
