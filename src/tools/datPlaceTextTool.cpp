//=======================================================================================
// datPlaceTextTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceTextTool.h"

USING_DAT_NAMESPACE

datPlaceTextTool::datPlaceTextTool() {

    std::string fullPath = datUtilities::GetAssetsFolder();
    fullPath.append("arial.ttf");
    m_font.loadFont(fullPath, 24, true, true, true);

    SetPlaceholderText();
}


datPlaceTextTool::~datPlaceTextTool() {

}


void datPlaceTextTool::onStartTool() {
    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_paramFillColor.set(datLocalization::DisplayParams_FillColor(), GetRenderer().GetActiveDisplayParams().fillColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);

    m_paramFillColor.addListener(this, &datPlaceTextTool::onFillColorChanged);
}


void datPlaceTextTool::onExitTool() {
    m_paramFillColor.removeListener(this, &datPlaceTextTool::onFillColorChanged);
    GetRenderer().ClearTransients();
}


void datPlaceTextTool::SetPlaceholderText() {
    m_text = datLocalization::PlaceTextTool_Placeholder();
}


bool datPlaceTextTool::IsPlaceholderText() const {
    return m_text == datLocalization::PlaceTextTool_Placeholder();
}


void datPlaceTextTool::updateTransient(datMouseEvent const* pEvent) {

    if (nullptr == m_transient) {
        m_transient = datTextString::Create(m_font, m_text, ofNode());
        GetRenderer().AddTransient(m_transient.get());
    }

    if (nullptr != pEvent) {
        ofNode node;
        node.setGlobalPosition(pEvent->GetWorldPoint());
        node.setGlobalOrientation(pEvent->GetViewport().camera.getGlobalOrientation());
        m_transient->SetNode(node);
    }

    m_transient->SetText(m_text);
    m_transient->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
}



void datPlaceTextTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (!m_text.empty()) {
        
        ofNode node;
        node.setPosition(ev.GetWorldPoint());
        node.setGlobalOrientation(ev.GetViewport().camera.getGlobalOrientation());

        std::unique_ptr<datTextString> textString = datTextString::Create(m_font, m_text, node);
        textString->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
        GetRenderer().GetScene().InsertElement(std::move(textString));

        GetRenderer().ClearTransients();
        m_transient = nullptr;
    }

    SetPlaceholderText();
    updateTransient(&ev);
}


void datPlaceTextTool::onMouseMotion(datMouseEvent const& ev) {
    updateTransient(&ev);
}


void datPlaceTextTool::onKeyPressed(ofKeyEventArgs const& ev) {

    if (ofGetKeyPressed(OF_KEY_SHIFT))
        return;

    if (IsPlaceholderText()) {
        m_text.clear();
    }

    if (0x08 == ev.key && !m_text.empty()) {
        m_text = m_text.substr(0, m_text.size() - 1);
    }
    else {
        char key = static_cast<char>(ev.key);
        m_text += key;
    }

    updateTransient();
}


void datPlaceTextTool::onDraw() {
    m_panel.draw();
}
