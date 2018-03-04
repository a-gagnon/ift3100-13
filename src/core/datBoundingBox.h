//=======================================================================================
// datBoundingBox.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Defines a range in 3d that the geometry occupies
//=======================================================================================
struct datBoundingBox {

public:
    ofVec3f low;
    ofVec3f high;

public:
    // Creates an invalid range (with inverted low/high)
    datBoundingBox();
    datBoundingBox(ofPoint const& point);
    datBoundingBox(ofPolyline const& polyline);
    datBoundingBox(ofMesh const& mesh);

    void Init(ofPoint const& point);
    void InitInvalid();
    bool IsValid() const;

    void Extend(ofPoint const& point);
};

END_DAT_NAMESPACE
