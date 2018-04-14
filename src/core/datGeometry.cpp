//=======================================================================================
// datGeometry.cpp
// IFT3100-13
//=======================================================================================
#include "datGeometry.h"

USING_DAT_NAMESPACE

datPlane::datPlane(ofPoint const& origin, ofVec3f const& normal) :
    m_origin(origin),
    m_unitNormal(normal.getNormalized()) {
}


float datPlane::Evaluate(ofPoint const& point) const {

    ofVec3f originToPoint(point.x - m_unitNormal.x, point.y - m_unitNormal.y, point.z - m_unitNormal.z);
    return m_unitNormal.dot(originToPoint);
}


ofPoint datPlane::ProjectPoint(ofPoint const& point) const {

    const float distance = Evaluate(point);

    ofPoint projected;
    projected.x = point.x - (distance * m_unitNormal.x);
    projected.y = point.y - (distance * m_unitNormal.y);
    projected.z = point.z - (distance * m_unitNormal.z);
    return projected;
}



datRay::datRay(ofPoint const& origin, ofVec3f direction) :
    m_origin(origin),
    m_unitDirection(direction.getNormalized()) {
}


bool datRay::IntersectPlane(datPlane const& plane, ofPoint* pIntersection) const {

    const float dotDirNormal = m_unitDirection.dot(plane.GetNormal());

    // Same direction. No intersection
    if (0.0 <= dotDirNormal)
        return false;

    if (nullptr != pIntersection) {

        // ax + by + cz + d = 0
        float d = -plane.GetNormal().dot(plane.GetOrigin());
        float t = (d - plane.GetNormal().dot(m_origin)) / dotDirNormal;

        *pIntersection = ofPoint(m_origin.x + t * m_unitDirection.x, m_origin.y + t * m_unitDirection.y, m_origin.z + t * m_unitDirection.z);
    }

    return true;
}


bool datRay::IntersectBox(datBoundingBox const& aabb, ofPoint* pIntersection) const {

    // Find places where we intersect the planes defined by the axis lines
    float xLow = (aabb.low.x - m_origin.x) / m_unitDirection.x;
    float xHigh = (aabb.high.x - m_origin.x) / m_unitDirection.x;

    float yLow = (aabb.low.y - m_origin.y) / m_unitDirection.y;
    float yHigh = (aabb.high.y - m_origin.y) / m_unitDirection.y;
    
    float zLow = (aabb.low.z - m_origin.z) / m_unitDirection.z;
    float zHigh = (aabb.high.z - m_origin.z) / m_unitDirection.z;

    float tMin = std::max(std::max(std::min(xLow, xHigh), std::min(yLow, yHigh)), std::min(zLow, zHigh));
    float tMax = std::min(std::min(std::max(xLow, xHigh), std::max(yLow, yHigh)), std::max(zLow, zHigh));

    if (0.0 > tMax || tMin > tMax)
        return false;

    if (nullptr != pIntersection)
        *pIntersection = (m_origin + (tMax * m_unitDirection));

    return true;
}


float datRay::DistanceLineLine(datRay const& ray) const {

    ofVec3f pq = ray.m_origin - m_origin;
    ofVec3f cross = ray.m_unitDirection.getCrossed(m_unitDirection);

    if (datEpsilon > cross.length())
        return 0.0;

    const float distance = std::abs(pq.dot(cross) / cross.length());
    return distance;
}


bool datRay::IntersectLineLine(datRay const& ray) const {
    return datEpsilon > DistanceLineLine(ray);
}
