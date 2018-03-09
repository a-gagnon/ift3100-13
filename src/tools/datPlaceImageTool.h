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
    std::vector<ofImage> m_imagesToPlace;
    ofPoint m_position;

    ofxPanel m_panel;
    ofParameter<int> m_paramWidth;
    ofParameter<int> m_paramHeight;
    void UpdateParameters();

protected:
    virtual void onStartTool() override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onRightMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onDraw() override;


public:
    void SetImagesToPlace(std::vector<ofImage> const& images) { m_imagesToPlace = images; }

    datPlaceImageTool();
    virtual ~datPlaceImageTool();
};

END_DAT_NAMESPACE
