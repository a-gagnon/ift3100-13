//=======================================================================================
// datViewManipTool.cpp
// IFT3100-13
//=======================================================================================
#include "datViewManipTool.h"

USING_DAT_NAMESPACE

datViewManipTool::datViewManipTool(datMouseEvent const& ev) {

    m_isShiftKey = ofGetKeyPressed(OF_KEY_SHIFT);
    m_anchorPoint = ev.GetViewPoint();
}


datViewManipTool::~datViewManipTool() {

}


void datViewManipTool::onStartTool() {

    ofPoint point(ofGetMouseX(), ofGetMouseY());
    size_t viewportIdx = GetRenderer().GetViewportIndex(point);
    m_vp = &GetRenderer().GetViewport(viewportIdx);
    m_initialState = *m_vp;
}


void datViewManipTool::onMouseMotion(datMouseEvent const& ev) {

    ofPoint viewDelta = m_anchorPoint - ev.GetViewPoint();

    float deltaX = viewDelta.x * m_initialState.camera.getDistance() / ofGetWidth();
    float deltaY = viewDelta.y * m_initialState.camera.getDistance() / ofGetHeight();

    if (m_isShiftKey) {
        // Rotation

        static float s_rotFactor = 0.25;
        deltaX *= s_rotFactor;
        deltaY *= s_rotFactor;


        ofQuaternion prevOrientation = m_initialState.camera.getGlobalOrientation();
        ofPoint prevPosition = m_initialState.camera.getGlobalPosition();

        ofPoint positionOfTarget = m_vp->camera.getTarget().getGlobalPosition();
        ofQuaternion rotation(deltaY, m_initialState.camera.getXAxis(), deltaX, m_initialState.camera.getYAxis(), 0.0, m_initialState.camera.getZAxis());

        m_vp->camera.setPosition((prevPosition - positionOfTarget) * rotation + positionOfTarget);
        m_vp->camera.setOrientation(prevOrientation * rotation);
    }
    else {
        if (!m_vp->camera.isVFlipped())
            deltaY *= -1.0;

        // Translation
        ofPoint newPosition = m_initialState.camera.getGlobalPosition();
        newPosition += m_initialState.camera.getXAxis() * deltaX;
        newPosition += m_initialState.camera.getYAxis() * deltaY;
        m_vp->camera.setPosition(newPosition);
    }

}


void datViewManipTool::onLeftMouseButtonDown(datMouseEvent const& ev) {
    _ExitTool();
}


void datViewManipTool::onRightMouseButtonDown(datMouseEvent const& ev) {
    m_vp->camera = m_initialState.camera;
    _ExitTool();
}


void datViewManipTool::onMiddleMouseButtonUp(datMouseEvent const& ev) {
    _ExitTool();
}

