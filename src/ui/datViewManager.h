//=======================================================================================
// datViewManager.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datView.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Manager class for input views.
// The manager owns a 'main' view that has the same size as the application
// Any view can be added as a child of the main view
//=======================================================================================
struct datViewManager : datNonCopyableClass, IViewRemovedListener {

private:
    static datViewManager* s_activeViewManager; // pointer to active ViewManager or nullptr
    std::unique_ptr<datView> m_mainView;
    datView* m_viewWithMouseInside;

private:
    virtual void _OnViewDropped(datView& view) override;

    // Returns the view that is most suitable to get the event
    datView* FindTargetView(ofVec2f const& point) const;
    datView* GetViewByNameInternal(datView& view, std::string const& name) const;
    void DoDrawInternal(datView& view) const;

public:
    datViewManager();
    ~datViewManager();
    static datViewManager& GetActiveViewManager();

    datView& GetMainView() const;
    datView* GetViewByName(std::string const& name) const;

    // Sends the mouse event to the appropriate view
    // @remarks returns true if the event is handled by the view
    bool SendMouseEvent(datMouseEvent const& ev);
    void DoDraw();
};

END_DAT_NAMESPACE
