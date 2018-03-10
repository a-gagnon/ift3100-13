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

    void Extend(ofPoint const& point);
    void Expand(float delta);
    void Multiply(float factor);
    void Translate(ofPoint const& offset);

    bool Intersects(datBoundingBox const& other, bool strictlyInside) const;

    ofPoint GetCenter() const;
    std::vector<ofPoint> Get8Corners() const;
    float GetXLength() const { return high.x - low.x; }
    float GetYLength() const { return high.y - low.y; }
    float GetZLength() const { return high.z - low.z; }

};

END_DAT_NAMESPACE
