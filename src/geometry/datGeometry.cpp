//=======================================================================================
// datGeometry.cpp
// IFT3100-13
//=======================================================================================
#include "datGeometry.h"

USING_DAT_NAMESPACE

datGeometry::datGeometry(ofPolyline const& polyline) :
    m_type(GeometryType::Polyline),
    m_polylineData(polyline) {
}


datGeometry::datGeometry(ofMesh const& mesh) :
    m_type(GeometryType::Mesh),
    m_meshData(mesh) {
}


datGeometry::datGeometry(datText const& text) :
    m_type(GeometryType::Text),
    m_textData(text) {
}


void datGeometry::draw() {

    ofSetColor(m_color);

    switch (m_type) {
        case GeometryType::Polyline:
            m_polylineData.draw();
            break;
        case GeometryType::Mesh:
            m_meshData.draw();
            break;
        case GeometryType::Text:
            m_textData.draw();
    }
}


//=======================================================================================
GeometryCache& GeometryCache::GetCache() {

    static GeometryCache s_instance;
    return s_instance;
}


void GeometryCache::addGeometry(datGeometry* pGeometry) {

    assert(nullptr != pGeometry);
    m_geometries.push_back(std::unique_ptr<datGeometry>(pGeometry));
}


void GeometryCache::drawCachedGeometries() {

    for (auto const& entry : m_geometries) {

        if (nullptr != entry) {
            entry->draw();
        }
    }
}
