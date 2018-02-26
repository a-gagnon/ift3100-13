//=======================================================================================
// datofxRadioButton.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../core/datCore.h"

BEGIN_DAT_NAMESPACE

typedef void(*ButtonCallback)();

//=======================================================================================
struct datofxRadioButton : ofxButton {

DEFINE_T_SUPER(ofxButton);

protected:
    ButtonCallback m_pCallback;
    ofEvent<ofxButton>& m_event;

protected:
    virtual bool mousePressed(ofMouseEventArgs & args) override;
    virtual bool mouseReleased(ofMouseEventArgs & args) override;
    void onRadioButtonPressed(ofxButton& button);

public:
    datofxRadioButton(ButtonCallback callback, ofEvent<ofxButton>& ev);
    virtual ~datofxRadioButton();
};


END_DAT_NAMESPACE
