//=======================================================================================
// datofxRadioButton.cpp
// IFT3100-13
//=======================================================================================
#include "datofxRadioButton.h"

USING_DAT_NAMESPACE

datofxRadioButton::datofxRadioButton(ButtonCallback callback, ofEvent<ofxButton>& ev) :
    m_pCallback(callback),
    m_event(ev) {
    assert(nullptr != m_pCallback);
    ofAddListener(m_event, this, &datofxRadioButton::onRadioButtonPressed);
}


datofxRadioButton::~datofxRadioButton() {
    ofRemoveListener(m_event, this, &datofxRadioButton::onRadioButtonPressed);
}


bool datofxRadioButton::mousePressed(ofMouseEventArgs& args) {

    if (!T_Super::mousePressed(args))
        return false;

    ofNotifyEvent(m_event, *this);
    return true;
}


bool datofxRadioButton::mouseReleased(ofMouseEventArgs& args) {
    return true;
}


void datofxRadioButton::onRadioButtonPressed(ofxButton& button) {

    if (this == &button) {
        value = true;
        m_pCallback();
    }
    else
        value = false;

    generateDraw();
}
