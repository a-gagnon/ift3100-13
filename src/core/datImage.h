//=======================================================================================
// datImage.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDefinitions.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Basic wrapper around the ofImage class
//=======================================================================================
struct datImage {

public:
    ofImage m_image;
    ofPoint m_position;
    uint32_t m_width;
    uint32_t m_height;

public:
    datImage(ofImage const& image, ofPoint const& position, uint32_t width, uint32_t height);
    ~datImage();

    void draw() const;
};

END_DAT_NAMESPACE
