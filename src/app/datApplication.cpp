//=======================================================================================
// datApplication.cpp
// IFT3100-13
//=======================================================================================
#include "datApplication.h"

USING_DAT_NAMESPACE

namespace {

void startSelectTool()          { datApplication::GetApp().GetToolManager().StartTool(new datSelectTool()); }
void startPlacePolylineTool()   { datApplication::GetApp().GetToolManager().StartTool(new datPlacePolylineTool()); }
void startPlaceTextTool()       { datApplication::GetApp().GetToolManager().StartTool(new datPlaceTextTool()); }

}; // end unnamed namespaceters


datApplication::datApplication() {

}


datApplication::~datApplication() {

}


void datApplication::CreateToolbar() {

    // Select tool
    datButton* pSelectToolButton = new datButton(10, 20, 40, 40, datButtonStyle::createForToolButton());
    pSelectToolButton->SetOnPressedCallback(startSelectTool);
    pSelectToolButton->SetImage(LoadImageFromAssetsFolder("cursor.png"));
    pSelectToolButton->SetTooltip("Select tool");
    GetInputManager().AddView(pSelectToolButton);

    // Place polyline tool
    datButton* pPolylineToolButton = new datButton(10, 65, 40, 40, datButtonStyle::createForToolButton());
    pPolylineToolButton->SetOnPressedCallback(startPlacePolylineTool);
    pPolylineToolButton->SetImage(LoadImageFromAssetsFolder("pencil.png"));
    pPolylineToolButton->SetTooltip("Place polyline tool");
    GetInputManager().AddView(pPolylineToolButton);

    // Place text tool
    datButton* pWriteTextToolButton = new datButton(10, 110, 40, 40, datButtonStyle::createForToolButton());
    pWriteTextToolButton->SetOnPressedCallback(startPlaceTextTool);
    pWriteTextToolButton->SetImage(LoadImageFromAssetsFolder("write_text.png"));
    pWriteTextToolButton->SetTooltip("Place text tool");
    GetInputManager().AddView(pWriteTextToolButton);
}


void datApplication::setup() {
    CreateToolbar();

}



void datApplication::dragged(ofDragInfo& ev) {

	if (ev.files.size() > 0) {
		dragPt = ev.position;

		draggedImages.assign(ev.files.size(), ofImage());
		for (unsigned int k = 0; k < ev.files.size(); k++) {
			draggedImages[k].load(ev.files[k]);
		}
	}

}
bool datApplication::SendMouseEvent(ofMouseEventArgs& ev) {

    if (GetInputManager().SendMouseEvent(ev))
        return true;

    if (GetToolManager().SendMouseEvent(ev))
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
    GetToolManager().DoDraw();
	ofSetColor(255);

	float dx = dragPt.x;
	float dy = dragPt.y;

	for (unsigned int k = 0; k < draggedImages.size(); k++) {
		draggedImages[k].draw(dx, dy);
		dy += draggedImages[k].getHeight() + 10;
	}

	ofSetColor(0);
	ofDrawBitmapString("drag here", 10, 20);

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


void datApplication::keyPressed(ofKeyEventArgs& ev) {
	if (!SendKeyEvent(ev)) 
		T_Super::keyPressed(ev);

}

void datApplication::exit() {
	img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	img.save("screenshot.png");
}


datToolManager& datApplication::GetToolManager() {

    if (nullptr == m_toolManager)
        m_toolManager.reset(new datToolManager());

    return *m_toolManager;
}


datInputManager& datApplication::GetInputManager() {

    if (nullptr == m_inputManager)
        m_inputManager.reset(new datInputManager());

    return *m_inputManager;
}


datApplication& datApplication::GetApp() {

    ofBaseApp* pApp = ofGetAppPtr();
    assert(nullptr != pApp);

    assert(nullptr != dynamic_cast<datApplication*>(pApp));
    return *static_cast<datApplication*>(pApp);
}
