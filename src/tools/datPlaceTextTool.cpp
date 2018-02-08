//=======================================================================================
// datPlaceTextTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceTextTool.h"

USING_DAT_NAMESPACE

datPlaceTextTool::datPlaceTextTool() {

    std::string fullPath = GetAssetsFolder();
    fullPath.append("arial.ttf");
    m_font.loadFont(fullPath, 24, true, true, true);
}


datPlaceTextTool::~datPlaceTextTool() {

}


void datPlaceTextTool::onRightMouseButtonDown(ofVec2f const& point) {

    if (!m_text.empty()) {
        datText text(m_font, m_text, point);
        datGeometry* pGeometry = new datGeometry(text);
        pGeometry->SetColor(ofColor::red);
        GeometryCache::GetCache().addGeometry(pGeometry);
    }

    m_text.clear();
}


void datPlaceTextTool::onKeyPressed(ofKeyEventArgs const& ev) {

    if (0x08 == ev.key && !m_text.empty()) {
        m_text = m_text.substr(0, m_text.size() - 1);
    }
    else {
        char key = static_cast<char>(ev.key);
        m_text += key;
    }
}


void datPlaceTextTool::onDraw() {

    GeometryCache::GetCache().drawCachedGeometries();

    if (!m_text.empty()) {
        ofSetColor(ofColor::orangeRed);
        m_font.drawStringAsShapes(m_text, 120, 120);
    }
}

