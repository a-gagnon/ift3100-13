//=======================================================================================
// datPlaceModelTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Tool to place a model inside the scene
//=======================================================================================
struct datPlaceModelTool : datEditTool {

private:
    std::unique_ptr<datAssimpModel> m_transient;
    std::vector<ofxAssimpModelLoader> m_modelsToPlace;
    bool m_hasStarted;

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onRightMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onDraw() override;

    void updateTransient(datMouseEvent const& ev);

public:
    void SetModelsToPlace(std::vector<ofxAssimpModelLoader>&& models) { m_modelsToPlace = std::move(models); }

    datPlaceModelTool();
    virtual ~datPlaceModelTool();
};

END_DAT_NAMESPACE
