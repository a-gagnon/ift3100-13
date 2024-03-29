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
    static std::string PlaceCoonsTool_Tooltip()     { return "Place Coons surface"; }
    static std::string PlaceImageTool_Tooltip()     { return "Place image tool"; }
    static std::string PlaceLightTool_Point()       { return "Point"; }
    static std::string PlaceLightTool_Area()        { return "Area"; }
    static std::string PlaceLightTool_Spot()        { return "Spot"; }
    static std::string PlaceLightTool_Directional() { return "Directional"; }
    static std::string PlaceLightTool_Tooltip()     { return "Place light tool"; }
    static std::string PlaceLightTool_ColorAmbient()    { return "Color ambient"; }
    static std::string PlaceLightTool_ColorDiffuse()    { return "Color diffuse"; }
    static std::string PlaceLightTool_ColorSpecular()   { return "Color specular"; }
    static std::string PlaceLightTool_AttenuationConstant()     { return "Attenuation (constant)"; }
    static std::string PlaceLightTool_AttenuationLinear()       { return "Attenuation (linear)"; }
    static std::string PlaceLightTool_AttenuationQuadratic()    { return "Attenuation (quadratric)"; }
    static std::string PlaceLightTool_SpotCutoff()              { return "Cutoff"; }
    static std::string PlaceLightTool_SpotConcentration()       { return "Concentration"; }
    static std::string PlaceLightTool_Direction()               { return "Direction"; }
    static std::string PlaceLightTool_Width()                   { return "Width"; }
    static std::string PlaceLightTool_Height()                  { return "Height"; }
    static std::string PlaceParametricCurve_Tooltip()           { return "Place Parametric Curve"; }

    static std::string PlaceModelTool_Tooltip()     { return "Place model tool"; }
    static std::string PlacePolylineTool_Tooltip()  { return "Place polyline tool"; }
    static std::string PlaceTextTool_Placeholder()  { return "Placeholder"; }
    static std::string PlaceTextTool_Tooltip()      { return "Place text tool"; }
    static std::string SelectTool_BackgroundColor() { return "Background color"; }
    static std::string SelectTool_Tooltip()         { return "Select tool"; }
    static std::string SelectTool_CursorNormal()    { return "'1': Normal cursor"; }
    static std::string SelectTool_CursorCircle()    { return "'2': Circle"; }
    static std::string SelectTool_CursorX()         { return "'3': X"; }
    static std::string SelectTool_CursorCross()     { return "'4': Cross"; }
    static std::string SelectTool_CursorTriangle()  { return "'5': Triangle"; }
    static std::string ToggleLighting_Tooltip()     { return "Toggle lighting"; }
    static std::string TwoViewports_Tooltip()       { return "Toggle two viewports"; }
    static std::string BoundingBox_ToolTip()        { return "Toggle bounding box display"; }
    static std::string Orthographic_Tooltip()       { return "Toggle orthographic camera"; }

    static std::string CatmullRom()                 { return "Catmull-Rom"; }
    static std::string Bezier()                     { return "Bezier"; }
    static std::string BSpline()                    { return "B-Spline"; }
    static std::string FillGeometry()               { return "Fill geometry"; }
    static std::string FillColor()                  { return "Fill color"; }
    static std::string GenerateSceneRayTracing_Tooltip() { return "Generate scene using Ray tracing technique \nThis may take a while"; }
    static std::string Hermite()                    { return "Hermite"; }
    static std::string Length()                     { return "Length"; }
    static std::string LineColor()                  { return "Line color"; }
    static std::string LineWidth()                  { return "Line width"; }
    static std::string Materials()                  { return "Materials"; }
    static std::string Material1()                  { return "Material 1"; }
    static std::string Material2()                  { return "Material 2"; }
    static std::string Material3()                  { return "Material 3"; }
    static std::string NoMaterial()                 { return "No Material"; }
    static std::string Redo()                       { return "Redo"; }
    static std::string ToolSettings()               { return "Tool Settings"; }
    static std::string Undo()                       { return "Undo"; }
    static std::string Width()                      { return "Width"; }

    static std::string DisplayParams()              { return "Display parameters"; }
    static std::string GeometryParams()             { return "Geometry parameters"; }
    static std::string GeometryParams_Rotate()      { return "Rotate"; }
    static std::string GeometryParams_Scale()       { return "Scale"; }
    static std::string GeometryParams_Translate()   { return "Translate"; }
};

END_DAT_NAMESPACE
