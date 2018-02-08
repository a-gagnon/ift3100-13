//=======================================================================================
// datInputManager.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datInputView.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Manager class for input views.
// Views are typically created by the application, but must be registered with
// the input manager to receive events and display properly
//=======================================================================================
struct datInputManager : NonCopyableClass {

private:
    std::vector<std::unique_ptr<datInputView>> m_views;
    datInputView* m_focusedView;

private:
    void AddListeners();
    void RemoveListeners();
    void OnDraw(ofEventArgs& ev);

    datInputView* FindHit(ofVec2f const& point) const;

public:
    datInputManager();
    ~datInputManager();

    // Sends the mouse event to the active tool, if any
    // @remarks returns true if the event occurred inside an input view
    bool SendMouseEvent(ofMouseEventArgs const& ev);

    // Takes ownership of the view by putting it inside a unique_ptr
    // adds the view to the list of active views
    void AddView(datInputView* pView);
};

END_DAT_NAMESPACE
