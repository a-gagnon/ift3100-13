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

    AddViewport();
    ResizeViewports();
}


datRenderer::~datRenderer() {

}


size_t datRenderer::GetViewportIndex(ofPoint const& viewPoint) const {

    for (size_t i = 0; i < m_viewports.size(); ++i) {

        ofRectangle const& rect = m_viewports[i].rect;
        const ofPoint low = rect.getTopLeft();
        const ofPoint high = rect.getBottomRight();

        // ofRectangle::inside ignores the case where we're equal
        if (low.x <= viewPoint.x && viewPoint.x <= high.x &&
            low.y <= viewPoint.y && viewPoint.y <= high.y)
            return i;
    }

    assert(false);
    return 0;
}


void datRenderer::SetUseTwoViewports(bool yesNo) {

    if (yesNo && 2 != m_viewports.size()) {
        AddViewport();
    }
    else if (!yesNo && 1 != m_viewports.size()) {
        m_viewports.pop_back();
    }

    ResizeViewports();
}


void datRenderer::ResizeViewports() {

    int vpWidth = ofGetWidth() / m_viewports.size();
    int vpHeight = ofGetHeight();

    for (size_t i = 0; i < m_viewports.size(); ++i) {

        datViewport& vp = m_viewports[i];
        vp.rect.set(i * vpWidth, 0, vpWidth, vpHeight);
    }

    ofRectangle& lastRect = m_viewports.back().rect;
    lastRect.setWidth(vpWidth + 1);
}


void datRenderer::SetUseOrthoCamera(bool yesNo) {

    for (auto& vp : m_viewports) {

        if (yesNo)
            vp.camera.enableOrtho();
        else
            vp.camera.disableOrtho();
    }
}


void datRenderer::AddViewport() {
    
    datViewport vp;

    if (!m_viewports.empty()) {
        // Copy settings from first viewport
        vp = m_viewports.front();
    }
    else {
        vp.camera.setPosition(ofPoint(0, 0, 500.0));
        vp.camera.lookAt(ofPoint(0, 0, 0));
        vp.camera.setOrientation(ofQuaternion());
        vp.camera.disableMouseInput();
        vp.camera.setVFlip(false);
    }

    m_viewports.push_back(vp);
}


void datRenderer::DrawCursorType() const {

    if (CursorType::Normal == m_activeCursorType) {
        ofShowCursor();
        return;
    }

    ofHideCursor();
    ofNoFill();
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


void datRenderer::Render() {

    ofEnableDepthTest();

    for (auto& vp : m_viewports) {

        std::vector<datGeometry const*> geometries = m_scene.QueryGeometries();
        std::vector<datGeometry const*> selectedGeometries;
        std::vector<datGeometry const*> bBoxGeometries;

        vp.camera.begin(vp.rect);

        for (auto const& geometry : geometries) {

            if (IsNeverDraw(geometry->GetId()))
                continue;

            geometry->drawWithDisplayParams();

            if (m_drawSelectedInHilite && m_scene.IsSelected(geometry->GetId()))
                selectedGeometries.push_back(geometry);

            if (m_drawBoundingBox)
                bBoxGeometries.push_back(geometry);
        }

        // Redraw elements that are selected. Just put their outline in a different color
        if (!selectedGeometries.empty()) {
            ofSetColor(ofColor::darkBlue);
            ofNoFill();
            ofSetLineWidth(20.0);

            for (auto const& geometry : selectedGeometries) {
                geometry->draw();
            }
        }

        // Draw bounding box
        if (!bBoxGeometries.empty()) {
            for (auto const& geometry : bBoxGeometries)
                DrawBoundingBox(*geometry);
        }

        // Draw transient graphics
        for (auto const& pTransient : m_transients) {
            pTransient->drawWithDisplayParams();
        }

        vp.camera.end();
    }

    ofDisableDepthTest();

    ofNoFill();
    ofSetColor(ofColor::black);
    ofSetLineWidth(10.0);

    for (auto const& vp : m_viewports) {
        ofDrawRectangle(vp.rect);
    }


    DrawCursorType();
}
