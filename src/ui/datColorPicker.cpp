//=======================================================================================
// datButton.cpp
// IFT3100-13
//=======================================================================================
#include "datColorPicker.h"

USING_DAT_NAMESPACE

datColorPicker::datColorPicker(ofVec2f const& position) :
    T_Super(position.x, position.y, 300, 140) {

    m_rgbImage.reset(datUtilities::LoadImageFromAssetsFolder("rgb_colors.png"));
    assert(nullptr != m_rgbImage);
}


datColorPicker::~datColorPicker() {

}


bool datColorPicker::onLeftMouseButtonDown(datMouseEvent const& ev) {

    ofVec2f hitPosition = ev;
    hitPosition.x -= getX();
    hitPosition.y -= getY();

    // click outside the rgb image for colors
    if (255 < hitPosition.x)
        return true;

    datRenderer& renderer = datRenderer::GetActiveRenderer();
    ofColor color = renderer.getActiveDrawColor();

    if (hitPosition.y <= 40) {
        color.r = hitPosition.x;
    }
    else if (hitPosition.y <= 80) {
        color.g = hitPosition.x;
    }
    else if (hitPosition.y <= 120) {
        color.b = hitPosition.x;
    }
    else
        return true;

    renderer.setActiveDrawColor(color);
    return true;
}


void datColorPicker::onDraw() {

    if (nullptr != m_rgbImage)
        m_rgbImage->draw(getX(), getY(), 256, 120);

    ofRectangle rect(getX(), getY() + 130, getWidth(), 10);

    ofColor current = datRenderer::GetActiveRenderer().getActiveDrawColor();
    ofSetColor(current);
    ofDrawRectangle(rect);
}
