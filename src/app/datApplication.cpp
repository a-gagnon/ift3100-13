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
#define DAT_BUTTON_NAME_PLACELIGHT "btn_placeLightTool"
#define DAT_BUTTON_NAME_PLACEPARAMETRICCURVE "btn_PlaceParametricCurve"
#define DAT_BUTTON_NAME_GENERATESCENERAYTRACING "btn_GenerateSceneRayTracing"

#define DAT_BUTTON_NAME_DELETESELECTED "btn_deleteSelected"
#define DAT_BUTTON_NAME_UNDO "btn_undo"
#define DAT_BUTTON_NAME_REDO "btn_redo"
#define DAT_BUTTON_NAME_TOGGLELIGHTING "btn_ToggleLighting"
#define DAT_BUTTON_NAME_VIEWPORTS "btn_Viewports"
#define DAT_BUTTON_NAME_BBOX "btn_BoundingBox"
#define DAT_BUTTON_NAME_ORTHO_CAM "btn_Orthographic"


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

    void onPlaceParametricCurveToolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_PLACEPARAMETRICCURVE);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datPlaceParametricCurveTool*>(&editTool));
    }

    void onPlaceLightToolStarted(datEditTool& editTool) {
        datView* pView = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_PLACELIGHT);
        static_cast<datButton*>(pView)->SetToggle(nullptr != dynamic_cast<datPlaceLightTool*>(&editTool));
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

    void onStartPlaceParametricCurveToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datPlaceParametricCurveTool());
    }

    void onStartPlaceLightToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datPlaceLightTool());
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

    void onGenerateSceneRayTracingPressed(datButton& button) {

        if (!datUtilities::ExecuteRayTracer()) {
            ofLog() << "Failed to start raytracer program";
            return;
        }

        if (!datUtilities::OpenWithDefaultProgram("/raytracer/result.bmp")) { //&&AG todo use the output path of the raytracer
            ofLog() << "Failed to start default program to open raytracer output image";
            return;
        }
    }

    void onStartEditAttributesToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datEditAttributesTool());
    }

    void onStartAddTextureToolPressed(datButton& button) {
        datApplication::GetApp().GetToolManager().StartTool(new datAddTextureTool());
    }

    void onToggleLightingPressed(datButton& button) {
        datApplication::GetApp().GetRenderer().SetLighting(!button.IsToggled());
        button.SetToggle(!button.IsToggled());
    }

    void onViewportsButtonPressed(datButton& button) {
        datApplication::GetApp().GetRenderer().SetUseTwoViewports(!button.IsToggled());
        button.SetToggle(!button.IsToggled());
    }

    void onBoundingBoxButtonPressed(datButton& button) {
        datApplication::GetApp().GetRenderer().SetDrawBoundingBox(!button.IsToggled());
        button.SetToggle(!button.IsToggled());
    }

    void onOrthoCamButtonPressed(datButton& button) {
        datApplication::GetApp().GetRenderer().SetUseOrthoCamera(!button.IsToggled());
        button.SetToggle(!button.IsToggled());
    }


    void onDeleteSelectionPressed(datButton& button) {

        datScene& scene = datApplication::GetApp().GetScene();
        std::set<datId> ids = scene.GetSelection();

        scene.ClearSelection();
        scene.DeleteElements(ids);
        datApplication::GetApp().SupplyDefaultEditTool();
    }

    // Called when the selection changes
    void onSelectionChanged() {

        datScene& scene = datApplication::GetApp().GetScene();
        std::set<datId> selectedIds = scene.GetSelection();
        const bool isEnabled = !selectedIds.empty();

        auto pDeleteSelectionButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_DELETESELECTED);
        static_cast<datButton*>(pDeleteSelectionButton)->SetEnabled(isEnabled);

        auto pEditAttributesButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_EDITATTRIBUTES);
        static_cast<datButton*>(pEditAttributesButton)->SetEnabled(isEnabled);


        bool hasImage = false;
        for (auto const& id : selectedIds) {
            if (nullptr != scene.GetElement(id)->ToImageElement()) {
                hasImage = true;
                break;
            }
        }

        auto pAddTextureButton = datApplication::GetApp().GetViewManager().GetViewByName(DAT_BUTTON_NAME_ADDTEXTURE);
        static_cast<datButton*>(pAddTextureButton)->SetVisible(isEnabled && hasImage);
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
    ofSetColor(120, 120, 120);

    datView& mainView = GetViewManager().GetMainView();
    mainView.setPosition(0, 0);
    mainView.setWidth(ofGetWidth());
    mainView.setHeight(ofGetHeight());

    // Menu for tools (always present)
    datMenu* pToolMenu = new datMenu(10, 10, datMenu::Layout::Vertical);
    mainView.AddView(pToolMenu);

    datButton* pSelectToolButton = pToolMenu->AddToolButton(DAT_BUTTON_NAME_SELECT, datLocalization::SelectTool_Tooltip(), "cursor.png");
    ofAddListener(pSelectToolButton->GetOnPressedEvent(), onStartSelectToolPressed);

    datButton* pPolylineToolButton = pToolMenu->AddToolButton(DAT_BUTTON_NAME_PLACEPOLYLINE, datLocalization::PlacePolylineTool_Tooltip(), "pencil.png");
    ofAddListener(pPolylineToolButton->GetOnPressedEvent(), onStartPlacePolylineToolPressed);

    datButton* pParametricCurveToolButton = pToolMenu->AddToolButton(DAT_BUTTON_NAME_PLACEPARAMETRICCURVE, datLocalization::PlaceParametricCurve_Tooltip(), "scribble.png");
    ofAddListener(pParametricCurveToolButton->GetOnPressedEvent(), onStartPlaceParametricCurveToolPressed);

    datButton* pPlaceLightToolButton = pToolMenu->AddToolButton(DAT_BUTTON_NAME_PLACELIGHT, datLocalization::PlaceLightTool_Tooltip(), "add_light.png");
    ofAddListener(pPlaceLightToolButton->GetOnPressedEvent(), onStartPlaceLightToolPressed);

    datButton* pWriteTextToolButton = pToolMenu->AddToolButton(DAT_BUTTON_NAME_PLACETEXT, datLocalization::PlaceTextTool_Tooltip(), "write_text.png");
    ofAddListener(pWriteTextToolButton->GetOnPressedEvent(), onStartPlaceTextToolPressed);

    datButton* pPlaceModelToolButton = pToolMenu->AddToolButton(DAT_BUTTON_NAME_PLACEMODEL, datLocalization::PlaceModelTool_Tooltip(), "add_model.png");
    ofAddListener(pPlaceModelToolButton->GetOnPressedEvent(), onStartPlaceModelToolPressed);

    datButton* pPlaceImageToolButton = pToolMenu->AddToolButton(DAT_BUTTON_NAME_PLACEIMAGE, datLocalization::PlaceImageTool_Tooltip(), "add_image.png");
    ofAddListener(pPlaceImageToolButton->GetOnPressedEvent(), onStartPlaceImageToolPressed);

    datButton* pExportImageToolButton = pToolMenu->AddToolButton(DAT_BUTTON_NAME_EXPORTIMAGE, datLocalization::ExportImageTool_Tooltip(), "export_image.png");
    ofAddListener(pExportImageToolButton->GetOnPressedEvent(), onStartExportImageToolPressed);

    datButton* pGenerateSceneRayTracing = pToolMenu->AddToolButton(DAT_BUTTON_NAME_GENERATESCENERAYTRACING, datLocalization::GenerateSceneRayTracing_Tooltip(), "project.png");
    ofAddListener(pGenerateSceneRayTracing->GetOnPressedEvent(), onGenerateSceneRayTracingPressed);

    // Menu for contextual actions/tools
    datMenu* pContextMenu = new datMenu(60, 10, datMenu::Layout::Horizontal);
    mainView.AddView(pContextMenu);

    datButton* pLightingButton = pContextMenu->AddToolButton(DAT_BUTTON_NAME_TOGGLELIGHTING, datLocalization::ToggleLighting_Tooltip(), "lightbulb.png");
    ofAddListener(pLightingButton->GetOnPressedEvent(), onToggleLightingPressed);
    pLightingButton->SetToggle(true);

    datButton* pViewportsButton = pContextMenu->AddToolButton(DAT_BUTTON_NAME_VIEWPORTS, datLocalization::TwoViewports_Tooltip(), "screen.png");
    ofAddListener(pViewportsButton->GetOnPressedEvent(), onViewportsButtonPressed);

    datButton* pBoundingBoxButton = pContextMenu->AddToolButton(DAT_BUTTON_NAME_BBOX, datLocalization::BoundingBox_ToolTip(), "bounding_box.png");
    ofAddListener(pBoundingBoxButton->GetOnPressedEvent(), onBoundingBoxButtonPressed);

    datButton* pOrthoCamButton = pContextMenu->AddToolButton(DAT_BUTTON_NAME_ORTHO_CAM, datLocalization::Orthographic_Tooltip(), "orthographic.png");
    ofAddListener(pOrthoCamButton->GetOnPressedEvent(), onOrthoCamButtonPressed);

    datButton* pUndoButton = pContextMenu->AddToolButton(DAT_BUTTON_NAME_UNDO, datLocalization::Undo(), "undo.png");
    ofAddListener(pUndoButton->GetOnPressedEvent(), onUndoPressed);
    pUndoButton->SetEnabled(false);

    datButton* pRedoButton = pContextMenu->AddToolButton(DAT_BUTTON_NAME_REDO, datLocalization::Redo(), "redo.png");
    ofAddListener(pRedoButton->GetOnPressedEvent(), onRedoPressed);
    pRedoButton->SetEnabled(false);

    datButton* pDeleteButton = pContextMenu->AddToolButton(DAT_BUTTON_NAME_DELETESELECTED, datLocalization::DeleteSelectedGeometries(), "trash_can.png");
    ofAddListener(pDeleteButton->GetOnPressedEvent(), onDeleteSelectionPressed);
    pDeleteButton->SetEnabled(false);

    datButton* pEditAttributes = pContextMenu->AddToolButton(DAT_BUTTON_NAME_EDITATTRIBUTES, datLocalization::EditAttributesTool_Tooltip(), "palette.png");
    ofAddListener(pEditAttributes->GetOnPressedEvent(), onStartEditAttributesToolPressed);
    pEditAttributes->SetEnabled(false);

    datButton* pAddTexture = pContextMenu->AddToolButton(DAT_BUTTON_NAME_ADDTEXTURE, datLocalization::AddTextureTool_Tooltip(), "add_image.png");
    ofAddListener(pAddTexture->GetOnPressedEvent(), onStartAddTextureToolPressed);
    pAddTexture->SetEnabled(false);

    // Register all events
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onSelectToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlacePolylineToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlaceParametricCurveToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlaceLightToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlaceTextToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlaceModelToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onPlaceImagetoolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onExportImageToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onEditAttributesToolStarted);
    ofAddListener(GetToolManager().GetOnEditToolStartedEvent(), onAddTextureToolStarted);

    ofAddListener(GetScene().GetOnSelectionChangedEvent(), onSelectionChanged);
    ofAddListener(GetScene().GetOnUndoRedoStatusChangedEvent(), onUndoRedoStatusChanged);
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

    // Calculate point in app coordinates

    // Define ray in screen space, with NDC z
    ofPoint ray[2];
    ray[0] = ofVec3f(ev.x, ev.y, -1);
    ray[1] = ofVec3f(ev.x, ev.y, 1);

    // Transform ray into world space
    ray[0] = vp.camera.screenToWorld(ray[0], vp.rect);
    ray[1] = vp.camera.screenToWorld(ray[1], vp.rect);

    ofPoint worldPoint = vp.camera.screenToWorld(ofVec3f(ev.x, ev.y, 0.9), vp.rect);

    datMouseEvent datEvent(ev);
    datEvent.InitEvent(vp, ev, worldPoint, ofGetKeyPressed(OF_KEY_CONTROL), ofGetKeyPressed(OF_KEY_SHIFT), ofGetKeyPressed(OF_KEY_ALT));


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
