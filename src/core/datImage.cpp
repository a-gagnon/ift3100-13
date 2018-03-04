//=======================================================================================
// datImage.cpp
// IFT3100-13
//=======================================================================================
#include "datImage.h"

USING_DAT_NAMESPACE

datImage::datImage(ofImage const& image, ofPoint const& position, uint32_t width, uint32_t height) : 
    m_image(image),
    m_position(position),
    m_width(width),
    m_height(height) {
    assert(m_image.isAllocated());
}


datImage::~datImage() {

}


void datImage::draw() const {
    m_image.draw(m_position.x, m_position.y, m_width, m_height);
}


std::vector<ofPoint> datImage::Get4Corners() const {

    ofPoint point0 = m_position;

    ofPoint point1 = m_position;
    point1.y += m_height;

    ofPoint point2 = point1;
    point2.x += m_width;

    ofPoint point3 = m_position;
    point3.x += m_width;

    std::vector<ofPoint> points { point0, point1, point2, point3 };
    return std::move(points);
}


