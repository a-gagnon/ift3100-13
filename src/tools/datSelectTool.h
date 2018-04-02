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
        Crossing,   // objects inside or crossing the rectangle are selected
        Hit         // objects that intersects with the (single-point) hit
    };

private:
    bool m_isMouseDrag;
    bool m_hasFirstPoint;
    ofVec2f m_downPoint;
    ofRectangle m_downPointRect;

    ofColor m_color;
    ofRectangle m_rectangle;
    SelectionMode m_mode;

    ofxPanel m_panel;
    datofxRadioButton m_cursorTypeRadio1;
    datofxRadioButton m_cursorTypeRadio2;
    datofxRadioButton m_cursorTypeRadio3;
    datofxRadioButton m_cursorTypeRadio4;
    datofxRadioButton m_cursorTypeRadio5;
    ofParameter<ofColor> m_appBackgroundColor;

private:
    void selectObjectsAndClearState(datMouseEvent const& ev);
    void updateRectangle(datMouseEvent const& ev);
    void updateSelectionMode(datMouseEvent const& ev);
    void setBackgroundColor(ofColor& color) { GetRenderer().SetBackgroundColor(color); }

protected:
    virtual void onStartTool() override;
    virtual void onExitTool() override;
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
