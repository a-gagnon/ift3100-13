//=======================================================================================
// datRenderer.cpp
// IFT3100-13
//=======================================================================================
#include "datRenderer.h"

USING_DAT_NAMESPACE

//=======================================================================================
datRenderer::Entry::Entry(std::unique_ptr<datGeometry>& geometry) :
    m_geometry(geometry.release()) {
    m_worldToGeometry.makeTranslationMatrix({ 0, 0, 0 });
}


datRenderer::Entry::~Entry() {

}


//=======================================================================================
datRenderer* datRenderer::s_activeRenderer = nullptr;

datRenderer::datRenderer() : 
    m_activeDrawColor(255, 255, 255, 255),
    m_activeCursorType(CursorType::Normal) {
    assert(nullptr == s_activeRenderer);
    s_activeRenderer = this;
}


datRenderer::~datRenderer() {
    s_activeRenderer = nullptr;
}


datRenderer& datRenderer::GetActiveRenderer() {
    assert(nullptr != s_activeRenderer);
    return *s_activeRenderer;
}


std::vector<datRenderer::Entry*> datRenderer::GetVisibleEntries() const {

    std::vector<Entry*> visibleEntries;

    for (auto& entry : m_entries) {
        visibleEntries.push_back(entry.get());
    }

    return visibleEntries;
}


void datRenderer::DrawCursorType() const {

    if (CursorType::Normal == m_activeCursorType) {
        ofShowCursor();
        return;
    }

    ofHideCursor();
    ofSetColor(80);
    ofSetLineWidth(3);

    switch (m_activeCursorType) {

        case CursorType::Circle:
            ofDrawCircle(m_cursorCoordinates.x, m_cursorCoordinates.y, 10);
            break;

        case CursorType::X:
            ofSetLineWidth(3);
            ofDrawLine(m_cursorCoordinates.x + 8, m_cursorCoordinates.y + 8, m_cursorCoordinates.x - 8, m_cursorCoordinates.y - 8);
            ofDrawLine(m_cursorCoordinates.x - 8, m_cursorCoordinates.y + 8, m_cursorCoordinates.x + 8, m_cursorCoordinates.y - 8);
            break;

        case CursorType::Cross:
            ofDrawLine(m_cursorCoordinates.x, m_cursorCoordinates.y + 8, m_cursorCoordinates.x, m_cursorCoordinates.y - 8);
            ofDrawLine(m_cursorCoordinates.x - 8, m_cursorCoordinates.y, m_cursorCoordinates.x + 8, m_cursorCoordinates.y);
            break;

        case CursorType::Triangle:
            ofDrawTriangle(m_cursorCoordinates.x, m_cursorCoordinates.y, m_cursorCoordinates.x - 8,
                m_cursorCoordinates.y + 15, m_cursorCoordinates.x + 8, m_cursorCoordinates.y + 15);
            break;
    }
}


void datRenderer::GrabMouseEvent(datMouseEvent const& ev)
    {
    m_cursorCoordinates = ev;
    }


void datRenderer::AddGeometry(std::unique_ptr<datGeometry>& geometry) {

    std::unique_ptr<Entry> entry(new Entry(geometry));
    m_entries.push_back(std::move(entry));
}


void datRenderer::Render() const {

    const std::vector<Entry*> visibleEntries = GetVisibleEntries();
    for (auto const& entry : visibleEntries) {

        ofPushMatrix(); // save transform to top of stack
                        //ofLoadMatrix(node->GetWorldToNodeTransform());
        entry->GetGeometry().draw();

        ofPopMatrix(); // load transform from top of stack
    }
}
