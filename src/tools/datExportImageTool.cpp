//=======================================================================================
// datExportImageTool.cpp
// IFT3100-13
//=======================================================================================
#include "datExportImageTool.h"

USING_DAT_NAMESPACE

datExportImageTool::datExportImageTool() {

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
}


void datExportImageTool::onDraw() {
    _ExitTool();
}


