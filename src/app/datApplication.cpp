//=======================================================================================
// datApplication.cpp
// IFT3100-13
//=======================================================================================
#include "datApplication.h"

USING_DAT_NAMESPACE

#define BUTTON_NAME_SELECT "btn_selectTool"
#define BUTTON_NAME_PLACEPOLYLINE "btn_placePolylineTool"
#define BUTTON_NAME_PLACETEXT "btn_placeTextTool"

namespace {

    void setToggleAllToolButtons(bool yesNo) {

        const std::vector<std::string> buttonNames{
            BUTTON_NAME_SELECT,
            BUTTON_NAME_PLACEPOLYLINE,
            BUTTON_NAME_PLACETEXT
        };

        datViewManager& manager = datApplication::GetApp().GetViewManager();
        for (auto const& buttonName : buttonNames) {

            auto pButton = manager.GetViewByName(buttonName);
            if (nullptr != pButton) {
                static_cast<datButton*>(pButton)->SetToggle(yesNo);
            }
        }
    }

    void startSelectTool(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datSelectTool());
        setToggleAllToolButtons(false);
        button.SetToggle(true);
    }

    void startPlacePolylineTool(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datPlacePolylineTool());
        setToggleAllToolButtons(false);
        button.SetToggle(true);
    }

    void startPlaceTextTool(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datPlaceTextTool());
        setToggleAllToolButtons(false);
        button.SetToggle(true);
    }

}; // end unnamed namespaceters


datApplication::datApplication() {

}


datApplication::~datApplication() {

}


void datApplication::SetupUI() {

    datView& mainView = GetViewManager().GetMainView();
    mainView.setPosition(0, 0);
    mainView.setWidth(ofGetWidth());
    mainView.setHeight(ofGetHeight());

    // Select tool
    datButton* pSelectToolButton = new datButton(10, 20, 40, 40, datButtonStyle::createForToolButton());
    pSelectToolButton->SetOnPressedCallback(startSelectTool);
    pSelectToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("cursor.png"));
    pSelectToolButton->SetTooltip(datLocalization::Tooltip_SelectTool());
    pSelectToolButton->SetName(BUTTON_NAME_SELECT);
    mainView.AddView(pSelectToolButton);

    // Place polyline tool
    datButton* pPolylineToolButton = new datButton(10, 65, 40, 40, datButtonStyle::createForToolButton());
    pPolylineToolButton->SetOnPressedCallback(startPlacePolylineTool);
    pPolylineToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("pencil.png"));
    pPolylineToolButton->SetTooltip(datLocalization::Tooltip_PlacePolylineTool());
    pPolylineToolButton->SetName(BUTTON_NAME_PLACEPOLYLINE);
    mainView.AddView(pPolylineToolButton);

    // Place text tool
    datButton* pWriteTextToolButton = new datButton(10, 110, 40, 40, datButtonStyle::createForToolButton());
    pWriteTextToolButton->SetOnPressedCallback(startPlaceTextTool);
    pWriteTextToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("write_text.png"));
    pWriteTextToolButton->SetTooltip(datLocalization::Tooltip_PlaceTextTool());
    pWriteTextToolButton->SetName(BUTTON_NAME_PLACETEXT);
    mainView.AddView(pWriteTextToolButton);

    // Set the select tool as the active tool
    pSelectToolButton->PressButton();
}


void datApplication::setup() {

    m_width = ofGetWidth();
    m_height = ofGetHeight();

    SetupUI();
}


void datApplication::ClampEvent(datMouseEvent& ev) const {

    if (ev.x < 1)
        ev.x = 1.0;
    else if (m_width < ev.x)
        ev.x = m_width;

    if (ev.y < 1)
        ev.y = 1.0;
    else if (m_height < ev.y)
        ev.y = m_height;
}


bool datApplication::SendMouseEvent(ofMouseEventArgs& ev) {

    datMouseEvent datEvent(ev);
    ClampEvent(datEvent);

    if (GetViewManager().SendMouseEvent(datEvent))
        return true;

    if (GetToolManager().SendMouseEvent(datEvent))
        return true;

    return false;
}


bool datApplication::SendKeyEvent(ofKeyEventArgs& ev) {

    if (GetToolManager().SendKeyEvent(ev))
        return true;

    return false;
}


void datApplication::draw() {

    T_Super::draw();
    GeometryCache::GetCache().drawCachedGeometries();
    GetViewManager().DoDraw();
    GetToolManager().DoDraw();
}

void datApplication::mousePressed(ofMouseEventArgs& ev) {
    if (!SendMouseEvent(ev))
        T_Super::mousePressed(ev);
}


void datApplication::mouseReleased(ofMouseEventArgs& ev) {
    if (!SendMouseEvent(ev))
        T_Super::mouseReleased(ev);
}


void datApplication::mouseMoved(ofMouseEventArgs& ev) {
    if (!SendMouseEvent(ev))
        T_Super::mouseMoved(ev);
}


void datApplication::mouseDragged(ofMouseEventArgs& ev) {
    if (!SendMouseEvent(ev))
        T_Super::mouseDragged(ev);
}


void datApplication::keyPressed(ofKeyEventArgs& ev) {
    if (!SendKeyEvent(ev))
        T_Super::keyPressed(ev);
}


void datApplication::windowResized(ofResizeEventArgs& resize) {
    T_Super::windowResized(resize);

    m_width = resize.width;
    m_height = resize.height;

    // Main view must always be same size as the application
    datView& mainView = GetViewManager().GetMainView();
    mainView.setWidth(resize.width);
    mainView.setHeight(resize.height);
}

datToolManager& datApplication::GetToolManager() {

    if (nullptr == m_toolManager)
        m_toolManager.reset(new datToolManager());

    return *m_toolManager;
}


datViewManager& datApplication::GetViewManager() {

    if (nullptr == m_viewManager)
        m_viewManager.reset(new datViewManager());

    return *m_viewManager;
}


datApplication& datApplication::GetApp() {

    ofBaseApp* pApp = ofGetAppPtr();
    assert(nullptr != pApp);

    assert(nullptr != dynamic_cast<datApplication*>(pApp));
    return *static_cast<datApplication*>(pApp);
}
