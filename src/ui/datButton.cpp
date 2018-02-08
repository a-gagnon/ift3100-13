//=======================================================================================
// datButton.cpp
// IFT3100-13
//=======================================================================================
#include "datButton.h"

USING_DAT_NAMESPACE

datButtonStyle datButtonStyle::createForToolButton() {

    datButtonStyle style;
    style.buttonBackgroundColor = ofColor::lightSteelBlue;
    style.buttonBackgroundColorFocused = ofColor::steelBlue;
    style.tooltipBackgroundColor = ofColor::darkGrey;
    style.tooltipTextColor = ofColor::antiqueWhite;
    return style;
}


datButton::datButton(datButtonStyle const& style) : T_Super(),
    m_pCallbackFunction(nullptr),
    m_style(style) {

}


datButton::datButton(float x, float y, float width, float height, datButtonStyle const& style) :
    T_Super(x, y, width, height),
    m_pCallbackFunction(nullptr),
    m_style(style) {

}


datButton::~datButton() {

}


void datButton::onHover() {
    T_Super::onHover();
}


void datButton::onBlur() {
    T_Super::onBlur();
}


void datButton::onClick() {

    if (nullptr != m_pCallbackFunction) {
        m_pCallbackFunction();
    }
}


void datButton::onDraw() {

    const ofColor bgColor = HasFocus() ? m_style.buttonBackgroundColorFocused : m_style.buttonBackgroundColor;
    ofSetColor(bgColor);
    ofDrawRectangle(getX(), getY(), getWidth(), getHeight());

    if (nullptr != m_image)
        m_image->draw(getX(), getY(), getWidth(), getHeight());

    if (HasFocus() && !m_tooltip.empty()) {
        ofDrawBitmapStringHighlight(m_tooltip, getX() + getWidth() + 5, getY() + getHeight() + 5,
            m_style.tooltipBackgroundColor, m_style.tooltipTextColor);
    }
}




