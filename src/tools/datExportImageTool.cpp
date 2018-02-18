//=======================================================================================
// datExportImageTool.cpp
// IFT3100-13
//=======================================================================================
#include "datExportImageTool.h"

USING_DAT_NAMESPACE

datExportImageTool::datExportImageTool(datExportImageDoneCallback callback) :
    m_pCallbackFunction(callback) {
    assert(nullptr != m_pCallbackFunction);
}


datExportImageTool::~datExportImageTool() {

}


void datExportImageTool::onStartTool() {

    std::string filePath;
    if (datUtilities::OpenFileDialog(filePath, false/*fileMustExist*/)) {

        std::string fileExt = ofFilePath::getFileExt(filePath);
        if (!fileExt.empty()) {
            filePath = filePath.substr(0, filePath.size() - 1 - fileExt.size());
        }
        filePath.append(".png");

        ofImage img;
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        img.save(filePath);
    }

    m_pCallbackFunction();
}
