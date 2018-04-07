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


void datBoundingBox::InitInvalid() {
    low.x = low.y = low.z = std::numeric_limits<float>::max();
    high.x = high.y = high.z = std::numeric_limits<float>::lowest();
}


bool datBoundingBox::IsValid() const {
    return low.x <= high.x &&
           low.y <= high.y &&
           low.z <= high.z;
}


datBoundingBox datBoundingBox::FromPoints(std::vector<ofPoint> points, ofMatrix4x4 const* pTransform) {
    
    datBoundingBox box;

    if (nullptr != pTransform) {
        for (auto& point : points) {
            point = point * (*pTransform);
            box.Extend(point);
        }
    }
    return box;
}




void datBoundingBox::Extend(ofPoint const& point) {

    low.x = MIN(low.x, point.x);
    low.y = MIN(low.y, point.y);
    low.z = MIN(low.z, point.z);
    high.x = MAX(high.x, point.x);
    high.y = MAX(high.y, point.y);
    high.z = MAX(high.z, point.z);
}

void datBoundingBox::Extend(datBoundingBox const& box) {

    low.x = MIN(low.x, box.low.x);
    low.y = MIN(low.y, box.low.y);
    low.z = MIN(low.z, box.low.z);
    high.x = MAX(high.x, box.high.x);
    high.y = MAX(high.y, box.high.y);
    high.z = MAX(high.z, box.high.z);
}


void datBoundingBox::Expand(float delta) {
    low.x -= delta;
    low.y -= delta;
    low.z -= delta;
    high.x += delta;
    high.y += delta;
    high.z += delta;
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

ofPoint datBoundingBox::GetCenter() const {

    ofPoint pt;
    pt.x = 0.5 * (low.x + high.x);
    pt.y = 0.5 * (low.y + high.y);
    pt.z = 0.5 * (low.z + high.z);
    return pt;
}


std::vector<ofPoint> datBoundingBox::Get8Corners() const {

    std::vector<ofPoint> result;
    result.reserve(8);

    ofPoint pts[2];
    pts[0] = low;
    pts[1] = high;

    for (uint32_t z = 0; z < 2; ++z) {
        for (uint32_t y = 0; y < 2; ++y) {
            for (uint32_t x = 0; x < 2; ++x) {
                result.push_back(ofPoint(pts[x].x, pts[y].y, pts[z].z));
            }
        }
    }

    return result;
    }


bool datBoundingBox::ContainsInclusive(ofPoint const& point) const {

    return  low.x <= point.x && point.x <= high.x &&
            low.y <= point.y && point.y <= high.y &&
            low.z <= point.z && point.z <= high.z;
}


bool datBoundingBox::ContainsInclusive(datBoundingBox const& box) const {
    return Intersects(box, true);
}


bool datBoundingBox::Intersects(datBoundingBox const& box, bool strictlyInsideOrEqual) const {

    if (high.x < box.low.x || low.x > box.high.x)
        return false;
    if (high.y < box.low.y || low.y > box.high.y)
        return false;
    if (high.z < box.low.z || low.z > box.high.z)
        return false;

    if (!strictlyInsideOrEqual)
        return true;

    return low.x <= box.low.x && box.high.x <= high.x &&
        low.y <= box.low.y && box.high.y <= high.y &&
        low.z <= box.low.z && box.high.z <= high.z;
}


