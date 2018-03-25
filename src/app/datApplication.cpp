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
#define DAT_BUTTON_NAME_PLACEMODEL "btn_placeModelTool"
#define DAT_BUTTON_NAME_PLACEIMAGE "btn_placeImageTool"
#define DAT_BUTTON_NAME_EXPORTIMAGE "btn_exportImageTool"
#define DAT_BUTTON_NAME_EDITATTRIBUTES "btn_editAttributesTool"
#define DAT_BUTTON_NAME_ADDTEXTURE "btn_addTextureTool"

#define DAT_BUTTON_NAME_DELETESELECTED "btn_deleteSelected"
#define DAT_BUTTON_NAME_UNDO "btn_undo"
#define DAT_BUTTON_NAME_REDO "btn_redo"


namespace {

    // Event listeners whenever user starts a tool.
    // This should toggle the button of the tool, and put all the others off
    void onSelectToolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_SELECT);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datSelectTool*>(&editTool));
    }

    void onPlacePolylineToolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_PLACEPOLYLINE);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datPlacePolylineTool*>(&editTool));
    }

    void onPlaceTextToolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_PLACETEXT);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datPlaceTextTool*>(&editTool));
    }

    void onPlaceModelToolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_PLACEMODEL);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datPlaceModelTool*>(&editTool));
    }

    void onPlaceImagetoolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_PLACEIMAGE);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datPlaceImageTool*>(&editTool));
    }

    void onExportImageToolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_EXPORTIMAGE);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datExportImageTool*>(&editTool));
    }

    void onEditAttributesToolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_EDITATTRIBUTES);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datEditAttributesTool*>(&editTool));
    }

    void onAddTextureToolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_ADDTEXTURE);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datEditAttributesTool*>(&editTool));
    }
    
    // On-pressed button events
    void onStartSelectToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datSelectTool());
    }

    void onStartPlacePolylineToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datPlacePolylineTool());
    }

    void onStartPlaceTextToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datPlaceTextTool());
    }

    void onStartPlaceModelToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datPlaceModelTool());
    }

    void onStartPlaceImageToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datPlaceImageTool());
    }

    void onStartExportImageToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datExportImageTool());
    }

    void onStartEditAttributesToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datEditAttributesTool());
    }

    void onStartAddTextureToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datAddTextureTool());
    }


    void onDeleteSelectionPressed(datButton& button) {

        datScene& scene = datApplication::GetApp().GetScene();
        std::set<datId> ids = scene.GetSelection();

        scene.ClearSelection();
        scene.DeleteMultipleGeometries(ids);
        datApplication::GetApp().SupplyDefaultEditTool();
    }

    // Called when the selection changes
    void onSelectionChanged() {

        datScene& scene = datApplication::GetApp().GetScene();
        std::set<datId> selectedIds = scene.GetSelection();
        const bool isVisible = !selectedIds.empty();

        auto pDeleteSelectionButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_DELETESELECTED);
        static_cast<datButton*>(pDeleteSelectionButton)->SetVisible(isVisible);

        auto pEditAttributesButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_EDITATTRIBUTES);
        static_cast<datButton*>(pEditAttributesButton)->SetVisible(isVisible);


        bool hasImage = false;
        for (auto const& id : selectedIds) {
            if (datGeometry::GeometryType::Image == scene.GetGeometry(id)->GetType()) {
                hasImage = true;
                break;
            }
        }

        auto pAddTextureButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_ADDTEXTURE);
        static_cast<datButton*>(pAddTextureButton)->SetVisible(isVisible && hasImage);
    }
    // Called when undo/redo status changed
    void onUndoRedoStatusChanged() {

        datScene& scene = datApplication::GetApp().GetScene();

        auto pUndoButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_UNDO);
        static_cast<datButton*>(pUndoButton)->SetEnabled(scene.CanUndo());

        auto pRedoButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_REDO);
        static_cast<datButton*>(pRedoButton)->SetEnabled(scene.CanRedo());
    }



    void onUndoPressed(datButton& button) {

        datScene& scene = datApplication::GetApp().GetScene();
        assert(scene.CanUndo());
        // To make sure we never interfere with any tool, start Select tool first
        datApplication::GetApp().SupplyDefaultEditTool();
        scene.ClearSelection();
        scene.Undo();
    }

    void onRedoPressed(datButton& button) {

        datScene& scene = datApplication::GetApp().GetScene();
        assert(scene.CanRedo());
        // To make sure we never interfere with any tool, start Select tool first
        datApplication::GetApp().SupplyDefaultEditTool();
        scene.ClearSelection();
        scene.Redo();
    }



}; // end unnamed namespace


datApplication::datApplication() {

}


datApplication::~datApplication() {

}


void datApplication::SetupUI() {
    ofDisableArbTex();
    datView& mainView = GetViewManager().GetMainView();
    mainView.setPosition(0, 0);
    mainView.setWidth(ofGetWidth());
    mainView.setHeight(ofGetHeight());

    // Select tool
    datButton* pSelectToolButton = new datButton(10, 20, 40, 40);
    ofAddListener(pSelectToolButton->GetOnPressedEvent(), onStartSelectToolPressed);
    pSelectToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("cursor.png"));
    pSelectToolButton->SetTooltip(datLocalization::SelectTool_Tooltip());
    pSelectToolButton->SetName(DAT_BUTTON_NAME_SELECT);
    mainView.AddView(pSelectToolButton);

    // Place polyline tool
    datButton* pPolylineToolButton = new datButton(10, 65, 40, 40);
    ofAddListener(pPolylineToolButton->GetOnPressedEvent(), onStartPlacePolylineToolPressed);
    pPolylineToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("pencil.png"));
    pPolylineToolButton->SetTooltip(datLocalization::PlacePolylineTool_Tooltip());
    pPolylineToolButton->SetName(DAT_BUTTON_NAME_PLACEPOLYLINE);
    mainView.AddView(pPolylineToolButton);

    // Place text tool
    datButton* pWriteTextToolButton = new datButton(10, 110, 40, 40);
    ofAddListener(pWriteTextToolButton->GetOnPressedEvent(), onStartPlaceTextToolPressed);
    pWriteTextToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("write_text.png"));
    pWriteTextToolButton->SetTooltip(datLocalization::PlaceTextTool_Tooltip());
    pWriteTextToolButton->SetName(DAT_BUTTON_NAME_PLACETEXT);
    mainView.AddView(pWriteTextToolButton);

    // Insert model tool
    datButton* pPlaceModelToolButton = new datButton(10, 155, 40, 40);
    ofAddListener(pPlaceModelToolButton->GetOnPressedEvent(), onStartPlaceModelToolPressed);
    pPlaceModelToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("add_model.png"));
    pPlaceModelToolButton->SetTooltip(datLocalization::PlaceModelTool_Tooltip());
    pPlaceModelToolButton->SetName(DAT_BUTTON_NAME_PLACEMODEL);
    mainView.AddView(pPlaceModelToolButton);

    // Insert image tool
    datButton* pPlaceImageToolButton = new datButton(10, 200, 40, 40);
    ofAddListener(pPlaceImageToolButton->GetOnPressedEvent(), onStartPlaceImageToolPressed);
    pPlaceImageToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("add_image.png"));
    pPlaceImageToolButton->SetTooltip(datLocalization::PlaceImageTool_Tooltip());
    pPlaceImageToolButton->SetName(DAT_BUTTON_NAME_PLACEIMAGE);
    mainView.AddView(pPlaceImageToolButton);

    // Export image tool
    datButton* pExportImageToolButton = new datButton(10, 245, 40, 40);
    ofAddListener(pExportImageToolButton->GetOnPressedEvent(), onStartExportImageToolPressed);
    pExportImageToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("export_image.png"));
    pExportImageToolButton->SetTooltip(datLocalization::ExportImageTool_Tooltip());
    pExportImageToolButton->SetName(DAT_BUTTON_NAME_EXPORTIMAGE);
    mainView.AddView(pExportImageToolButton);

    // Undo button
    datButton* pUndoButton = new datButton(55, 20, 40, 40);
    ofAddListener(pUndoButton->GetOnPressedEvent(), onUndoPressed);
    pUndoButton->SetImage(datUtilities::LoadImageFromAssetsFolder("undo.png"));
    pUndoButton->SetTooltip(datLocalization::Undo());
    pUndoButton->SetName(DAT_BUTTON_NAME_UNDO);
    mainView.AddView(pUndoButton);
    pUndoButton->SetEnabled(false);

    // Redo button
    datButton* pRedoButton = new datButton(100, 20, 40, 40);
    ofAddListener(pRedoButton->GetOnPressedEvent(), onRedoPressed);
    pRedoButton->SetImage(datUtilities::LoadImageFromAssetsFolder("redo.png"));
    pRedoButton->SetTooltip(datLocalization::Redo());
    pRedoButton->SetName(DAT_BUTTON_NAME_REDO);
    mainView.AddView(pRedoButton);
    pRedoButton->SetEnabled(false);

    // Delete selection
    datButton* pDeleteSelectionButton = new datButton(280, 20, 40, 40);
    ofAddListener(pDeleteSelectionButton->GetOnPressedEvent(), onDeleteSelectionPressed);
    pDeleteSelectionButton->SetImage(datUtilities::LoadImageFromAssetsFolder("trash_can.png"));
    pDeleteSelectionButton->SetTooltip(datLocalization::DeleteSelectedGeometries());
    pDeleteSelectionButton->SetName(DAT_BUTTON_NAME_DELETESELECTED);
    mainView.AddView(pDeleteSelectionButton);
    pDeleteSelectionButton->SetVisible(false);

    // Edit attributes
    datButton* pEditAttributesToolButton = new datButton(325, 20, 40, 40);
    ofAddListener(pEditAttributesToolButton->GetOnPressedEvent(), onStartEditAttributesToolPressed);
    pEditAttributesToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("palette.png"));
    pEditAttributesToolButton->SetTooltip(datLocalization::EditAttributesTool_Tooltip());
    pEditAttributesToolButton->SetName(DAT_BUTTON_NAME_EDITATTRIBUTES);
    mainView.AddView(pEditAttributesToolButton);
    pEditAttributesToolButton->SetVisible(false);

    // Add texture
    datButton* pAddtextureToolButton = new datButton(370, 20, 40, 40);
    ofAddListener(pAddtextureToolButton->GetOnPressedEvent(), onStartAddTextureToolPressed);
    pAddtextureToolButton->SetImage(datUtilities::LoadImageFromAssetsFolder("add_image.png"));
    pAddtextureToolButton->SetTooltip(datLocalization::AddTextureTool_Tooltip());
    pAddtextureToolButton->SetName(DAT_BUTTON_NAME_ADDTEXTURE);
    mainView.AddView(pAddtextureToolButton);
    pAddtextureToolButton->SetVisible(false);

    // Register all events
    ofAddListener(GetScene().GetOnSelectionChangedEvent(), onSelectionChanged);
    ofAddListener(GetScene().GetOnUndoRedoStatusChangedEvent(), onUndoRedoStatusChanged);

    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onSelectToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlacePolylineToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlaceTextToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlaceModelToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlaceImagetoolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onExportImageToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onEditAttributesToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onAddTextureToolStarted);
    
    ofAddListener(GetToolManager().GetOnSupplyEditToolEvent(), this, &datApplication::SupplyDefaultEditTool);
    SupplyDefaultEditTool();
}


void datApplication::setup() {

    m_width = ofGetWidth();
    m_height = ofGetHeight();

    // Initialize common resources
    GetScene();
    GetToolManager();
    GetViewManager();
    GetRenderer();

    SetupUI();
}


void datApplication::ClampEvent(ofMouseEventArgs& ev) const {
    ev.x = CLAMP(ev.x, 1, m_width);
    ev.y = CLAMP(ev.y, 1, m_height);
}


bool datApplication::SendMouseEvent(ofMouseEventArgs& ev) {

    ClampEvent(ev);
    size_t viewportIdx = GetRenderer().GetViewportIndex(ev);
    datViewport& vp = GetRenderer().GetViewport(viewportIdx);

//&&AG needswork. some kind of projection to get a valid 3d point

    // Calculate point in app coordinates
    float xApp = ofGetWidth() * (ev.x - vp.rect.x) / vp.rect.width;
    float yApp = ofGetHeight() * (ev.y - vp.rect.y) / vp.rect.height;

    ofPoint ray[2];
    // Define ray in screen space
    ray[0] = ofVec3f(xApp, yApp, -1);
    ray[1] = ofVec3f(xApp, yApp, 1);

    // Transform ray into world space
    ray[0] = vp.camera.screenToWorld(ray[0]);
    ray[1] = vp.camera.screenToWorld(ray[1]);

    ofPoint vec = ray[1] - ray[0];
    vec.normalize();
    ofPoint worldPoint = ray[0] + (vec * ray[0].z);

    datMouseEvent datEvent(ev);
    datEvent.InitEvent(ev, worldPoint, ofGetKeyPressed(OF_KEY_CONTROL), ofGetKeyPressed(OF_KEY_SHIFT), ofGetKeyPressed(OF_KEY_ALT));


    if (ofMouseEventArgs::Type::Pressed == ev.type && ev.button == OF_MOUSE_BUTTON_MIDDLE) {
        GetToolManager().StartTool(new datViewManipTool(datEvent));
        return true;
    }

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
        auto pTool = new datPlaceImageTool();
        pTool->SetImagesToPlace(images);
        datApplication::GetApp().GetToolManager().StartTool(pTool);
    }

    // Try as ofxAssimpModel
    std::vector<ofxAssimpModelLoader> models;
    for (auto const& filePath : ev.files) {
        ofxAssimpModelLoader model;
        if (model.loadModel(filePath)) {
            models.push_back(std::move(model));
        }
    }

    if (!models.empty()) {
        auto pTool = new datPlaceModelTool();
        pTool->SetModelsToPlace(std::move(models));
        datApplication::GetApp().GetToolManager().StartTool(pTool);
    }
}


void datApplication::draw() {

    T_Super::draw();

    GetRenderer().Render();
    GetToolManager().DoDraw(GetRenderer());
    GetViewManager().DoDraw(GetRenderer());

    string comment =  
    "-Select tool: changer le curseur, changer la couleur de background, selectionner des elements dans la scene, 'Bounding Box'.\n"
    "-Place polyline tool: placer une ligne, changer couleur et epaisseur de ligne, changer couleur de remplissage.\n"
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


void datApplication::mouseScrolled(ofMouseEventArgs & mouse) {

    size_t viewportIdx = GetRenderer().GetViewportIndex(mouse);
    datViewport& vp = GetRenderer().GetViewport(viewportIdx);
    
    float zOffset = -mouse.scrollY * 120.0;

    ofPoint offset = vp.camera.getZAxis() * zOffset;
    vp.camera.move(offset);
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

    GetRenderer().ResizeViewports();
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


datScene& datApplication::GetScene() {
    if (nullptr == m_scene)
        m_scene = std::make_shared<datScene>();

    return *m_scene;
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
    if (nullptr == m_renderer) {
        m_renderer.reset(new datRenderer(*m_scene));
    }

    return *m_renderer;
}


void datApplication::SupplyDefaultEditTool() {
    GetToolManager().StartTool(new datSelectTool());
}


datApplication& datApplication::GetApp() {

    ofBaseApp* pApp = ofGetAppPtr();
    assert(nullptr != pApp);

    assert(nullptr != dynamic_cast<datApplication*>(pApp));
    return *static_cast<datApplication*>(pApp);
}
