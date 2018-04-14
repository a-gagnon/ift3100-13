//=======================================================================================
// datGeometry.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"
#include "datBoundingBox.h"

BEGIN_DAT_NAMESPACE

// Small tolerance for comparisons
#define datEpsilon 1e-03

//=======================================================================================
// Implementation of a plane in 3d
//=======================================================================================
struct datPlane {

private:
    ofPoint m_origin;       // Arbitrary point on the plane
    ofVec3f m_unitNormal;   // Unit normal vector.

public:
    datPlane(ofPoint const& origin, ofVec3f const& normal);

    ofPoint const& GetOrigin() const { return m_origin; }
    ofVec3f const& GetNormal() const { return m_unitNormal; }
    void SetNormal(ofVec3f const& normal) { m_unitNormal = normal.getNormalized(); }

    // Returns the distance from the point to the plane.
    // Negative distance means the point is behind the plane
    float Evaluate(ofPoint const& point) const;

    // Projects a point onto the plane
    ofPoint ProjectPoint(ofPoint const& point) const;
};

//=======================================================================================
// Implementation of a ray in 3d
//=======================================================================================
struct datRay {

private:
    ofPoint m_origin;           // Origin of the ray
    ofVec3f m_unitDirection;    // Unit direction vector

public:
    datRay(ofPoint const& origin, ofVec3f direction);

    ofPoint const& GetOrigin() const { return m_origin; }
    ofVec3f const& GetDirection() const { return m_unitDirection; }
    void SetDirection(ofVec3f direction) { m_unitDirection = direction.getNormalized(); }

    // Intersects a plane
    bool IntersectPlane(datPlane const& plane, ofPoint* pIntersection = nullptr) const;

    // Intersects a box
    bool IntersectBox(datBoundingBox const& aabb, ofPoint* pIntersection = nullptr) const;

    // Returns the closest distance between two lines.
    float DistanceLineLine(datRay const& ray) const;

    bool IntersectLineLine(datRay const& ray) const;
};

END_DAT_NAMESPACE