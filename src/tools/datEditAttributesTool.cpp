//=======================================================================================
// datEditAttributesTool.cpp
// IFT3100-13
//=======================================================================================
#include "datEditAttributesTool.h"

USING_DAT_NAMESPACE

datEditAttributesTool::datEditAttributesTool() {
}


datEditAttributesTool::~datEditAttributesTool() {
}


void datEditAttributesTool::onStartTool() {

    m_geometries = GetRenderer().GetSelectionSet().GetSelection();
    assert(!m_geometries.empty());

    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_paramLineColor.set(datLocalization::DisplayParams_LineColor(), GetRenderer().GetActiveDisplayParams().lineColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.add(m_paramLineWidth.set(datLocalization::DisplayParams_LineWidth(), GetRenderer().GetActiveDisplayParams().lineWidth, 0.01f, 12.0f));
    m_panel.add(m_paramFillColor.set(datLocalization::DisplayParams_FillColor(), GetRenderer().GetActiveDisplayParams().fillColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);

    m_paramLineColor.addListener(this, &datEditAttributesTool::onLineColorChanged);
    m_paramLineWidth.addListener(this, &datEditAttributesTool::onLineWidthChanged);
    m_paramFillColor.addListener(this, &datEditAttributesTool::onFillColorChanged);

    GetRenderer().SetDrawSelectedInHilite(false);
}


void datEditAttributesTool::onExitTool() {

    m_paramLineColor.removeListener(this, &datEditAttributesTool::onLineColorChanged);
    m_paramLineWidth.removeListener(this, &datEditAttributesTool::onLineWidthChanged);
    m_paramFillColor.removeListener(this, &datEditAttributesTool::onFillColorChanged);
    GetRenderer().SetDrawSelectedInHilite(true);
}


void datEditAttributesTool::onLineColorChanged(ofColor& color) {
    for (auto const& geometry : m_geometries) {
        geometry->GetDisplayParamsR().lineColor = color;
    }
}


void datEditAttributesTool::onLineWidthChanged(float& value) {
    for (auto const& geometry : m_geometries) {
        geometry->GetDisplayParamsR().lineWidth = value;
    }
}


void datEditAttributesTool::onFillColorChanged(ofColor& color) {
    for (auto const& geometry : m_geometries) {
        geometry->GetDisplayParamsR().fillColor = color;
    }
}

void datEditAttributesTool::onDraw() {
    m_panel.draw();
}
