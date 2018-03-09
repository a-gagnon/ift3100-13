//=======================================================================================
// datTransform.cpp
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTransform.h"

USING_DAT_NAMESPACE

datTransform::datTransform() {

}


datTransform::datTransform(ofMatrix4x4 const& mat) {

}


void datTransform::Multiply(ofPoint& point) const {

    const ofPoint inPoint = point;
    point.x =
        _mat[0][0] * inPoint.x +
        _mat[1][0] * inPoint.y +
        _mat[2][0] * inPoint.z +
        _mat[3][0];

    point.y =
        _mat[0][1] * inPoint.x +
        _mat[1][1] * inPoint.y +
        _mat[2][1] * inPoint.z +
        _mat[3][1];

    point.z =
        _mat[0][2] * inPoint.x +
        _mat[1][2] * inPoint.y +
        _mat[2][2] * inPoint.z +
        _mat[3][2];
}
