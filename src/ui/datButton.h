//=======================================================================================
// datButton.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datView.h"

BEGIN_DAT_NAMESPACE

struct datButton;

//=======================================================================================
// Generic style holder for buttons
//=======================================================================================
struct datButtonStyle {

public:
    ofColor buttonBackgroundColor;
    ofColor buttonBackgroundColorDisabled;
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
    ofEvent<datButton> m_onPressedEvent;
    datButtonStyle m_style;
    std::unique_ptr<ofImage> m_image;
    std::string m_tooltip;
    bool m_isToggled;
    bool m_isEnabled;

protected:
    virtual bool onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual bool onLeftMouseButtonUp(datMouseEvent const& ev) override;
    virtual void onHover() override;
    virtual void onBlur() override;
    virtual void onDraw() override;

    ofColor DetermineDrawColor() const;

public:
    datButton(float x, float y, float width = 40.0, float height = 40.0);
    virtual ~datButton();

    ofEvent<datButton>& GetOnPressedEvent() { return m_onPressedEvent; }
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

    void SetEnabled(bool yesNo) { m_isEnabled = yesNo; }
    bool IsEnabled() const { return m_isEnabled; }
};

END_DAT_NAMESPACE
