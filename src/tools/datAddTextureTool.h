//=======================================================================================
// datAddTextureTool.h
// IFT3100-13
//=======================================================================================

#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

struct datAddTextureTool : datEditTool {

private:
    std::unique_ptr<ofImage> m_mask;
    ofShader m_shader;
    ofFbo m_fbo;

    std::vector<std::unique_ptr<datElement>> m_elements;

    void applyTexture();

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    virtual void onDraw() override;

public:
    datAddTextureTool();
    virtual ~datAddTextureTool();
};

END_DAT_NAMESPACE
