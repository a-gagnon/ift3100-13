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

    SetPlaceholderText();
}


datPlaceTextTool::~datPlaceTextTool() {

}


void datPlaceTextTool::SetPlaceholderText() {
    m_text = datLocalization::PlaceTextTool_Placeholder();
}


bool datPlaceTextTool::IsPlaceholderText() const {
    return m_text == datLocalization::PlaceTextTool_Placeholder();
}


void datPlaceTextTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (!m_text.empty()) {
        datTextString textString(m_font, m_text, m_position);
        std::unique_ptr<datGeometry> geometry = datGeometry::Create(textString);
        geometry->SetColor(ofColor::red);
        datRenderer::GetRenderer().addGeometry(geometry);
    }

    SetPlaceholderText();
}


void datPlaceTextTool::onMouseMotion(datMouseEvent const& ev) {
    m_position = ev;
}


void datPlaceTextTool::onKeyPressed(ofKeyEventArgs const& ev) {

    if (IsPlaceholderText()) {
        m_text.clear();
    }

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
