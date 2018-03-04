//=======================================================================================
// datTextString.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Basic wrapper around the ofTrueTypeFont class
//=======================================================================================
struct datTextString {

public:
    ofTrueTypeFont m_trueTypeFont;
    std::string m_text;
    ofPoint m_position;

public:
    datTextString(ofTrueTypeFont const& trueTypeFont, std::string const& text, ofVec2f const& position);
    ~datTextString();

    void draw() const;
};

END_DAT_NAMESPACE
