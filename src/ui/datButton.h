//=======================================================================================
// datButton.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datView.h"

BEGIN_DAT_NAMESPACE

struct datButton;

// Define pointer-to-function
typedef void(*datButtonCallbackFunction)(datButton&);

//=======================================================================================
// Generic style holder for buttons
//=======================================================================================
struct datButtonStyle {

public:
    ofColor buttonBackgroundColor;
    ofColor buttonBackgroundColorMouseInside;
    ofColor buttonBackgroundColorToggled;
    ofColor tooltipBackgroundColor;
    ofColor tooltipTextColor;

public:
    static datButtonStyle createForToolButton();
};

//=======================================================================================
// Generic button
//=======================================================================================
struct datButton : datView {

DEFINE_T_SUPER(datView)

protected:
    datButtonCallbackFunction m_pCallbackFunction;
    datButtonStyle m_style;
    std::unique_ptr<ofImage> m_image;
    std::string m_tooltip;
    bool m_isToggled;

protected:
    virtual bool onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual bool onLeftMouseButtonUp(datMouseEvent const& ev) override;
    virtual void onHover() override;
    virtual void onBlur() override;
    virtual void onDraw() override;

    ofColor DetermineDrawColor() const;

public:
    datButton(datButtonStyle const& style);
    datButton(float x, float y, float width, float height, datButtonStyle const& style);
    virtual ~datButton();

    // Sets the function that will be called when the button is pressed
    void SetOnPressedCallback(datButtonCallbackFunction func) { m_pCallbackFunction = func; }

    void PressButton();

    // Sets the image that will be displayed
    // @remarks takes ownership with a unique_ptr
    void SetImage(ofImage* pImage) { m_image.reset(pImage); }

    // Sets the tooltip that will be displayed when the cursor stays over the button
    void SetTooltip(std::string const& text) { m_tooltip = text; }

    void SetStyle(datButtonStyle const& style) { m_style = style; }
    datButtonStyle const& GetStyle() const { return m_style; }
    datButtonStyle& GetStyleR() { return m_style; }

    void SetToggle(bool yesNo) { m_isToggled = yesNo; }
    bool IsToggled() const { return m_isToggled; }
};

END_DAT_NAMESPACE
