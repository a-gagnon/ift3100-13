//=======================================================================================
// datBoundingBox.cpp
// IFT3100-13
//=======================================================================================
#pragma once

#include "datBoundingBox.h"

USING_DAT_NAMESPACE

datBoundingBox::datBoundingBox() {
    InitInvalid();
}


datBoundingBox::datBoundingBox(ofPoint const& point) {
    Init(point);
}


datBoundingBox::datBoundingBox(ofPolyline const& polyline) {
    InitInvalid();
    for (uint32_t i = 0; i < polyline.size(); ++i) {
        Extend(polyline[i]);
    }
}


datBoundingBox::datBoundingBox(ofMesh const& mesh) {
    InitInvalid();
    std::vector<ofPoint> const& vertices = mesh.getVertices();
    for (auto const& vertex : vertices) {
        Extend(vertex);
    }
}


void datBoundingBox::Init(ofPoint const& point) {
    low = point;
    high = point;
}

void datBoundingBox::InitInvalid() {
    low.x = low.y = low.z = std::numeric_limits<float>::max();
    high.x = high.y = high.z = std::numeric_limits<float>::lowest();
}


bool datBoundingBox::IsValid() const {
    return low.x <= high.x &&
           low.y <= high.y &&
           low.z <= high.z;
}


void datBoundingBox::Extend(ofPoint const& point) {

    low.x = MIN(low.x, point.x);
    low.y = MIN(low.y, point.y);
    low.z = MIN(low.z, point.z);

    high.x = MAX(high.x, point.x);
    high.y = MAX(high.y, point.y);
    high.z = MAX(high.z, point.z);
}


void datBoundingBox::Multiply(float factor) {
    low.x *= factor;
    low.y *= factor;
    low.z *= factor;
    high.x *= factor;
    high.y *= factor;
    high.z *= factor;
}


void datBoundingBox::Translate(ofPoint const& offset) {
    low.x += offset.x;
    low.y += offset.y;
    low.z += offset.z;
    high.x += offset.x;
    high.y += offset.y;
    high.z += offset.z;
}



bool datBoundingBox::HasAnyOverlapWith(datBoundingBox const& rhs) const {

    if (low.x > rhs.high.x || high.x < rhs.low.x)
        return false;

    if (low.y > rhs.high.y || high.y < rhs.low.y)
        return false;

    if (low.z > rhs.high.z || high.z < rhs.low.z)
        return false;

    return true;
}

bool datBoundingBox::Contains(datBoundingBox const& rhs) const {
    
    if (rhs.low.x < low.x || high.x < rhs.high.x)
        return false;

    if (rhs.low.y < low.y || high.y < rhs.high.y)
        return false;

    if (rhs.low.z < low.z || high.z < rhs.high.z)
        return false;

    return true;
}
