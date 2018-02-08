//=======================================================================================
// datDefinitions.h
// IFT3100-13
//=======================================================================================
#pragma once

#include <memory>
#include "ofMain.h"

// Convenience macros
#define BEGIN_DAT_NAMESPACE namespace dat {
#define END_DAT_NAMESPACE };
#define USING_DAT_NAMESPACE using namespace dat;

// Use this so we can refer to the base class as T_Super
#define DEFINE_T_SUPER(base) private: typedef base T_Super; public:

// Define pointer-to-function
typedef void(*datCallbackFunction)();

//=======================================================================================
struct NonCopyableClass {

private:
    NonCopyableClass(NonCopyableClass const&) = delete;
    NonCopyableClass& operator= (NonCopyableClass const&) = delete;
protected:
    NonCopyableClass() {}
    ~NonCopyableClass() {}
};



// Returns the resolved path to the assets folder
static std::string GetAssetsFolder() {

    std::string exeDir = ofFilePath::getCurrentExeDir();
    exeDir.append("../../assets/");
    return ofFilePath::getAbsolutePath(exeDir);
} 

// Utility. Loads an image from the assets folder
// @remarks expects the assets folder to be located one level below the exe
// returns a pointer to a dynamically allocated ofImage or nullptr
static ofImage* LoadImageFromAssetsFolder(std::string const& fileName) {

    std::string fullPath = GetAssetsFolder();
    fullPath.append(fileName);

    ofImage* pImage = new ofImage();
    if (pImage->load(fullPath))
        return pImage;

    assert(false); // We should never fail to load an image
    delete pImage;
    return nullptr;
}


BEGIN_DAT_NAMESPACE
END_DAT_NAMESPACE
