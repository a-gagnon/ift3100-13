//=======================================================================================
// datPlaceParametricCurveTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceParametricCurveTool.h"

USING_DAT_NAMESPACE

namespace {

    static datPlaceParametricCurveTool* s_tool = nullptr;
    void setBezier() { s_tool->SetType(datParametricCurve::Type::Bezier); }
    void setHermite() { s_tool->SetType(datParametricCurve::Type::Hermite); }
    void setBSpline() { s_tool->SetType(datParametricCurve::Type::BSpline); }
    void setCatmullRom() { s_tool->SetType(datParametricCurve::Type::CatmullRom); }
    ofEvent<ofxButton> typeEvent;

};


datPlaceParametricCurveTool::datPlaceParametricCurveTool():
    m_typeBezier(setBezier, typeEvent),
    m_typeHermite(setHermite, typeEvent),
    m_typeBSpline(setBSpline, typeEvent),
    m_typeCatmullRom(setCatmullRom, typeEvent) {
    m_type = datParametricCurve::Type::Hermite; //&&AG put back to bezier when it's done
    s_tool = this;
}


datPlaceParametricCurveTool::~datPlaceParametricCurveTool() {
    s_tool = nullptr;
}


void datPlaceParametricCurveTool::onStartTool() {
    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_paramLineColor.set(datLocalization::DisplayParams_LineColor(), GetRenderer().GetActiveDisplayParams().lineColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_panel.add(m_paramLineWidth.set(datLocalization::DisplayParams_LineWidth(), GetRenderer().GetActiveDisplayParams().lineWidth, 0.01f, 12.0f));
    m_panel.add(m_typeBezier.setup(datLocalization::Bezier()));
    m_panel.add(m_typeHermite.setup(datLocalization::Hermite()));
    m_panel.add(m_typeBSpline.setup(datLocalization::BSpline()));
    m_panel.add(m_typeCatmullRom.setup(datLocalization::CatmullRom()));
    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);

    m_paramLineColor.addListener(this, &datPlaceParametricCurveTool::onLineColorChanged);
    m_paramLineWidth.addListener(this, &datPlaceParametricCurveTool::onLineWidthChanged);
    ofNotifyEvent(typeEvent, m_typeHermite);
}


void datPlaceParametricCurveTool::onExitTool() {
    m_paramLineColor.removeListener(this, &datPlaceParametricCurveTool::onLineColorChanged);
    m_paramLineWidth.removeListener(this, &datPlaceParametricCurveTool::onLineWidthChanged);

    GetRenderer().ClearTransients();
}


void datPlaceParametricCurveTool::updateTransient(datMouseEvent const* pEvent) {

    GetRenderer().ClearTransients();
    m_transient = nullptr;

    std::vector<ofPoint> points = m_controlPoints;
    if (points.empty() || nullptr == pEvent)
        return;

    // We need to have a multiples of 4 points for bspline and catmull rom
    while (0 != (points.size() % 4)) {
        points.push_back(points.back());
    }

    switch (m_type) {
        case datParametricCurve::Type::Bezier:
            m_transient = datParametricCurve::CreateBezier(points);
            break;
        case datParametricCurve::Type::Hermite:
            m_transient = datParametricCurve::CreateHermite(points[0], points[2], points[1], points[3]);
            break;
        case datParametricCurve::Type::BSpline:
            m_transient = datParametricCurve::CreateBSpline(points);
            break;
        case datParametricCurve::Type::CatmullRom:
            m_transient = datParametricCurve::CreateCatmullRom(points);
            break;
    }

    if (nullptr != m_transient) {
        m_transient->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
        GetRenderer().AddTransient(m_transient.get());
    }
}

void datPlaceParametricCurveTool::updateStyle() {
    if (nullptr != m_transient) {
        m_transient->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
    }
}



void datPlaceParametricCurveTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (4 < m_controlPoints.size() && datEpsilon > m_controlPoints[m_controlPoints.size() - 2].squareDistance(ev.GetWorldPoint())) {
        saveCurve(ev);
    }

    // Add first point twice and use the last one as dynamic
    if (0 == m_controlPoints.size())
        m_controlPoints.push_back(ev.GetWorldPoint());

    m_controlPoints.push_back(ev.GetWorldPoint());
    updateTransient(&ev);
}


void datPlaceParametricCurveTool::onRightMouseButtonDown(datMouseEvent const& ev) {
    saveCurve(ev);
}


void datPlaceParametricCurveTool::saveCurve(datMouseEvent const& ev) {

    // Cheat. transient already does all the work, so just update and clone it.
    updateTransient(&ev);

    if (nullptr != m_transient) {
        std::unique_ptr<datElement> parametricCurve = m_transient->Clone();
        static_cast<datParametricCurve*>(parametricCurve.get())->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
        GetRenderer().GetScene().InsertElement(std::move(parametricCurve));

        m_controlPoints.clear();
        updateTransient(nullptr); // Unregister transient from renderer and clears it
        _ExitTool();
    }
}



void datPlaceParametricCurveTool::onMouseMotion(datMouseEvent const& ev) {

    if (0 < m_controlPoints.size())
        m_controlPoints.back() = ev.GetWorldPoint();

    updateTransient(&ev);
}


void datPlaceParametricCurveTool::onDraw() {
    m_panel.draw();
}
