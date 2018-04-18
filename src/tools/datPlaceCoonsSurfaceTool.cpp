//=======================================================================================
// datPlaceCoonsSurfaceTool.cpp
// IFT3100-13
//=======================================================================================
#include "datPlaceCoonsSurfaceTool.h"

USING_DAT_NAMESPACE

datPlaceCoonsSurfaceTool::datPlaceCoonsSurfaceTool() {

}


datPlaceCoonsSurfaceTool::~datPlaceCoonsSurfaceTool() {

}


void datPlaceCoonsSurfaceTool::onStartTool() {

    m_panel.setup(datLocalization::ToolSettings(), "", 0.4 * ofGetWidth());
    m_panel.add(m_paramLengthXY.set(datLocalization::Length(), 500, 1, 1000));
    m_panel.add(m_paramWidthXY.set(datLocalization::Width(), 500, 1, 1000));

    m_paramLengthXY.addListener(this, &datPlaceCoonsSurfaceTool::onLengthOrWidthChanged);
    m_paramWidthXY.addListener(this, &datPlaceCoonsSurfaceTool::onLengthOrWidthChanged);
}


void datPlaceCoonsSurfaceTool::onExitTool() {
    GetRenderer().ClearTransients();

    m_paramLengthXY.removeListener(this, &datPlaceCoonsSurfaceTool::onLengthOrWidthChanged);
    m_paramWidthXY.removeListener(this, &datPlaceCoonsSurfaceTool::onLengthOrWidthChanged);
}


void datPlaceCoonsSurfaceTool::onLengthOrWidthChanged(uint32_t& value) {
    updateTransient(nullptr);
}


void datPlaceCoonsSurfaceTool::updateTransient(datMouseEvent const* pEvent) {

    std::vector<ofPoint> points;
    points.push_back(ofPoint(0, 0, 0));
    points.push_back(ofPoint(m_paramLengthXY, 0, 0));
    points.push_back(ofPoint(m_paramLengthXY, m_paramWidthXY, 0));
    points.push_back(ofPoint(0, m_paramWidthXY, 0));
    points.push_back(points.front());

    if (nullptr == m_transient) {
        m_transient = datPolyline::Create(points, true/*isClosed*/);
        GetRenderer().AddTransient(m_transient.get());
    }
    else {
        m_transient->SetPoints(points);
        m_transient->SetIsClosed(true);
    }
}


void datPlaceCoonsSurfaceTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    // Create 4 cubic bezier curves out of random point locations
    std::vector<ofPoint> cPoints;

    // Pseudo-hardcodded values
    cPoints.push_back(ofPoint(0, 0, 0));                                                            // first corner
    cPoints.push_back(ofPoint(0.33 * m_paramLengthXY, cPoints.back().y, ofRandom(-100, 100)));
    cPoints.push_back(ofPoint(0.66 * m_paramLengthXY, cPoints.back().y, ofRandom(-100, 100)));
    cPoints.push_back(ofPoint(1.0  * m_paramLengthXY, cPoints.back().y, ofRandom(-100, 100)));      // second corner
    cPoints.push_back(ofPoint(cPoints.back().x, 0.25 * m_paramWidthXY, ofRandom(-100, 100)));
    cPoints.push_back(ofPoint(cPoints.back().x, 0.65 * m_paramWidthXY, ofRandom(-100, 100)));
    cPoints.push_back(ofPoint(cPoints.back().x, 1.0  * m_paramWidthXY, ofRandom(-100, 100)));       // third corner
    cPoints.push_back(ofPoint(0.5 * m_paramLengthXY, cPoints.back().y, ofRandom(-100, 100)));
    cPoints.push_back(ofPoint(0.25 * m_paramLengthXY, cPoints.back().y, ofRandom(-100, 100)));
    cPoints.push_back(ofPoint(0, cPoints.back().y, ofRandom(-100, 100)));                           // last corner
    cPoints.push_back(ofPoint(cPoints.back().x, 0.88 * m_paramWidthXY, ofRandom(-50, 50)));
    cPoints.push_back(ofPoint(cPoints.back().x, 0.30 * m_paramWidthXY, ofRandom(-50, 50)));
    cPoints.push_back(cPoints.front());

    std::vector<ofPoint> points1(cPoints.begin(), cPoints.begin() + 4);
    std::vector<ofPoint> points4(cPoints.begin() + 3, cPoints.begin() + 7);
    std::vector<ofPoint> points2(cPoints.begin() + 6, cPoints.begin() + 10);
    std::vector<ofPoint> points3(cPoints.begin() + 9, cPoints.end());

    // c2 and c3 needs to have their points reversed
    std::reverse(points2.begin(), points2.end());
    std::reverse(points3.begin(), points3.end());

    std::unique_ptr<datParametricCurve> curve1 = datParametricCurve::CreateBezier(points1);
    std::unique_ptr<datParametricCurve> curve2 = datParametricCurve::CreateBezier(points2);
    std::unique_ptr<datParametricCurve> curve3 = datParametricCurve::CreateBezier(points3);
    std::unique_ptr<datParametricCurve> curve4 = datParametricCurve::CreateBezier(points4);
    //              c2
    //      x-------------->x              /|\ y-axis 'v'
    //     /|\             /|\              |  
    //      |               |               |
    //  c3  |               |   c4          |
    //      |               |               |
    //      x-------------->x               ---------> x-axis 'u'
    //              c1


    static size_t s_nPointsX = 100;
    static size_t s_nPointsY = 80;

    ofPoint const& c10 = cPoints[0];
    ofPoint const& c11 = cPoints[3];
    ofPoint const& c21 = cPoints[6];
    ofPoint const& c20 = cPoints[9];

    float xIncrement = 1.0f / s_nPointsX;
    float yIncrement = 1.0f / s_nPointsY;

    std::vector<ofPoint> resultPoints;
    resultPoints.reserve((s_nPointsX + 1) * (s_nPointsY + 1));

    for (size_t xi = 0; xi <= s_nPointsX; ++xi) {

        const float x = xi * xIncrement;
        ofPoint c1x, c2x;
        curve1->EvaluateBezier(c1x, x);
        curve2->EvaluateBezier(c2x, x);

        for (size_t yi = 0; yi <= s_nPointsY; ++yi) {

            const float y = yi * yIncrement;
            ofPoint c3y, c4y;
            curve3->EvaluateBezier(c3y, y);
            curve4->EvaluateBezier(c4y, y);

            ofPoint xLerp = (1.0 - y) * c1x + y * c2x;
            ofPoint yLerp = (1.0 - x) * c3y + x * c4y;

            ofPoint blerp = (1.0 - x) * (1.0 - y) * c10 + x * (1.0 - y) * c11 + y * (1.0 - x) * c20 + x * y * c21;

            ofPoint result = xLerp + yLerp - blerp;
            resultPoints.push_back(result);
        }
    }

    ofxDelaunay delaunay;
    delaunay.addPoints(resultPoints);
    if (0 < delaunay.triangulate()) {
        std::unique_ptr<datMesh> element = datMesh::Create(delaunay.triangleMesh);
        element->SetDisplayParams(GetRenderer().GetActiveDisplayParams());
        GetRenderer().GetScene().InsertElement(std::move(element));
        _ExitTool();
    }


}


void datPlaceCoonsSurfaceTool::onRightMouseButtonDown(datMouseEvent const& ev) {
    _ExitTool();
}


void datPlaceCoonsSurfaceTool::onMouseMotion(datMouseEvent const& ev) {
    updateTransient(&ev);
}


void datPlaceCoonsSurfaceTool::onDraw() {
    m_panel.draw();
}

