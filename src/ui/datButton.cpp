//=======================================================================================
// datButton.cpp
// IFT3100-13
//=======================================================================================
#include "datButton.h"

USING_DAT_NAMESPACE

datButtonStyle datButtonStyle::createForToolButton() {

    datButtonStyle style;
    style.buttonBackgroundColor = ofColor::lightSteelBlue;
    style.buttonBackgroundColorMouseInside = ofColor::steelBlue;
    style.buttonBackgroundColorToggled = ofColor::cadetBlue;
    style.tooltipBackgroundColor = ofColor::darkGrey;
    style.tooltipTextColor = ofColor::antiqueWhite;
    return style;
}


datButton::datButton(float x, float y, float width, float height, datButtonStyle const& style) :
    T_Super(x, y, width, height),
    m_pCallbackFunction(nullptr),
    m_isToggled(false),
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


bool datButton::onLeftMouseButtonDown(datMouseEvent const& ev) {

    PressButton();
    return true;
}


bool datButton::onLeftMouseButtonUp(datMouseEvent const& ev) {
    return IsMouseInside();
}


void datButton::onDraw() {

    ofFill();

    const ofColor color = DetermineDrawColor();

    ofSetColor(color);
    ofDrawRectangle(getX(), getY(), getWidth(), getHeight());

    if (nullptr != m_image)
        m_image->draw(getX(), getY(), getWidth(), getHeight());

    if (IsMouseInside() && !m_tooltip.empty()) {
        ofDrawBitmapStringHighlight(m_tooltip, getX() + getWidth() + 5, getY() + getHeight() + 5,
            m_style.tooltipBackgroundColor, m_style.tooltipTextColor);
    }
}


ofColor datButton::DetermineDrawColor() const {

    if (IsToggled())
        return m_style.buttonBackgroundColorToggled;

    if (IsMouseInside())
        return m_style.buttonBackgroundColorMouseInside;

    return m_style.buttonBackgroundColor;
}

void datButton::PressButton() {

    if (nullptr != m_pCallbackFunction)
        m_pCallbackFunction(*this);
}
