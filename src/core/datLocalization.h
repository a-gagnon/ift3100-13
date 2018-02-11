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

	static std::string Tooltip_SelectTool()			{ return "Select tool"; }
	static std::string Tooltip_PlacePolylineTool()	{ return "Place polyline tool"; }
	static std::string Tooltip_PlaceTextTool()		{ return "Place text tool"; }

};

END_DAT_NAMESPACE
