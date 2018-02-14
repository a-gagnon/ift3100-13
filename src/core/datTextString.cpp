//=======================================================================================
// datTextString.cpp
// IFT3100-13
//=======================================================================================
#include "datTextString.h"

USING_DAT_NAMESPACE

datTextString::datTextString(ofTrueTypeFont const& trueTypeFont, std::string const& text, ofVec2f const& position) :
    m_trueTypeFont(trueTypeFont), m_text(text), m_position(position) {
    assert(m_trueTypeFont.isLoaded());
}


datTextString::~datTextString() {

}


void datTextString::draw() const {
    m_trueTypeFont.drawString(m_text, m_position.x, m_position.y);
}
