//=======================================================================================
// datBoundingBox.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Defines a range in 3d that the geometry occupies
// This box should be aligned with the axis!
//=======================================================================================
struct datBoundingBox {

public:
    ofPoint low;
    ofPoint high;

public:
    // Creates an invalid range (with inverted low/high)
    datBoundingBox();

    void InitInvalid();
    bool IsValid() const;

    static datBoundingBox FromPoints(std::vector<ofPoint> points, ofMatrix4x4 const* pTransform = nullptr);

    void Extend(ofPoint const& point);
    void Extend(datBoundingBox const& box);
    void Expand(float delta);
    bool Intersects(datBoundingBox const& box, bool strictlyInsideOrEqual) const;
    ofPoint GetCenter() const;

    float GetXLength() const { return high.x - low.x; }
    float GetYLength() const { return high.y - low.y; }
    float GetZLength() const { return high.z - low.z; }
};

END_DAT_NAMESPACE
