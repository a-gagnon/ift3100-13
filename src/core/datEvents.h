//=======================================================================================
// datEvents.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"

BEGIN_DAT_NAMESPACE

struct datViewport;

//=======================================================================================
// Basic wrapper around mouse events
// Also contains ctrl/alt/shift key modifiers
//=======================================================================================
struct datMouseEvent {

public:
    datViewport* m_viewport;
    ofMouseEventArgs m_ofEvent;
    ofPoint m_viewPoint;
    ofPoint m_worldPoint;
    bool m_isCtrlKey;
    bool m_isShiftKey;
    bool m_isAltKey;

public:
    // Create from a ofMouseEvent
    explicit datMouseEvent(ofMouseEventArgs const& ev) : m_ofEvent(ev) {}

    void InitEvent(datViewport& vp, ofPoint const& viewPoint, ofPoint const& worldPoint, bool isCtrlKey, bool isShiftKey, bool isAltKey) {
        m_viewport = &vp;
        m_viewPoint = viewPoint;
        m_worldPoint = worldPoint;
        m_isCtrlKey = isCtrlKey;
        m_isShiftKey = isShiftKey;
        m_isAltKey = isAltKey;
    }

    datViewport& GetViewport() const { return *m_viewport;  }
    ofPoint const& GetViewPoint() const { return m_viewPoint; }
    ofPoint const& GetWorldPoint() const { return m_worldPoint; }
    bool IsCtrlKey() const { return m_isCtrlKey; }
    bool IsShiftKey() const { return m_isShiftKey; }
    bool IsAltKey() const { return m_isAltKey; }
    bool IsDrag() const { return ofMouseEventArgs::Type::Dragged == m_ofEvent.type; }

    ofMouseEventArgs::Type GetType() const { return m_ofEvent.type; }
    int GetButton() const { return m_ofEvent.button; }
};

END_DAT_NAMESPACE
