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


void datPlacePolylineTool::saveAndClearShape(bool closeShape) {

    if (2 <= m_polyline.size()) {

        ofPoint const& secondToLast = m_polyline[m_polyline.size() - 2];
        ofPoint const& last = m_polyline[m_polyline.size() - 1];

        // Remove duplicate point if any
        if (datEpsilon > secondToLast.squareDistance(last)) {
            m_polyline.resize(m_polyline.size() - 1);
        }
    }

    if (3 <= m_polyline.size() && closeShape)
        m_polyline.addVertex(m_polyline[0]);

    if (2 <= m_polyline.size()) {
        datGeometry* pGeometry = new datGeometry(m_polyline);
        pGeometry->SetColor(ofColor::orange);
        GeometryCache::GetCache().addGeometry(pGeometry);
    }

    m_polyline.clear();
}

void datPlacePolylineTool::onLeftMouseButtonDown(datMouseEvent const& ev) {

    if (2 <= m_polyline.size() && datEpsilon > m_polyline[m_polyline.size() - 2].squareDistance(ev)) {
        saveAndClearShape(false);
        return;
    }

    // Add first point twice and use the last one as dynamic
    if (0 == m_polyline.size())
        m_polyline.addVertex(ev);

    m_polyline.addVertex(ev);

}


void datPlacePolylineTool::onRightMouseButtonDown(datMouseEvent const& ev) {

    saveAndClearShape(true);
}


void datPlacePolylineTool::onMouseMotion(datMouseEvent const& ev) {

    if (0 < m_polyline.size()) {
        m_polyline[m_polyline.size() - 1] = ev;
    }
}


void datPlacePolylineTool::onDraw() {

    if (0 < m_polyline.size()) {
        m_polyline.draw();
    }
}

