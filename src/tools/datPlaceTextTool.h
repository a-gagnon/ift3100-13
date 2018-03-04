//=======================================================================================
// datPlaceTextTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datPlaceTextTool : datEditTool {

private:
    std::string m_text;
    ofTrueTypeFont m_font;
    ofPoint m_position;

    ofxPanel m_panel;
    ofParameter<ofColor> m_paramLineColor;

private:
    void onLineColorChanged(ofColor& color) { GetRenderer().GetActiveDisplayParamsR().lineColor = color; }

    void SetPlaceholderText();
    bool IsPlaceholderText() const;

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onKeyPressed(ofKeyEventArgs const& ev) override;
    virtual void onDraw() override;

public:
    datPlaceTextTool();
    virtual ~datPlaceTextTool();
};

END_DAT_NAMESPACE
