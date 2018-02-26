//=======================================================================================
// datSelectTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"
#include "../ui/datofxRadioButton.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datSelectTool : datEditTool {

private:
    enum class SelectionMode {
        Window,     // objects that are strictly inside the rectangle are selected
        Crossing    // objects inside or crossing the rectangle are selected
    };

private:
    bool m_isMouseDrag;
    bool m_hasFirstPoint;
    ofVec2f m_downPoint;

    ofColor m_color;
    ofRectangle m_rectangle;
    SelectionMode m_mode;

    ofxPanel m_panel;
    datofxRadioButton m_radio1;
    datofxRadioButton m_radio2;
    datofxRadioButton m_radio3;
    datofxRadioButton m_radio4;
    datofxRadioButton m_radio5;

private:
    void selectObjectsAndClearState();
    void updateRectangle(datMouseEvent const& ev);
    void updateSelectionMode(datMouseEvent const& ev);

protected:
    virtual void onStartTool() override;
    virtual void onLeftMouseButtonDown(datMouseEvent const& ev) override;
    virtual void onLeftMouseButtonUp(datMouseEvent const& ev) override;
    virtual void onMouseMotion(datMouseEvent const& ev) override;
    virtual void onKeyPressed(ofKeyEventArgs const& ev) override;
    virtual void onDraw() override;

public:
    datSelectTool();
    virtual ~datSelectTool();
};

END_DAT_NAMESPACE
