//=======================================================================================
// datRenderer.cpp
// IFT3100-13
//=======================================================================================
#include "datRenderer.h"

USING_DAT_NAMESPACE

datRenderer::datRenderer() : 
    m_activeCursorType(CursorType::Normal),
    m_displayBoundingBox(false),
    m_drawSelectedInHilite(true) {

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

void datRenderer::DrawGeometry(datGeometry const& geometry, bool useDisplayParams) const {

    ofPushMatrix(); // save transform to top of stack
                    //ofLoadMatrix(node->GetWorldToNodeTransform());

    if (useDisplayParams)
        geometry.drawWithDisplayParams();
    else
        geometry.draw();

    ofPopMatrix(); // load transform from top of stack
}


void datRenderer::DrawBoundingBox(datGeometry const& geometry) const {

    datBoundingBox const& box = geometry.GetBoundingBox();
    ofSetColor(ofColor::lightGray);
    ofSetLineWidth(2.0);

    static bool s_drawRect = true;
    if (s_drawRect)
        ofDrawRectangle(box.low, box.GetXLength(), box.GetYLength());
    else
        ofDrawBox(box.low.x, box.low.y, box.low.z, box.GetXLength(), box.GetYLength(), box.GetZLength());
}


namespace {
    void cloneInDest(std::vector<std::unique_ptr<datGeometry>>& result, std::vector<std::unique_ptr<datGeometry>> const& source) {

        result.clear();
        std::transform(source.begin(), source.end(), std::back_inserter(result), [](std::unique_ptr<datGeometry> const& ptr) { return ptr->Clone(); });
    }
};


void datRenderer::AddGeometry(std::unique_ptr<datGeometry>&& geometry) {
    m_geometries.push_back(std::move(geometry));
}


void datRenderer::RemoveGeometry(datGeometry* pGeometry) {

    for (size_t i = 0; i < m_geometries.size(); ++i) {

        if (pGeometry == m_geometries[i].get()) {
            m_selectionSet.RemoveFromSelection(pGeometry, false);
            m_geometries.erase(m_geometries.begin() + i);
        }
    }
}


std::vector<datGeometry*> datRenderer::QueryGeometries(datBoundingBox const& boundingBox) const {
    
    std::vector<datGeometry*> results;

    //&&AG this will probably need to take into account current transform and element transform at some point
    for (auto const& geometry : m_geometries) {

        if (boundingBox.HasAnyOverlapWith(geometry->GetBoundingBox())) {
            results.push_back(geometry.get());
        }
    }

    return results;
}


void datRenderer::Render() const {

    std::vector<datGeometry*> selectedGeometries;

    const std::vector<datGeometry*> visibleGeometries = GetVisibleGeometries();
    for (auto const& geometry : visibleGeometries) {

        if (m_selectionSet.IsSelected(geometry))
            selectedGeometries.push_back(geometry);

        DrawGeometry(*geometry);

        //ofNoFill();
        if (m_displayBoundingBox)
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
