//=======================================================================================
// datButton.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datInputView.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Generic style holder for buttons
//=======================================================================================
struct datButtonStyle {

public:
    ofColor buttonBackgroundColor;
    ofColor buttonBackgroundColorFocused;
    ofColor tooltipBackgroundColor;
    ofColor tooltipTextColor;

public:
    static datButtonStyle createForToolButton();
};

//=======================================================================================
// Generic button
//=======================================================================================
struct datButton : datInputView {

DEFINE_T_SUPER(datInputView)

protected:
    datCallbackFunction m_pCallbackFunction;
    datButtonStyle m_style;
    std::unique_ptr<ofImage> m_image;
    std::string m_tooltip;

protected:
    virtual void onHover() override;
    virtual void onBlur() override;
    virtual void onClick() override;
    virtual void onDraw() override;

public:
    datButton(datButtonStyle const& style);
    datButton(float x, float y, float width, float height, datButtonStyle const& style);
    virtual ~datButton();

    // Sets the function that will be called when the button is pressed
    void SetOnPressedCallback(datCallbackFunction func) { m_pCallbackFunction = func; }

    // Sets the image that will be displayed
    // @remarks takes ownership with a unique_ptr
    void SetImage(ofImage* pImage) { m_image.reset(pImage); }

    // Sets the tooltip that will be displayed when the cursor stays over the button
    void SetTooltip(std::string const& text) { m_tooltip = text; }

    void SetStyle(datButtonStyle const& style) { m_style = style; }
    datButtonStyle const& GetStyle() const { return m_style; }
    datButtonStyle& GetStyleR() { return m_style; }
};

END_DAT_NAMESPACE
