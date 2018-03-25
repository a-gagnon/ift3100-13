//=======================================================================================
// datPlacePolylineTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlacePolylineTool.h"

USING_DAT_NAMESPACE

datPlacePolylineTool::datPlacePolylineTool() {
}


datPlacePolylineTool::~datPlacePolylineTool() {
}


void datPlacePolylineTool::onStartTool() {

    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_paramLineColor.set(datLocalization::DisplayParams_LineColor(), GetRenderer().GetActiveDisplayParams().lineColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.add(m_paramLineWidth.set(datLocalization::DisplayParams_LineWidth(), GetRenderer().GetActiveDisplayParams().lineWidth, 0.01f, 12.0f));
    m_panel.add(m_paramFillColor.set(datLocalization::DisplayParams_FillColor(), GetRenderer().GetActiveDisplayParams().fillColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);

    m_paramLineColor.addListener(this, &datPlacePolylineTool::onLineColorChanged);
    m_paramLineWidth.addListener(this, &datPlacePolylineTool::onLineWidthChanged);
    m_paramFillColor.addListener(this, &datPlacePolylineTool::onFillColorChanged);
}


void datPlacePolylineTool::onExitTool() {

    m_paramLineColor.removeListener(this, &datPlacePolylineTool::onLineColorChanged);
    m_paramLineWidth.removeListener(this, &datPlacePolylineTool::onLineWidthChanged);
    m_paramFillColor.removeListener(this, &datPlacePolylineTool::onFillColorChanged);
}


void datPlacePolylineTool::saveAndClearShape(bool closeShape) {

    if (2 <= m_polyline.size()) {

        ofPoint const& secondToLast = m_polyline[m_polyline.size() - 2];
        ofPoint const& last = m_polyline[m_polyline.size() - 1];

        // Remove duplicate point if any
        if (datEpsilon > secondToLast.squareDistance(last)) {
            m_polyline.resize(m_polyline.size() - 1);
        }
    }

    if (3 <= m_polyline.size() && closeShape) {
        m_polyline.addVertex(m_polyline[0]);
        m_polyline.setClosed(true);
    }

    if (2 <= m_polyline.size()) {
        std::unique_ptr<datGeometry> geometry = datGeometry::Create(m_polyline);
        geometry->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
        GetRenderer().GetScene().InsertGeometry(std::move(geometry));
    }

    m_polyline.clear();
    GetRenderer().ClearTransients();
    m_transient = nullptr;
}


void datPlacePolylineTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (2 <= m_polyline.size() && datEpsilon > m_polyline[m_polyline.size() - 2].squareDistance(ev.GetWorldPoint())) {
        saveAndClearShape(false);
        return;
    }

    // Add first point twice and use the last one as dynamic
    if (0 == m_polyline.size())
        m_polyline.addVertex(ev.GetWorldPoint());

    m_polyline.addVertex(ev.GetWorldPoint());
    updateTransient();
}


void datPlacePolylineTool::onRightMouseButtonDown(datMouseEvent const& ev) {

    // Remove the dynamic point
    if (0 < m_polyline.size())
        m_polyline.resize(m_polyline.size() - 1);

    saveAndClearShape(true);
}


void datPlacePolylineTool::onMouseMotion(datMouseEvent const& ev) {

    if (0 < m_polyline.size()) {
        m_polyline[m_polyline.size() - 1] = ev.GetWorldPoint();
        updateTransient();
    }
}


void datPlacePolylineTool::updateTransient() {

    if (nullptr == m_transient) {
        m_transient = datGeometry::Create(m_polyline);
        GetRenderer().AddTransient(m_transient.get());
    }

    m_transient->GetAsPolyline() = m_polyline;
    m_transient->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
}

void datPlacePolylineTool::onDraw() {
    m_panel.draw();
}

