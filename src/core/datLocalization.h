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

    static std::string ChangeActiveColor()          { return "Change active color"; }
    static std::string ExportImageTool_Tooltip()    { return "Export image"; }
    static std::string PlaceImageTool_Tooltip()     { return "Place image tool"; }
    static std::string PlacePolylineTool_Tooltip()  { return "Place polyline tool"; }
    static std::string PlaceTextTool_Placeholder()  { return "Placeholder"; }
    static std::string PlaceTextTool_Tooltip()      { return "Place text tool"; }
    static std::string SelectTool_Tooltip()         { return "Select tool"; }
    static std::string SelectTool_CursorNormal()    { return "Normal cursor"; }
    static std::string SelectTool_CursorCircle()    { return "Circle"; }
    static std::string SelectTool_CursorX()         { return "X"; }
    static std::string SelectTool_CursorCross()     { return "Cross"; }
    static std::string SelectTool_CursorTriangle()  { return "Triangle"; }


};

END_DAT_NAMESPACE
