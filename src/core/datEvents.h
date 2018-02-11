//=======================================================================================
// datEvents.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDefinitions.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
//&&AG needswork mouse event that takes into account CTRL/SHIFT/ALT key modifiers
struct datMouseEvent : ofMouseEventArgs {

    // Create from a ofMouseEvent
    datMouseEvent(ofMouseEventArgs const& ev) : ofMouseEventArgs(ev) {}

    bool IsDrag() const { return Type::Dragged == type; }
};

END_DAT_NAMESPACE
