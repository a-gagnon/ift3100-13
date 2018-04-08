//=======================================================================================
// datRenderer.cpp
// IFT3100-13
//=======================================================================================
#include "datRenderer.h"

USING_DAT_NAMESPACE


datBoundingBox datViewport::GetWorldBox(ofPoint viewMin, ofPoint viewMax) const {
    
    viewMin.z = 1.0;
    viewMax.z = 1.0;

    ofPoint pFarLeft = camera.screenToWorld(viewMin, rect);
    ofPoint pFarRight = camera.screenToWorld(viewMax, rect);

    float scale = std::abs(camera.getFarClip()) + std::abs(camera.getNearClip());
    ofPoint pCloseLeft = scale * camera.getZAxis() + pFarLeft;
    ofPoint pCloseRight = scale * camera.getZAxis() + pFarRight;

    datBoundingBox box;
    box.Extend(pFarLeft);
    box.Extend(pFarRight);
    box.Extend(pCloseLeft);
    box.Extend(pCloseRight);
    return box;
}


datBoundingBox datViewport::GetWorldBox() const {
    
    ofPoint pFarLeft = camera.cameraToWorld(ofVec3f(-1, -1, 1), rect);
    ofPoint pFarRight = camera.cameraToWorld(ofVec3f(1, 1, 1), rect);

    float scale = std::abs(camera.getFarClip()) + std::abs(camera.getNearClip());
    ofPoint pCloseLeft = scale * camera.getZAxis() + pFarLeft;
    ofPoint pCloseRight = scale * camera.getZAxis() + pFarRight;

    datBoundingBox box;
    box.Extend(pFarLeft);
    box.Extend(pFarRight);
    box.Extend(pCloseLeft);
    box.Extend(pCloseRight);
    return box;
}



datRenderer::datRenderer(datScene& scene) :
    m_scene(scene),
    m_activeCursorType(CursorType::Normal),
    m_drawBoundingBox(false),
    m_drawSelectedInHilite(true) {

    m_activeDisplayParams.fillColor = ofColor(120, 120, 120, 255);
    m_activeDisplayParams.lineColor = ofColor(160, 160, 160, 255);
    m_activeDisplayParams.lineWidth = 4.0f;

    InitMaterials();
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


void datRenderer::InitMaterials() {

    m_material1.setAmbientColor(ofColor(0.f, 0.f, 0.f));
    m_material1.setDiffuseColor(ofColor(0.f, 255.f, 0.f));
    m_material1.setSpecularColor(ofColor(255.f, 255.f, 0.f));
    m_material1.setShininess(10);

    m_material2.setAmbientColor(ofColor(0.f, 0.f, 0.f));
    m_material2.setDiffuseColor(ofColor(255.f, 0.f, 0.f));
    m_material2.setSpecularColor(ofColor(255.f, 0.f, 255.f));
    m_material2.setShininess(24);

    m_material3.setAmbientColor(ofColor(0.0, 225.f, 0.0));
    m_material3.setEmissiveColor(ofColor(0.0, 225.f, 0.0));
    m_material3.setShininess(60);
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


void datRenderer::DrawBoundingBox(datElement const& element) const {

    datBoundingBox box = element.CalculateBoundingBox();
    const ofPoint center = box.GetCenter();

    ofSetColor(ofColor::darkMagenta);
    ofSetLineWidth(4.0);
    ofDrawBox(center.x, center.y, center.z, box.GetXLength(), box.GetYLength(), box.GetZLength());

    ofSetColor(ofColor::white);
    ofSetLineWidth(1.0);
    ofDrawBox(center.x, center.y, center.z, box.GetXLength(), box.GetYLength(), box.GetZLength());
}


void datRenderer::RenderElement(datElement const& element, bool useDisplayParams) {

    ISupportMaterial const* pMaterialSupport = element.ToSupportMaterial();

    datDisplayParams const* pDisplayParams = (nullptr == element.ToSupportDisplayParams()) ?
        nullptr : &element.ToSupportDisplayParams()->GetDisplayParams();

    if (nullptr != pMaterialSupport && pMaterialSupport->GetUseMaterial()) {
        pMaterialSupport->GetMaterial().begin();
    }

    if (useDisplayParams && nullptr != pDisplayParams) {
        ofPushStyle();
        ofSetLineWidth(pDisplayParams->lineWidth);

        // Do a first draw call with fill enabled
        if (pDisplayParams->isFilled) {
            ofSetColor(pDisplayParams->fillColor);
            ofFill();
            element.Draw();
        }
        ofNoFill();
        ofSetColor(pDisplayParams->lineColor);
    }

    // Draw element
    element.Draw();

    if (useDisplayParams && nullptr != pDisplayParams) {
        ofPopStyle();
    }

    if (nullptr != pMaterialSupport && pMaterialSupport->GetUseMaterial()) {
        pMaterialSupport->GetMaterial().end();
    }
}

void datRenderer::Render() {

    ofPushStyle();
    ofSetColor(m_activeDisplayParams.lineColor);
    ofSetLineWidth(m_activeDisplayParams.lineWidth);

    ofEnableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableLighting();

    for (auto& vp : m_viewports) {

        datBoundingBox bbox = vp.GetWorldBox();

        std::vector<datElement const*> elements = m_scene.QueryElements(bbox, false);
        std::vector<datElement const*> selectedElements;
        std::vector<datElement const*> bboxElements;

        vp.camera.begin(vp.rect);

        // Draw node at (0, 0, 0)
        ofNode node;
        node.setGlobalPosition(ofPoint(0, 0, 0));
        node.draw();

        // Draw cameras
        for (auto const& vp : m_viewports)
            vp.camera.draw();

        for (auto const& element : elements) {

            // Should not draw this element
            if (IsNeverDraw(element->GetId()))
                continue;

            RenderElement(*element, true);

            if (m_drawSelectedInHilite && m_scene.IsSelected(element->GetId()))
                selectedElements.push_back(element);

            if (m_drawBoundingBox)
                bboxElements.push_back(element);
        }

        // Draw transient graphics
        for (auto const& pTransient : m_transients) {
            RenderElement(*pTransient, true);
        }

        // Redraw elements that are selected. Just put their outline in a different color
        if (!selectedElements.empty()) {

            ofPushStyle();
            ofSetColor(ofColor::yellow);
            ofFill();
            ofSetLineWidth(20.0);

            ofPushMatrix();
            ofTranslate(vp.camera.getZAxis() * 0.5); // Push geometry towards the eye a bit

            for (auto const& element : selectedElements) {
                RenderElement(*element, false);
            }

            ofPopMatrix();
            ofPopStyle();
        }

        // Draw bounding box
        if (!bboxElements.empty()) {
            ofPushStyle();
            ofNoFill();

            for (auto const& element : bboxElements)
                DrawBoundingBox(*element);

            ofPopStyle();
        }

        vp.camera.end();
    }

    ofDisableLighting();
    ofDisableBlendMode();
    ofDisableDepthTest();

    // Draw viewport outline
    ofNoFill();
    ofSetColor(ofColor::black);
    ofSetLineWidth(10.0);

    for (auto const& vp : m_viewports) {
        ofDrawRectangle(vp.rect);
    }

    DrawCursorType();

    ofPopStyle();
}
