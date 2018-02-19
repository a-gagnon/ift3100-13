//=======================================================================================
// datUtilities.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDefinitions.h"
#include <commdlg.h> // Windows dialog for OpenFileDialog


BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datUtilities {

    // Returns the resolved path to the assets folder
    // @remarks expects the /assets/ folder to be 2 levels below the executable
    static std::string GetAssetsFolder();

    // Loads an image from the assets folder
    // @returns pointer to a dynamically allocated ofImage or nullptr
    static ofImage* LoadImageFromAssetsFolder(std::string const& fileName);

    // Opens a native (windows-only) file dialog
    // fileMustExist when false, allow picking non-existing files. useful for exporting
    // @returns true if user picked a path, false if the user cancelled the dialog
    static bool OpenFileDialog(std::string& filePath, bool fileMustExist);
};

END_DAT_NAMESPACE
