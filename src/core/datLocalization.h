//=======================================================================================
// datLocalization.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDefinitions.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Class that hold strings for our app.
struct datLocalization {

    static std::string PlacePolylineTool_Tooltip()  { return "Place polyline tool"; }
    static std::string PlaceTextTool_Placeholder()  { return "Placeholder"; }
    static std::string PlaceTextTool_Tooltip()      { return "Place text tool"; }
    static std::string SelectTool_Tooltip()         { return "Select tool"; }

};

END_DAT_NAMESPACE
