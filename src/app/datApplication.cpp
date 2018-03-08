//=======================================================================================
// datApplication.cpp
// IFT3100-13
//=======================================================================================
#include "datApplication.h"

USING_DAT_NAMESPACE

// Private names so we can refer to a specific views at runtime
// not exposed to users
#define DAT_BUTTON_NAME_SELECT "btn_selectTool"
#define DAT_BUTTON_NAME_PLACEPOLYLINE "btn_placePolylineTool"
#define DAT_BUTTON_NAME_PLACETEXT "btn_placeTextTool"
#define DAT_BUTTON_NAME_PLACEIMAGE "btn_placeImageTool"
#define DAT_BUTTON_NAME_EXPORTIMAGE "btn_exportImageTool"
#define DAT_BUTTON_NAME_EDITATTRIBUTES "btn_editAttributesTool"

#define DAT_BUTTON_NAME_DELETESELECTED "btn_deleteSelected"

namespace {

    void setToggleAllToolButtons(bool yesNo) {

        const std::vector<std::string> buttonNames {
            DAT_BUTTON_NAME_SELECT,
            DAT_BUTTON_NAME_PLACEPOLYLINE,
            DAT_BUTTON_NAME_PLACETEXT,
            DAT_BUTTON_NAME_PLACEIMAGE,
            DAT_BUTTON_NAME_EXPORTIMAGE,
            DAT_BUTTON_NAME_EDITATTRIBUTES
        };

        datViewManager& manager = datApplication::GetApp().GetViewManager();
        for (auto const& buttonName : buttonNames) {

            auto pButton = manager.GetViewByName(buttonName);
            if (nullptr != pButton) {
                static_cast<datButton*>(pButton)->SetToggle(yesNo);
            }
        }
    }

    void startDefaultTool() {
        auto pSelectToolButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_SELECT);
        static_cast<datButton*>(pSelectToolButton)->PressButton();
    }

    void onStartSelectToolPressed(datButton& button) {
        setToggleAllToolButtons(false);
        button.SetToggle(true);
        datApplication::GetApp().GetToolManager().StartTool(new datSelectTool());
    }

    void onStartPlacePolylineToolPressed(datButton& button) {
        setToggleAllToolButtons(false);
        button.SetToggle(true);
        datApplication::GetApp().GetToolManager().StartTool(new datPlacePolylineTool());
    }

    void onStartPlaceTextToolPressed(datButton& button) {
        setToggleAllToolButtons(false);
        button.SetToggle(true);
        datApplication::GetApp().GetToolManager().StartTool(new datPlaceTextTool());
    }

    void onStartPlaceImageToolPressed(datButton& button) {
        setToggleAllToolButtons(false);
        button.SetToggle(true);
        datApplication::GetApp().GetToolManager().StartTool(new datPlaceImageTool(startDefaultTool));
    }

    void onStartExportImageToolPressed(datButton& button) {
        setToggleAllToolButtons(false);
        button.SetToggle(true);
        datApplication::GetApp().GetToolManager().StartTool(new datExportImageTool(startDefaultTool));
    }

    void onStartEditAttributesToolPressed(datButton& button) {
        setToggleAllToolButtons(false);
        button.SetToggle(true);
        datApplication::GetApp().GetToolManager().StartTool(new datEditAttributesTool());
    }


    void onDeleteSelectionPressed(datButton& button) {
        button.SetVisible(false);

        datRenderer& renderer = datApplication::GetApp().GetRenderer();

        std::set<datGeometry*> selection = renderer.GetSelectionSet().GetSelection();
        for (auto const& entry : selection) {
            renderer.RemoveGeometry(entry);
        }

        startDefaultTool();
    }

    void onDeleteButtonSelectionChanged() {
        const bool isVisible = 0 < datApplication::GetApp().GetRenderer().GetSelectionSet().GetSelection().size();
        auto pDeleteSelectionButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_DELETESELECTED);
        static_cast<datButton*>(pDeleteSelectionButton)->SetVisible(isVisible);
    }

    void onEditAttributesSelectionChanged() {
        const bool isVisible = 0 < datApplication::GetApp().GetRenderer().GetSelectionSet().GetSelection().size();
        auto pEditAttributesButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_EDITATTRIBUTES);
        static_cast<datButton*>(pEditAttributesButton)->SetVisible(isVisible);
    }

}; // end unnamed namespace


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
    pSelectToolButton->SetOnPressedCallback(onStartSelectToolPressed);
    pSelectToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("cursor.png"));
    pSelectToolButton->SetTooltip(datLocalization::SelectTool_Tooltip());
    pSelectToolButton->SetName(DAT_BUTTON_NAME_SELECT);
    mainView.AddView(pSelectToolButton);

    // Place polyline tool
    datButton* pPolylineToolButton = new datButton(10, 65, 40, 40, datButtonStyle::createForToolButton());
    pPolylineToolButton->SetOnPressedCallback(onStartPlacePolylineToolPressed);
    pPolylineToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("pencil.png"));
    pPolylineToolButton->SetTooltip(datLocalization::PlacePolylineTool_Tooltip());
    pPolylineToolButton->SetName(DAT_BUTTON_NAME_PLACEPOLYLINE);
    mainView.AddView(pPolylineToolButton);

    // Place text tool
    datButton* pWriteTextToolButton = new datButton(10, 110, 40, 40, datButtonStyle::createForToolButton());
    pWriteTextToolButton->SetOnPressedCallback(onStartPlaceTextToolPressed);
    pWriteTextToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("write_text.png"));
    pWriteTextToolButton->SetTooltip(datLocalization::PlaceTextTool_Tooltip());
    pWriteTextToolButton->SetName(DAT_BUTTON_NAME_PLACETEXT);
    mainView.AddView(pWriteTextToolButton);

    // Insert image tool
    datButton* pPlaceImageToolButton = new datButton(10, 155, 40, 40, datButtonStyle::createForToolButton());
    pPlaceImageToolButton->SetOnPressedCallback(onStartPlaceImageToolPressed);
    pPlaceImageToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("add_image.png"));
    pPlaceImageToolButton->SetTooltip(datLocalization::PlaceImageTool_Tooltip());
    pPlaceImageToolButton->SetName(DAT_BUTTON_NAME_PLACEIMAGE);
    mainView.AddView(pPlaceImageToolButton);

    // Export image tool
    datButton* pExportImageToolButton = new datButton(10, 200, 40, 40, datButtonStyle::createForToolButton());
    pExportImageToolButton->SetOnPressedCallback(onStartExportImageToolPressed);
    pExportImageToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("export_image.png"));
    pExportImageToolButton->SetTooltip(datLocalization::ExportImageTool_Tooltip());
    pExportImageToolButton->SetName(DAT_BUTTON_NAME_EXPORTIMAGE);
    mainView.AddView(pExportImageToolButton);

    // Delete selection
    datButton* pDeleteSelectionButton = new datButton(240, 20, 40, 40, datButtonStyle::createForToolButton());
    pDeleteSelectionButton->SetOnPressedCallback(onDeleteSelectionPressed);
    pDeleteSelectionButton->SetImage(datUtilities::LoadImageFromAssetsFolder("trash_can.png"));
    pDeleteSelectionButton->SetTooltip(datLocalization::DeleteSelectedGeometries());
    pDeleteSelectionButton->SetName(DAT_BUTTON_NAME_DELETESELECTED);
    mainView.AddView(pDeleteSelectionButton);
    pDeleteSelectionButton->SetVisible(false);
    ofAddListener(GetRenderer().GetSelectionSet().GetSelectionChangedEvent(), onDeleteButtonSelectionChanged);

    datButton* pEditAttributesToolButton = new datButton(285, 20, 40, 40, datButtonStyle::createForToolButton());
    pEditAttributesToolButton->SetOnPressedCallback(onStartEditAttributesToolPressed);
    pEditAttributesToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("palette.png"));
    pEditAttributesToolButton->SetTooltip(datLocalization::EditAttributesTool_Tooltip());
    pEditAttributesToolButton->SetName(DAT_BUTTON_NAME_EDITATTRIBUTES);
    mainView.AddView(pEditAttributesToolButton);
    pEditAttributesToolButton->SetVisible(false);
    ofAddListener(GetRenderer().GetSelectionSet().GetSelectionChangedEvent(), onEditAttributesSelectionChanged);

    startDefaultTool();
}


void datApplication::setup() {

    m_width = ofGetWidth();
    m_height = ofGetHeight();

    // Make sure we initialize managers
    GetToolManager();
    GetViewManager();
    GetRenderer();

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
        
        auto pTool = new datPlaceImageTool(startDefaultTool);
        pTool->SetImagesToPlace(images);
        datApplication::GetApp().GetToolManager().StartTool(pTool);
    }
}


void datApplication::draw() {

    T_Super::draw();

    GetRenderer().Render();
    GetViewManager().DoDraw();
    GetToolManager().DoDraw();
    GetRenderer().DrawCursorType();

	string comment =  
	"-Select tool: changer le curseur, changer la couleur de background, selectionner des elements dans la scene.\n"
	"-Place polyline tool: changer couleur et epaisseur de ligne, changer couleur de remplissage.\n"
	"-Place text tool: placer du texte dans la scene, changer la couleur du texte.\n"
	"-Place image tool: placer une image dans la scene.\n"
	"-Export image tool: sauver une photo de l'etat courant de la scene.";

	rect = getBitmapStringBoudingBox(comment);
	rect.x = 2;
	rect.y = ofGetWindowHeight()-75;
	ofSetColor(255,255,255,0);
	ofRect(rect.x, rect.y, rect.width, rect.height);
	ofSetColor(ofColor::black);
	ofDrawBitmapString(comment, rect.x, rect.y + 11);
	
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

ofRectangle datApplication::getBitmapStringBoudingBox(string text) {
	vector<string> lines = ofSplitString(text, "\n");
	int maxLineLength = 0;
	for (int i = 0; i < (int)lines.size(); i++) {
		// tabs are not rendered
		const string & line(lines[i]);
		int currentLineLength = 0;
		for (int j = 0; j < (int)line.size(); j++) {
			if (line[j] == '\t') {
				currentLineLength += 8 - (currentLineLength % 8);
			}
			else {
				currentLineLength++;
			}
		}
		maxLineLength = MAX(maxLineLength, currentLineLength);
	}

	int padding = 4;
	int fontSize = 8;
	float leading = 1.7;
	int height = lines.size() * fontSize * leading - 1;
	int width = maxLineLength * fontSize;
	return ofRectangle(0, 0, width, height);

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
