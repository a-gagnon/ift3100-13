//=======================================================================================
// datLocalization.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Class that hold strings for our app.
//=======================================================================================
struct datLocalization {

    static std::string ChangeActiveColor()          { return "Change active color"; }
    static std::string DeleteSelectedGeometries()   { return "Delete selected geometries"; }
    static std::string EditAttributesTool_Tooltip() { return "Edit attributes of selected geometries"; }
	static std::string AddTextureTool_Tooltip()		{ return "Add texture to image"; }
    static std::string ExportImageTool_Tooltip()    { return "Export image"; }
    static std::string PlaceImageTool_Tooltip()     { return "Place image tool"; }
    static std::string PlaceModelTool_Tooltip()     { return "Place model tool"; }
    static std::string PlacePolylineTool_Tooltip()  { return "Place polyline tool"; }
    static std::string PlaceTextTool_Placeholder()  { return "Placeholder"; }
    static std::string PlaceTextTool_Tooltip()      { return "Place text tool"; }
    static std::string SelectTool_BackgroundColor() { return "Background color"; }
    static std::string SelectTool_BoundingBox()     { return "Display bounding box"; }
    static std::string SelectTool_Tooltip()         { return "Select tool"; }
    static std::string SelectTool_CameraOrtho()     { return "'6': Orthographic cam."; }
    static std::string SelectTool_CameraPerspective() { return "'7': Perspective cam."; }
    static std::string SelectTool_CursorNormal()    { return "'1': Normal cursor"; }
    static std::string SelectTool_CursorCircle()    { return "'2': Circle"; }
    static std::string SelectTool_CursorX()         { return "'3': X"; }
    static std::string SelectTool_CursorCross()     { return "'4': Cross"; }
    static std::string SelectTool_CursorTriangle()  { return "'5': Triangle"; }
    static std::string SelectTool_TwoViewports()    { return "Two viewports"; }

    static std::string Redo()                       { return "Redo"; }
    static std::string Undo()                       { return "Undo"; }

    static std::string DisplayParams()              { return "Display parameters"; }
    static std::string DisplayParams_LineWidth()    { return "Line width"; }
    static std::string DisplayParams_LineColor()    { return "Line color"; }
    static std::string DisplayParams_FillColor()    { return "Fill color"; }
    static std::string GeometryParams()             { return "Geometry parameters"; }
    static std::string GeometryParams_Rotate()      { return "Rotate"; }
    static std::string GeometryParams_Scale()       { return "Scale"; }
    static std::string GeometryParams_Translate()   { return "Translate"; }
};

END_DAT_NAMESPACE
