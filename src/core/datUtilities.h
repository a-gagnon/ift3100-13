//=======================================================================================
// datUtilities.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDefinitions.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datUtilities {

    // Returns the resolved path to the assets folder
    // @remarks expects the /assets/ folder to be 2 levels below the executable
    static std::string GetAssetsFolder();

    // Loads an image from the assets folder
    // @returns pointer to a dynamically allocated ofImage or nullptr
    static ofImage* LoadImageFromAssetsFolder(std::string const& fileName);
};

END_DAT_NAMESPACE
