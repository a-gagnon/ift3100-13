//=======================================================================================
// datPlaceModelTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceModelTool.h"

USING_DAT_NAMESPACE

datPlaceModelTool::datPlaceModelTool() {

}


datPlaceModelTool::~datPlaceModelTool() {

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
    }
}


void datPlaceModelTool::onExitTool() {
    GetRenderer().ClearTransients();
}


void datPlaceModelTool::updateTransient(datMouseEvent const& ev) {

    ofNode node;
    node.setPosition(ev.GetWorldPoint());
    node.setGlobalOrientation(ev.GetViewport().camera.getGlobalOrientation());

    if (nullptr == m_transient) {
        m_transient = datAssimpModel::Create(m_modelsToPlace.back(), node);
        GetRenderer().AddTransient(m_transient.get());
    }
    else {
        m_transient->SetNode(node);
    }
}



void datPlaceModelTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (!m_modelsToPlace.empty()) {

        ofNode node;
        node.setPosition(ev.GetWorldPoint());
        node.setGlobalOrientation(ev.GetViewport().camera.getGlobalOrientation());

        std::unique_ptr<datAssimpModel> model = datAssimpModel::Create(m_modelsToPlace.back(), node);
        GetRenderer().GetScene().InsertElement(std::move(model));

        m_modelsToPlace.pop_back();

        if (!m_modelsToPlace.empty()) {
            GetRenderer().ClearTransients();
            m_transient = nullptr;
            updateTransient(ev);
        }
        else
            _ExitTool();
    }
}


void datPlaceModelTool::onRightMouseButtonDown(datMouseEvent const& ev) {

    if (!m_modelsToPlace.empty()) {

        m_modelsToPlace.pop_back();

        if (!m_modelsToPlace.empty()) {
            GetRenderer().ClearTransients();
            m_transient = nullptr;
            updateTransient(ev);
        }
        else
            _ExitTool();
    }
}


void datPlaceModelTool::onMouseMotion(datMouseEvent const& ev) {

    if (!m_modelsToPlace.empty())
        updateTransient(ev);
    else
        _ExitTool();
}


void datPlaceModelTool::onDraw() {

    if (m_modelsToPlace.empty()) {
        _ExitTool();
        return;
    }
}

