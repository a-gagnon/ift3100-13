//=======================================================================================
// datColorPicker.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datView.h"

BEGIN_DAT_NAMESPACE

struct datColorPicker;

//=======================================================================================
// Color picker
// Draw 3 images of 256x40 px that represents each color
//=======================================================================================
struct datColorPicker : datView {

DEFINE_T_SUPER(datView)

protected:
    std::unique_ptr<ofImage> m_rgbImage;

protected:
    virtual bool onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onDraw() override;

public:
    datColorPicker(ofVec2f const& position);
    virtual ~datColorPicker();
};

END_DAT_NAMESPACE
