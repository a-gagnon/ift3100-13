//=======================================================================================
// datRenderer.cpp
// IFT3100-13
//=======================================================================================
#include "datRenderer.h"

USING_DAT_NAMESPACE

datRenderer::datRenderer() : 
    m_activeCursorType(CursorType::Normal),
    m_displayBoundingBox(false) {

    m_activeDisplayParams.fillColor = ofColor(120, 120, 120, 255);
    m_activeDisplayParams.lineColor = ofColor(160, 160, 160, 255);
    m_activeDisplayParams.lineWidth = 4.0f;
}


datRenderer::~datRenderer() {

}


std::vector<datGeometry*> datRenderer::GetVisibleGeometries() const {

    std::vector<datGeometry*> visibleGeometries;

    for (auto& geometry : m_geometries) {
        visibleGeometries.push_back(geometry.get());
    }

    return std::move(visibleGeometries);
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

void datRenderer::DrawGeometry(datGeometry const& geometry) const {

    ofPushMatrix(); // save transform to top of stack
                    //ofLoadMatrix(node->GetWorldToNodeTransform());
    geometry.drawWithDisplayParams();

    ofPopMatrix(); // load transform from top of stack
}


void datRenderer::AddGeometry(std::unique_ptr<datGeometry>&& geometry) {
    m_geometries.push_back(std::move(geometry));
}


void datRenderer::Render() const {

    const std::vector<datGeometry*> visibleGeometries = GetVisibleGeometries();
    for (auto const& geometry : visibleGeometries) {
        DrawGeometry(*geometry);
    }
}
