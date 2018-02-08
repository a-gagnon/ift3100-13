//=======================================================================================
// datPlaceTextTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datPlaceTextTool : datTool {

private:
    std::string m_text;
    ofTrueTypeFont m_font;

protected:
    virtual void onRightMouseButtonDown(ofVec2f const& point) override;
    virtual void onKeyPressed(ofKeyEventArgs const& ev) override;
    virtual void onDraw() override;

public:
    datPlaceTextTool();
    virtual ~datPlaceTextTool();
};

END_DAT_NAMESPACE
