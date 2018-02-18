//=======================================================================================
// datColorPicker.cpp
// IFT3100-13
//=======================================================================================
#include "datColorPicker.h"

USING_DAT_NAMESPACE

#define COLOR_IMAGE_WIDTH 256
#define COLOR_IMAGE_HEIGHT 120

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

    // Clicking outside the R/G/B image range should do nothing
    if (COLOR_IMAGE_WIDTH <= hitPosition.x || COLOR_IMAGE_HEIGHT <= hitPosition.y)
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

    m_rgbImage->draw(getX(), getY(), COLOR_IMAGE_WIDTH, COLOR_IMAGE_HEIGHT);


    // Draw a rectangle to show the color preview
    const ofColor current = datRenderer::GetActiveRenderer().getActiveDrawColor();
    ofSetColor(current);
    const ofRectangle rect(getX(), getY() + 130, COLOR_IMAGE_WIDTH, 10);
    ofDrawRectangle(rect);

    ofSetColor(ofColor::black);

    // Draw the text
    ofVec2f textCoords(getX() + COLOR_IMAGE_WIDTH + 15, getY() - 15);

    textCoords.y += COLOR_IMAGE_HEIGHT / 3;
    std::string redText("R: " + std::to_string(current.r));
    ofDrawBitmapString(redText, textCoords);

    textCoords.y += COLOR_IMAGE_HEIGHT / 3;
    std::string greenText("G: " + std::to_string(current.g));
    ofDrawBitmapString(greenText, textCoords);

    textCoords.y += COLOR_IMAGE_HEIGHT / 3;
    std::string blueText("B: " + std::to_string(current.b));
    ofDrawBitmapString(blueText, textCoords);

}
