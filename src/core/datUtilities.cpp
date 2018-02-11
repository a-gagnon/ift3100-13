//=======================================================================================
// datUtilities.cpp
// IFT3100-13
//=======================================================================================
#include "datUtilities.h"

USING_DAT_NAMESPACE

std::string datUtilities::GetAssetsFolder() {

    std::string exeDir = ofFilePath::getCurrentExeDir();
    exeDir.append("../../assets/");
    return ofFilePath::getAbsolutePath(exeDir);
}


ofImage* datUtilities::LoadImageFromAssetsFolder(std::string const& fileName) {

    std::string filePath = GetAssetsFolder();
    filePath.append(fileName);

    ofImage* pImage = new ofImage();
    if (pImage->load(filePath))
        return pImage;

    assert(false); // We should never fail to load an image
    delete pImage;
    return nullptr;
}
