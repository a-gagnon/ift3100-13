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


void datBoundingBox::Extend(ofPoint const& point) {

    low.x = MIN(low.x, point.x);
    low.y = MIN(low.y, point.y);
    low.z = MIN(low.z, point.z);
    high.x = MAX(high.x, point.x);
    high.y = MAX(high.y, point.y);
    high.z = MAX(high.z, point.z);
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



namespace {

	void getLowHighOnVector(float& min, float& max, ofVec3f const& vector, ofPoint const& refPoint, std::vector<ofPoint> const& points) {

		min = std::numeric_limits<float>::max();
		max = std::numeric_limits<float>::lowest();

		for (auto const& point : points) {
			const ofVec3f refToPoint(point.x - refPoint.x, point.y - refPoint.y, point.z - refPoint.z);
			const float distance = vector.dot(refToPoint);

			if (min > distance)
				min = distance;
			if (max < distance)
				max = distance;
		}
	}
	
};


bool datBoundingBox::Intersects(datBoundingBox const& other, bool strictlyInside) const {

	// An implementation following the ideas of
	// https://gamedev.stackexchange.com/questions/25397/obb-vs-obb-collision-detection
	// For each pair of points in the first box, we create a normalized vector
	// We get the 'range' of the first box on that vector and compare with the second
	// If there are no intersections between ranges, it means we don't have any overlap

	const std::vector<ofPoint> pointsA = Get8Corners();
	const std::vector<ofPoint> pointsB = other.Get8Corners();

	for (uint32_t i = 1; i < pointsA.size(); ++i) {
		ofVec3f ref(pointsA[i].x - pointsA[i - 1].x,
					pointsA[i].y - pointsA[i - 1].y,
					pointsA[i].z - pointsA[i - 1].z);
		ref.normalize();

		// project all points of box1 and search for min max
		float minA, maxA;
		getLowHighOnVector(minA, maxA, ref, pointsA[i - 1], pointsA);

		float minB, maxB;
		getLowHighOnVector(minB, maxB, ref, pointsA[i - 1], pointsB);

		if (maxA < minB || maxB < minA)
			return false; // No intersection

		if (strictlyInside && (minA > minB || maxA < maxB))
			return false; // Not all other projected points are inside current box
	}

	return true;
}


