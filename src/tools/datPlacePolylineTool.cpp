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


void datPlacePolylineTool::saveShape(ofPolyline const& polyline) {

    assert(0 < polyline.size());
    datGeometry* pGeometry = new datGeometry(polyline);
    pGeometry->SetColor(ofColor::orange);
    GeometryCache::GetCache().addGeometry(pGeometry);

}

void datPlacePolylineTool::onLeftMouseButtonDown(ofVec2f const& point) {

    // If we're very close to previous point, consider the user wants to 'confirm' the placement
    if (3 < m_polyline.size()) {

        ofVec2f backPt = m_polyline[m_polyline.size() - 2];
        if (5.0 > backPt.squareDistance(point)) {
            m_polyline.resize(m_polyline.size() - 1);
            saveShape(m_polyline);
            m_polyline.clear();
            return;
        }
    }


    // Add it twice and use the last point as dynamic
    if (0 == m_polyline.size())
        m_polyline.addVertex(point);

    m_polyline.addVertex(point);

}


void datPlacePolylineTool::onRightMouseButtonDown(ofVec2f const& point) {

    if (3 < m_polyline.size()) {
        m_polyline.resize(m_polyline.size() - 1);
        m_polyline.close();
        saveShape(m_polyline);
    }

    m_polyline.clear();
}


void datPlacePolylineTool::onMouseMotion(ofVec2f const& point) {

    if (0 < m_polyline.size()) {
        m_polyline[m_polyline.size() - 1] = point;
    }
}


void datPlacePolylineTool::onDraw() {

    GeometryCache::GetCache().drawCachedGeometries();
    m_polyline.draw();
}

