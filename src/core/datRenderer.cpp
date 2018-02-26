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
    m_activeDrawColor(120, 120, 120, 255),
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

    ofVec2f coords;
    coords.x = ofGetMouseX();
    coords.y = ofGetMouseY();

    switch (m_activeCursorType) {

        case CursorType::Circle:
            ofDrawCircle(coords.x, coords.y, 10);
            break;

        case CursorType::X:
            ofSetLineWidth(3);
            ofDrawLine(coords.x + 8, coords.y + 8, coords.x - 8, coords.y - 8);
            ofDrawLine(coords.x - 8, coords.y + 8, coords.x + 8, coords.y - 8);
            break;

        case CursorType::Cross:
            ofDrawLine(coords.x, coords.y + 8, coords.x, coords.y - 8);
            ofDrawLine(coords.x - 8, coords.y, coords.x + 8, coords.y);
            break;

        case CursorType::Triangle:
            ofDrawTriangle(coords.x, coords.y, coords.x - 8,
                coords.y + 15, coords.x + 8, coords.y + 15);
            break;
    }
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
