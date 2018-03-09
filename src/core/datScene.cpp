//=======================================================================================
// datScene.cpp
// IFT3100-13
//=======================================================================================
#pragma once

#include "datScene.h"

USING_DAT_NAMESPACE

datScene::datScene() {

}


datScene::~datScene() {

}

void datScene::SetWorldToView(datTransform const& transform) {
    m_worldToView = transform;
    m_viewToWorld.makeInvertOf(transform);
}

