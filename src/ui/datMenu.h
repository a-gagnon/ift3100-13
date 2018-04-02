//=======================================================================================
// datMenu.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datView.h"
#include "datButton.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Bass class for a simple menu
//=======================================================================================
struct datMenu : datView {

DEFINE_T_SUPER(datView)

    enum class Layout { Horizontal, Vertical };

public:
    static constexpr float IconWidth = 35.0;
    static constexpr float IconHeight = 35.0;
    static constexpr float Padding = 5.0;

private:
    Layout m_layout;

protected:
    void layout();

    virtual void onViewAdded() override;
    virtual void onViewRemoved() override;

public:
    datMenu(float x, float y, Layout layout);
    virtual ~datMenu() {}

    datButton* AddToolButton(std::string const& name, std::string const& tooltip, std::string const& iconName);
};

END_DAT_NAMESPACE
