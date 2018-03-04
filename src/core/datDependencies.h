//=======================================================================================
// datDependencies.h
// IFT3100-13
//=======================================================================================
#pragma once

#include <memory>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

#include <commdlg.h> // Windows dialog for OpenFileDialog in datUtilities


// Convenience macros
#define BEGIN_DAT_NAMESPACE namespace dat {
#define END_DAT_NAMESPACE };
#define USING_DAT_NAMESPACE using namespace dat;

// Use this so we can refer to the base class as T_Super
#define DEFINE_T_SUPER(base) private: typedef base T_Super; public:

BEGIN_DAT_NAMESPACE
END_DAT_NAMESPACE
