//=======================================================================================
// datTransform.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Wrapper around the ofMatrix4x4
// Added some more methods for convenience
//=======================================================================================
struct datTransform : ofMatrix4x4 {

public:
    datTransform();
    datTransform(ofMatrix4x4 const& mat);

    void Multiply(ofPoint& point) const;
};

END_DAT_NAMESPACE
