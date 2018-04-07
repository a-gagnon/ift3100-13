//=======================================================================================
// datPlaceImageTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceImageTool.h"

USING_DAT_NAMESPACE

datPlaceImageTool::datPlaceImageTool() {
}


datPlaceImageTool::~datPlaceImageTool() {

}


void datPlaceImageTool::onStartTool() {

    if (m_imagesToPlace.empty()) {

        // Open a file dialog and let the user choose a image file
        std::string filePath;
        if (datUtilities::OpenFileDialog(filePath, true/*fileMustExist*/)) {

            ofImage image;
            if (image.load(filePath))
                m_imagesToPlace.push_back(image);
        }
    }

    if (!m_imagesToPlace.empty()) {
        m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
        m_panel.add(m_paramWidth);
        m_panel.add(m_paramHeight);
        m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);
        updateParameters();

        m_paramWidth.addListener(this, &datPlaceImageTool::onWidthChanged);
        m_paramHeight.addListener(this, &datPlaceImageTool::onHeightChanged);
    }
}


void datPlaceImageTool::onExitTool() {
    m_paramWidth.removeListener(this, &datPlaceImageTool::onWidthChanged);
    m_paramHeight.removeListener(this, &datPlaceImageTool::onHeightChanged);

    GetRenderer().ClearTransients();
    m_transient = nullptr;
}



void datPlaceImageTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (!m_imagesToPlace.empty()) {

        ofNode node;
        node.setPosition(ev.GetWorldPoint());
        node.setOrientation(ev.GetViewport().camera.getGlobalOrientation());

        std::unique_ptr<datImage> image = datImage::Create(m_imagesToPlace.back(), m_paramWidth, m_paramHeight, node);
        GetRenderer().GetScene().InsertElement(std::move(image));

        m_imagesToPlace.pop_back();

        if (!m_imagesToPlace.empty()) {
            GetRenderer().ClearTransients();
            m_transient = nullptr;
            updateParameters();
            updateTransient();
        }
        else
            _ExitTool();
    }
}


void datPlaceImageTool::onRightMouseButtonDown(datMouseEvent const& ev) {

    if (!m_imagesToPlace.empty()) {

        m_imagesToPlace.pop_back();

        if (!m_imagesToPlace.empty()) {
            GetRenderer().ClearTransients();
            m_transient = nullptr;
            updateParameters();
            updateTransient();
        }
        else
            _ExitTool();
    }
}


void datPlaceImageTool::onMouseMotion(datMouseEvent const& ev) {
    m_lastMouseEvent.reset(new datMouseEvent(ev));
    updateTransient();
}

void datPlaceImageTool::updateParameters() {

    assert(!m_imagesToPlace.empty());
    ofImage& img = m_imagesToPlace.back();
    m_paramWidth.set("width", img.getWidth(), 0.0, 2.0 * img.getWidth());
    m_paramHeight.set("heigth", img.getHeight(), 0.0, 2.0 * img.getHeight());
}

void datPlaceImageTool::updateTransient() {

    if (nullptr == m_lastMouseEvent || m_imagesToPlace.empty())
        return;

    ofNode node;
    node.setPosition(m_lastMouseEvent->GetWorldPoint());
    node.setOrientation(m_lastMouseEvent->GetViewport().camera.getGlobalOrientation());

    if (nullptr == m_transient) {
        m_transient = datImage::Create(m_imagesToPlace.back(), m_paramWidth, m_paramHeight, node);
        GetRenderer().AddTransient(m_transient.get());
    }

    m_transient->SetNode(node);
    m_transient->SetWidth(m_paramWidth);
    m_transient->SetHeight(m_paramHeight);
}

void datPlaceImageTool::onDraw() {

    if (m_imagesToPlace.empty()) {
        _ExitTool();
        return;
    }

    m_panel.draw();
}

