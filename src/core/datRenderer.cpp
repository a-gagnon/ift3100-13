//=======================================================================================
// datRenderer.cpp
// IFT3100-13
//=======================================================================================
#include "datRenderer.h"

USING_DAT_NAMESPACE

datRenderer::datRenderer(datScene& scene) : 
    m_scene(scene),
    m_activeCursorType(CursorType::Normal),
    m_drawBoundingBox(false),
    m_drawSelectedInHilite(true) {

    m_activeDisplayParams.fillColor = ofColor(120, 120, 120, 255);
    m_activeDisplayParams.lineColor = ofColor(160, 160, 160, 255);
    m_activeDisplayParams.lineWidth = 4.0f;
}


datRenderer::~datRenderer() {

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

void datRenderer::DrawGeometry(datGeometry const& geometry, bool useDisplayParams) const {

    if (useDisplayParams)
        geometry.drawWithDisplayParams();
    else
        geometry.draw();
}


void datRenderer::DrawBoundingBox(datGeometry const& geometry) const {

    ofPushMatrix();
    ofMultMatrix(geometry.GetTransform());

    datBoundingBox const& box = geometry.GetBoundingBox();
    const ofPoint center = box.GetCenter();

    ofSetColor(ofColor::darkMagenta);
    ofSetLineWidth(4.0);
    ofDrawBox(center.x, center.y, center.z, box.GetXLength(), box.GetYLength(), box.GetZLength());

    ofSetColor(ofColor::white);
    ofSetLineWidth(1.0);
    ofDrawBox(center.x, center.y, center.z, box.GetXLength(), box.GetYLength(), box.GetZLength());

    ofPopMatrix();
}


void datRenderer::Render() const {

    std::vector<datGeometry const*> geometries = m_scene.QueryGeometries();
    std::vector<datGeometry const*> selectedGeometries;

    for (auto const& geometry : geometries) {

        if (IsNeverDraw(geometry->GetId()))
            continue;

        geometry->drawWithDisplayParams();

        if (m_scene.IsSelected(geometry->GetId()))
            selectedGeometries.push_back(geometry);

        if (m_drawBoundingBox)
            DrawBoundingBox(*geometry);
    }


    if (m_drawSelectedInHilite && !selectedGeometries.empty()) {
        // Redraw elements that are selected. Just put their outline in a different color
        ofSetColor(ofColor::darkBlue);
        ofNoFill();

        for (auto const& geometry : selectedGeometries) {
            DrawGeometry(*geometry, false/*useDisplayParams*/);
        }
    }
}
