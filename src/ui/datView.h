//=======================================================================================
// datView.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../core/datDefinitions.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Bass class for UI views
//=======================================================================================
struct datView : ofRectangle, datNonCopyableClass {

DEFINE_T_SUPER(ofRectangle)
friend struct datViewManager;

private:
    datView* m_pParentView;
    std::vector<std::unique_ptr<datView>> m_views;

    std::string m_name;         // optional: unique name to find this view
    ofColor m_backgroundColor;
    bool m_isVisible;           // is this view displayed or not
    bool m_isMouseInside;       // set by datViewManager

protected:
    datView();
    datView(float x, float y, float width, float height);

    virtual bool onMouseMotion(datMouseEvent const& ev);
    virtual bool onLeftMouseButtonDown(datMouseEvent const& ev);
    virtual bool onLeftMouseButtonUp(datMouseEvent const& ev);
    virtual bool onRightMouseButtonDown(datMouseEvent const& ev);
    virtual bool onRightMouseButtonUp(datMouseEvent const& ev);
    virtual void onHover();
    virtual void onBlur();
    virtual void onDraw();

public:
    virtual ~datView() {}

    datView* GetParentView() const { return m_pParentView; }
    // Takes ownership of the view using a unique_ptr
    void AddView(datView* pView);
    void RemoveView(datView* pView);

    bool IsVisible() const;
    void SetVisible(bool yesNo);
    bool IsMouseInside() const { return m_isMouseInside; }

    void SetName(std::string const& name) { m_name = name; }
    std::string const& GetName() const { return m_name; }

    ofColor const& GetBackgroundColor() const { return m_backgroundColor; }
    void SetBackgroundColor(ofColor const& color) { m_backgroundColor = color; }
};

END_DAT_NAMESPACE
