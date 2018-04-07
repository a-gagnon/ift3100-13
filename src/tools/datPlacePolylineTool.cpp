//=======================================================================================
// datPlacePolylineTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlacePolylineTool.h"

USING_DAT_NAMESPACE

datPlacePolylineTool::datPlacePolylineTool() {
    m_isClosed = false;
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
    GetRenderer().ClearTransients();
}


void datPlacePolylineTool::saveAndClearShape(bool closeShape) {

    if (2 <= m_points.size()) {

        ofPoint const& secondToLast = m_points[m_points.size() - 2];
        ofPoint const& last = m_points.back();

        // Remove duplicate point if any
        if (datEpsilon > secondToLast.squareDistance(last)) {
            m_points.pop_back();
        }
    }

    if (3 <= m_points.size() && closeShape) {
        m_points.push_back(m_points.front());
        m_isClosed = true;
    }

    if (2 <= m_points.size()) {
        std::unique_ptr<datPolyline> element = datPolyline::Create(m_points, m_isClosed);
        element->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
        GetRenderer().GetScene().InsertElement(std::move(element));
    }

    m_isClosed = false;
    m_points.clear();
    GetRenderer().ClearTransients();
    m_transient = nullptr;
}


void datPlacePolylineTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (2 <= m_points.size() && datEpsilon > m_points[m_points.size() - 2].squareDistance(ev.GetWorldPoint())) {
        saveAndClearShape(false);
        return;
    }

    // Add first point twice and use the last one as dynamic
    if (0 == m_points.size())
        m_points.push_back(ev.GetWorldPoint());

    m_points.push_back(ev.GetWorldPoint());
    updateTransient();
}


void datPlacePolylineTool::onRightMouseButtonDown(datMouseEvent const& ev) {

    // Remove the dynamic point
    if (0 < m_points.size())
        m_points.pop_back();

    saveAndClearShape(true);
}


void datPlacePolylineTool::onMouseMotion(datMouseEvent const& ev) {

    if (0 < m_points.size()) {
        m_points.back() = ev.GetWorldPoint();
        updateTransient();
    }
}


void datPlacePolylineTool::updateTransient() {

    if (nullptr == m_transient) {
        m_transient = datPolyline::Create(m_points, m_isClosed);
        GetRenderer().AddTransient(m_transient.get());
    }

    m_transient->SetPoints(m_points);
    m_transient->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
}


void datPlacePolylineTool::onDraw() {
    m_panel.draw();
}
