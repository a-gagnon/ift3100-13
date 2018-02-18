//=======================================================================================
// datPlaceImageTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

// Define pointer-to-function. Called when the tool has no more images to place
typedef void(*datPlaceImageDoneCallback)(void);

//=======================================================================================
struct datPlaceImageTool : datEditTool {

private:
    datPlaceImageDoneCallback m_pCallbackFunction;
    std::vector<ofImage> m_imagesToPlace;
    ofPoint m_position;

protected:
    virtual void onStartTool() override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onRightMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onDraw() override;

public:
    void SetImagesToPlace(std::vector<ofImage> const& images) { m_imagesToPlace = images; }

    datPlaceImageTool(datPlaceImageDoneCallback callback);
    virtual ~datPlaceImageTool();
};

END_DAT_NAMESPACE
