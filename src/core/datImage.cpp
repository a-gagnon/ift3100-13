//=======================================================================================
// datImage.cpp
// IFT3100-13
//=======================================================================================
#include "datImage.h"

USING_DAT_NAMESPACE

datImage::datImage(ofImage const& image, ofPoint const& position, uint32_t width, uint32_t height) : 
    m_image(image), m_position(position), m_width(width), m_height(height) {
    assert(m_image.isAllocated());
}


datImage::~datImage() {

}


void datImage::draw() const {
    m_image.draw(m_position.x, m_position.y, m_width, m_height);
}
