//=======================================================================================
// datPlaceModelTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceModelTool.h"

USING_DAT_NAMESPACE

datPlaceModelTool::datPlaceModelTool() :
    m_position(0, 0, 0) {
}


datPlaceModelTool::~datPlaceModelTool() {

}


void datPlaceModelTool::UpdateParameters() {

    assert(!m_modelsToPlace.empty());
    ofxAssimpModelLoader const& model = m_modelsToPlace.back();
}


void datPlaceModelTool::onStartTool() {

    if (m_modelsToPlace.empty()) {

        // Open a file dialog and let the user choose a image file
        std::string filePath;
        if (datUtilities::OpenFileDialog(filePath, true/*fileMustExist*/)) {

            ofxAssimpModelLoader model;
            if (model.loadModel(filePath))
                m_modelsToPlace.push_back(std::move(model));
        }

        // Still empty. exit tool
        if (m_modelsToPlace.empty()) {
            _ExitTool();
            return;
        }
    }

    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);
    UpdateParameters();
}


void datPlaceModelTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (!m_modelsToPlace.empty()) {

        ofxAssimpModelLoader const& model = m_modelsToPlace.back();
        const ofVec2f position = ev;

        std::unique_ptr<datGeometry> geometry = datGeometry::Create(model);
        GetRenderer().AddGeometry(std::move(geometry));

        m_modelsToPlace.pop_back();

        if (!m_modelsToPlace.empty())
            UpdateParameters();
        else
            _ExitTool();
    }
}


void datPlaceModelTool::onRightMouseButtonDown(datMouseEvent const& ev) {

    if (!m_modelsToPlace.empty()) {

        m_modelsToPlace.pop_back();

        if (!m_modelsToPlace.empty())
            UpdateParameters();
        else
            _ExitTool();
    }
}


void datPlaceModelTool::onMouseMotion(datMouseEvent const& ev) {
    m_position = ev;
}


void datPlaceModelTool::onDraw() {

    if (!m_modelsToPlace.empty()) {

        const ofColor currentColor = ofGetStyle().color;

        // Copy current color and add some transparency
        ofColor color = currentColor;
        color.a = 128;
        ofSetColor(color);

        // Draw image using original size
        ofxAssimpModelLoader& model = m_modelsToPlace.back();
        model.setPosition(m_position.x, m_position.y, m_position.z);
        model.draw(ofPolyRenderMode::OF_MESH_FILL);

        // Put back original color
        ofSetColor(currentColor);
    }

    m_panel.draw();
}

