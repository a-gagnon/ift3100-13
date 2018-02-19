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


void datPlaceImageTool::onStartTool() {

    if (!m_imagesToPlace.empty())
        return;

    // Open a file dialog and let the user choose a image file
    std::string filePath;
    if (datUtilities::OpenFileDialog(filePath, true/*fileMustExist*/)) {

        ofImage image;
        if (image.load(filePath))
            m_imagesToPlace.push_back(image);
    }

    // Still empty. exit tool
    if (m_imagesToPlace.empty() && nullptr != m_pCallbackFunction)
        m_pCallbackFunction();
}


void datPlaceImageTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (!m_imagesToPlace.empty()) {

        ofImage const& image = m_imagesToPlace.back();
        const ofVec2f position = ev;
        const uint32_t width = static_cast<uint32_t>(image.getWidth());
        const uint32_t height = static_cast<uint32_t>(image.getHeight());
        datImage wrappedImage(image, position, width, height);
        std::unique_ptr<datGeometry> geometry = datGeometry::Create(wrappedImage);

        datRenderer::GetActiveRenderer().addGeometry(geometry);
        m_imagesToPlace.pop_back();

        if (m_imagesToPlace.empty() && nullptr != m_pCallbackFunction)
            m_pCallbackFunction();
    }
}


void datPlaceImageTool::onRightMouseButtonDown(datMouseEvent const& ev) {

    if (!m_imagesToPlace.empty()) {

        m_imagesToPlace.pop_back();

        if (m_imagesToPlace.empty() && nullptr != m_pCallbackFunction)
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
        const uint32_t width = image.getWidth();
        const uint32_t height = image.getHeight();
        image.draw(m_position.x, m_position.y, width, height);

        // Put back original color
        ofSetColor(currentColor);
    }
}
