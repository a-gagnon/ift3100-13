//=======================================================================================
// datToolbar.cpp
// IFT3100-13
//=======================================================================================
#include "datToolbar.h"

USING_DAT_NAMESPACE

datToolbar* datToolbar::s_activeToolbar = nullptr;

datToolbar::datToolbar() {
    s_activeToolbar = this;
}


datToolbar::~datToolbar() {
    s_activeToolbar = nullptr;
}


datToolbar& datToolbar::GetActiveToolbar() {
    assert(nullptr != s_activeToolbar);
    return *s_activeToolbar;
}


void datToolbar::InitToolbar(datView& mainView) {

    // Select tool
    datButton* pSelectToolButton = new datButton(10, 20, 40, 40, datButtonStyle::createForToolButton());
    pSelectToolButton->SetOnPressedCallback(onSelectPressed);
    pSelectToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("cursor.png"));
    pSelectToolButton->SetTooltip(datLocalization::SelectTool_Tooltip());
    pSelectToolButton->SetName(NameSelectButton());
    m_toolButtons.push_back(pSelectToolButton);
    mainView.AddView(pSelectToolButton);

    // Place polyline tool
    datButton* pPolylineToolButton = new datButton(10, 65, 40, 40, datButtonStyle::createForToolButton());
    pPolylineToolButton->SetOnPressedCallback(startPlacePolylineTool);
    pPolylineToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("pencil.png"));
    pPolylineToolButton->SetTooltip(datLocalization::PlacePolylineTool_Tooltip());
    pPolylineToolButton->SetName(NamePlacePolylineButton());
    m_toolButtons.push_back(pPolylineToolButton);
    mainView.AddView(pPolylineToolButton);

    // Place text tool
    datButton* pWriteTextToolButton = new datButton(10, 110, 40, 40, datButtonStyle::createForToolButton());
    pWriteTextToolButton->SetOnPressedCallback(startPlaceTextTool);
    pWriteTextToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("write_text.png"));
    pWriteTextToolButton->SetTooltip(datLocalization::PlaceTextTool_Tooltip());
    pWriteTextToolButton->SetName(NamePlaceTextButton());
    m_toolButtons.push_back(pWriteTextToolButton);
    mainView.AddView(pWriteTextToolButton);

    // Insert image tool
    datButton* pPlaceImageToolButton = new datButton(10, 155, 40, 40, datButtonStyle::createForToolButton());
    pPlaceImageToolButton->SetOnPressedCallback(startPlaceImageTool);
    pPlaceImageToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("add_image.png"));
    pPlaceImageToolButton->SetTooltip(datLocalization::PlaceImageTool_Tooltip());
    pPlaceImageToolButton->SetName(NamePlaceImageButton());
    m_toolButtons.push_back(pPlaceImageToolButton);
    mainView.AddView(pPlaceImageToolButton);

}


void datToolbar::setToggleAllButtonsOff() {

    for (auto const& pButton : m_toolButtons) {
        pButton->SetToggle(false);
    }
}


void datToolbar::onSelectPressed(datButton& button) {
    GetActiveToolbar().setToggleAllButtonsOff();
}


void datToolbar::onPlacePolylinePressed(datButton& button) {

}
void datToolbar::onPlaceTextPressed(datButton& button) {

}

void datToolbar::onPlaceImagePressed(datButton& button) {

}

void datToolbar::onPlaceImageCompleted() {


}









// Private button names so we can refer to a specific button at runtime
// not exposed to users
#define DAT_BUTTON_NAME_SELECT "btn_selectTool"
#define DAT_BUTTON_NAME_PLACEPOLYLINE "btn_placePolylineTool"
#define DAT_BUTTON_NAME_PLACETEXT "btn_placeTextTool"
#define DAT_BUTTON_NAME_PLACEIMAGE "btn_placeImageTool"

namespace {

    void setToggleAllToolButtons(bool yesNo) {

        const std::vector<std::string> buttonNames {
            DAT_BUTTON_NAME_SELECT,
            DAT_BUTTON_NAME_PLACEPOLYLINE,
            DAT_BUTTON_NAME_PLACETEXT,
            DAT_BUTTON_NAME_PLACEIMAGE
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
        setToggleAllToolButtons(false);
        button.SetToggle(true);
        datApplication::GetApp().GetToolManager().StartTool(new datSelectTool());
    }

    void startPlacePolylineTool(datButton& button) {
        setToggleAllToolButtons(false);
        button.SetToggle(true);
        datApplication::GetApp().GetToolManager().StartTool(new datPlacePolylineTool());
    }

    void startPlaceTextTool(datButton& button) {
        setToggleAllToolButtons(false);
        button.SetToggle(true);
        datApplication::GetApp().GetToolManager().StartTool(new datPlaceTextTool());
    }

    void onPlaceImageCompleted() {
        datViewManager& manager = datApplication::GetApp().GetViewManager();

        // Exits the place image tool and starts the select tool
        auto pSelectToolButton = manager.GetViewByName(DAT_BUTTON_NAME_SELECT);
        static_cast<datButton*>(pSelectToolButton)->PressButton();
    }
    void startPlaceImageTool(datButton& button) {

        setToggleAllToolButtons(false);
        button.SetToggle(true);

        auto pTool = new datPlaceImageTool();
        pTool->SetOnCompletedCallback(onPlaceImageCompleted);
        datApplication::GetApp().GetToolManager().StartTool(pTool);
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
    pSelectToolButton->SetTooltip(datLocalization::SelectTool_Tooltip());
    pSelectToolButton->SetName(DAT_BUTTON_NAME_SELECT);
    mainView.AddView(pSelectToolButton);

    // Place polyline tool
    datButton* pPolylineToolButton = new datButton(10, 65, 40, 40, datButtonStyle::createForToolButton());
    pPolylineToolButton->SetOnPressedCallback(startPlacePolylineTool);
    pPolylineToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("pencil.png"));
    pPolylineToolButton->SetTooltip(datLocalization::PlacePolylineTool_Tooltip());
    pPolylineToolButton->SetName(DAT_BUTTON_NAME_PLACEPOLYLINE);
    mainView.AddView(pPolylineToolButton);

    // Place text tool
    datButton* pWriteTextToolButton = new datButton(10, 110, 40, 40, datButtonStyle::createForToolButton());
    pWriteTextToolButton->SetOnPressedCallback(startPlaceTextTool);
    pWriteTextToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("write_text.png"));
    pWriteTextToolButton->SetTooltip(datLocalization::PlaceTextTool_Tooltip());
    pWriteTextToolButton->SetName(DAT_BUTTON_NAME_PLACETEXT);
    mainView.AddView(pWriteTextToolButton);

    // Insert image tool
    datButton* pPlaceImageToolButton = new datButton(10, 155, 40, 40, datButtonStyle::createForToolButton());
    pPlaceImageToolButton->SetOnPressedCallback(startPlaceImageTool);
    pPlaceImageToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("add_image.png"));
    pPlaceImageToolButton->SetTooltip(datLocalization::PlaceImageTool_Tooltip());
    pPlaceImageToolButton->SetName(DAT_BUTTON_NAME_PLACEIMAGE);
    mainView.AddView(pPlaceImageToolButton);


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


void datApplication::dragged(ofDragInfo& ev) {

    std::vector<ofImage> images;

    for (auto const& filePath : ev.files) {

        ofImage image;
        if (image.load(filePath))
            images.push_back(std::move(image));
    }

    if (!images.empty()) {
        setToggleAllToolButtons(false);
        auto pView = GetViewManager().GetViewByName(DAT_BUTTON_NAME_PLACEIMAGE);
        static_cast<datButton*>(pView)->SetToggle(true);
        
        auto pTool = new datPlaceImageTool();
        pTool->SetOnCompletedCallback(onPlaceImageCompleted);
        pTool->SetImagesToPlace(images);
        datApplication::GetApp().GetToolManager().StartTool(pTool);
    }
}


void datApplication::draw() {

    T_Super::draw();

    GetRenderer().render();
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

void datApplication::exit() {
    ofImage img;
    img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    img.save("screenshot.png");
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


datRenderer& datApplication::GetRenderer() {
    if (nullptr == m_renderer)
        m_renderer.reset(new datRenderer());

    return *m_renderer;
}


datApplication& datApplication::GetApp() {

    ofBaseApp* pApp = ofGetAppPtr();
    assert(nullptr != pApp);

    assert(nullptr != dynamic_cast<datApplication*>(pApp));
    return *static_cast<datApplication*>(pApp);
}
