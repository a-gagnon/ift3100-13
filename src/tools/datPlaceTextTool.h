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
    std::unique_ptr<datTextString> m_transient;

    ofTrueTypeFont m_font;
    std::string m_text;

    ofxPanel m_panel;
    ofParameter<ofColor> m_paramFillColor;

private:
    void onFillColorChanged(ofColor& color) { GetRenderer().GetActiveDisplayParamsR().fillColor = color; updateTransient(); }
    void SetPlaceholderText();
    bool IsPlaceholderText() const;
    void updateTransient(datMouseEvent const* pMouseEvent = nullptr);

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
