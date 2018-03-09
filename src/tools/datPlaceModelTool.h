//=======================================================================================
// datPlaceModelTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

// Define pointer-to-function. Called when the tool has no more images to place
typedef void(*datPlaceModelDoneCallback)(void);

//=======================================================================================
struct datPlaceModelTool : datEditTool {

private:
    datPlaceModelDoneCallback m_pCallbackFunction;
    std::vector<ofxAssimpModelLoader> m_modelsToPlace;
    ofPoint m_position;

    ofxPanel m_panel;
    void UpdateParameters();

protected:
    virtual void onStartTool() override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onRightMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onDraw() override;


public:
    void SetModelsToPlace(std::vector<ofxAssimpModelLoader>&& models) { m_modelsToPlace = std::move(models); }

    datPlaceModelTool(datPlaceModelDoneCallback callback);
    virtual ~datPlaceModelTool();
};

END_DAT_NAMESPACE
