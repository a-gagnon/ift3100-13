//=======================================================================================
// datInputView.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../datDefinitions.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Generic rectangle-shaped input class that drives the UI
//=======================================================================================
struct datInputView : ofRectangle, NonCopyableClass {

DEFINE_T_SUPER(ofRectangle)
friend struct datInputManager;

private:
    bool m_hasFocus;

protected:
    virtual void onHover()  { m_hasFocus = true; }
    virtual void onBlur()   { m_hasFocus = false;}
    virtual void onClick() {}
    virtual void onDraw() {}

    datInputView() : m_hasFocus(false) {}
    datInputView(float x, float y, float width, float height) : T_Super(x, y, width, height), m_hasFocus(false) {}

public:
    virtual ~datInputView() {}

    bool HasFocus() const { return m_hasFocus; }

    bool IsPointInside(ofVec2f const& point) const {
        const ofPoint low = getTopLeft();
        const ofPoint high = getBottomRight();
        return (low.x < point.x && point.x < high.x &&
                low.y < point.y && point.y < high.y);
    }

};

END_DAT_NAMESPACE
