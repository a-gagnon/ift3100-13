//=======================================================================================
// datPlaceTextTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceTextTool.h"

USING_DAT_NAMESPACE

datPlaceTextTool::datPlaceTextTool() :
    m_position(0, 0, 0) {

    std::string fullPath = datUtilities::GetAssetsFolder();
    fullPath.append("arial.ttf");
    m_font.loadFont(fullPath, 24, true, true, true);
}


datPlaceTextTool::~datPlaceTextTool() {

}


void datPlaceTextTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (!m_text.empty()) {
        datText text(m_font, m_text, m_position);
        datGeometry* pGeometry = new datGeometry(text);
        pGeometry->SetColor(ofColor::red);
        GeometryCache::GetCache().addGeometry(pGeometry);
    }

    m_text.clear();
}


void datPlaceTextTool::onMouseMotion(datMouseEvent const& ev) {
    m_position = ev;
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

    if (!m_text.empty()) {
        ofSetColor(ofColor::orangeRed);
        m_font.drawStringAsShapes(m_text, m_position.x, m_position.y);
    }
}
