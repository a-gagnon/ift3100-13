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


datGeometry::datGeometry(datTextString const& textString) :
    m_type(GeometryType::TextString),
    m_textStringData(textString) {
}


std::unique_ptr<datGeometry> datGeometry::Create(ofPolyline const& polyline) {
    auto ptr = std::unique_ptr<datGeometry>(new datGeometry(polyline));
    return std::move(ptr);
}


std::unique_ptr<datGeometry> datGeometry::Create(ofMesh const& mesh) {
    auto ptr = std::unique_ptr<datGeometry>(new datGeometry(mesh));
    return std::move(ptr);
}


std::unique_ptr<datGeometry> datGeometry::Create(datTextString const& textString) {
    auto ptr = std::unique_ptr<datGeometry>(new datGeometry(textString));
    return std::move(ptr);
}


void datGeometry::draw() const {

    ofSetColor(m_color);

    switch (m_type) {
        case GeometryType::Polyline:
            m_polylineData.draw();
            break;
        case GeometryType::Mesh:
            m_meshData.draw();
            break;
        case GeometryType::TextString:
            m_textStringData.draw();
            break;
    }
}
