//=======================================================================================
// datPlaceImageTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceImageTool.h"

USING_DAT_NAMESPACE

datPlaceImageTool::datPlaceImageTool(datPlaceImageDoneCallback callback) :
    m_pCallbackFunction(callback),
    m_position(0, 0, 0) {
    assert(nullptr != m_pCallbackFunction);
}


datPlaceImageTool::~datPlaceImageTool() {

}


void datPlaceImageTool::UpdateParameters() {

    assert(!m_imagesToPlace.empty());
    ofImage& img = m_imagesToPlace.back();
    m_paramWidth.set("width", img.getWidth(), 0.0, 2.0 * img.getWidth());
    m_paramHeight.set("heigth", img.getHeight(), 0.0, 2.0 * img.getHeight());
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

        // Still empty. exit tool
        if (m_imagesToPlace.empty()) {
            m_pCallbackFunction();
            return;
        }
    }

    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_paramWidth);
    m_panel.add(m_paramHeight);
    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);
    UpdateParameters();
}


void datPlaceImageTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (!m_imagesToPlace.empty()) {

        ofImage const& image = m_imagesToPlace.back();
        const ofVec2f position = ev;
        datImage wrappedImage(image, position, m_paramWidth, m_paramHeight);

        std::unique_ptr<datGeometry> geometry = datGeometry::Create(wrappedImage);
        GetRenderer().AddGeometry(std::move(geometry));

        m_imagesToPlace.pop_back();

        if (!m_imagesToPlace.empty())
            UpdateParameters();
        else
            m_pCallbackFunction();
    }
}


void datPlaceImageTool::onRightMouseButtonDown(datMouseEvent const& ev) {

    if (!m_imagesToPlace.empty()) {

        m_imagesToPlace.pop_back();

        if (!m_imagesToPlace.empty())
            UpdateParameters();
        else
            m_pCallbackFunction();
    }
}


void datPlaceImageTool::onMouseMotion(datMouseEvent const& ev) {
    m_position = ev;
}


void datPlaceImageTool::onDraw() {

    if (!m_imagesToPlace.empty()) {

        const ofColor currentColor = ofGetStyle().color;

        // Copy current color and add some transparency
        ofColor color = currentColor;
        color.a = 128;
        ofSetColor(color);

        // Draw image using original size
        ofImage const& image = m_imagesToPlace.back();
        image.draw(m_position.x, m_position.y, m_paramWidth, m_paramHeight);

        // Put back original color
        ofSetColor(currentColor);
    }

    m_panel.draw();
}

