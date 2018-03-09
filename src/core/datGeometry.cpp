//=======================================================================================
// datGeometry.cpp
// IFT3100-13
//=======================================================================================
#include "datGeometry.h"

USING_DAT_NAMESPACE

datGeometry::datGeometry(ofPolyline const& polyline) :
    m_type(GeometryType::Polyline),
    m_polylineData(polyline) {
    m_transform.makeIdentityMatrix();
    CalculateBoundingBox();
}


datGeometry::datGeometry(ofMesh const& mesh) :
    m_type(GeometryType::Mesh),
    m_meshData(mesh) {
    m_transform.makeIdentityMatrix();
    CalculateBoundingBox();
}


datGeometry::datGeometry(datTextString const& textString) :
    m_type(GeometryType::TextString),
    m_textStringData(textString) {
    m_transform.makeIdentityMatrix();
    CalculateBoundingBox();
}


datGeometry::datGeometry(datImage const& image) :
    m_type(GeometryType::Image),
    m_imageData(image) {
    m_transform.makeIdentityMatrix();
    CalculateBoundingBox();
}


datGeometry::datGeometry(ofxAssimpModelLoader const& model) :
    m_type(GeometryType::AssimpModel),
    m_modelData(model) {
    m_transform.makeIdentityMatrix();
    CalculateBoundingBox();
}

datGeometry::datGeometry(datGeometry const& rhs) {
    memcpy(this, &rhs, sizeof(datGeometry));
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


std::unique_ptr<datGeometry> datGeometry::Create(datImage const& image) {
    auto ptr = std::unique_ptr<datGeometry>(new datGeometry(image));
    return std::move(ptr);
}


std::unique_ptr<datGeometry> datGeometry::Create(ofxAssimpModelLoader const& model) {
    auto ptr = std::unique_ptr<datGeometry>(new datGeometry(model));
    return std::move(ptr);
}


std::unique_ptr<datGeometry> datGeometry::Clone() const {
    auto ptr = std::unique_ptr<datGeometry>(new datGeometry(*this));
    return std::move(ptr);
}


void datGeometry::CalculateBoundingBox() {

    switch (m_type) {
        case GeometryType::Polyline: {
            m_boundingBox = datBoundingBox(m_polylineData);
            break;
        }
        case GeometryType::Mesh: {
            m_boundingBox = datBoundingBox(m_meshData);
            break;
        }
        case GeometryType::TextString: {
            ofRectangle rect = m_textStringData.m_trueTypeFont.getStringBoundingBox(m_textStringData.m_text, m_textStringData.m_position.x, m_textStringData.m_position.y);
            m_boundingBox.low = rect.getTopLeft();
            m_boundingBox.high = rect.getBottomRight();
            break;
        }
        case GeometryType::Image: {
            m_boundingBox.InitInvalid();
            const std::vector<ofPoint> corners = m_imageData.Get4Corners();
            for (auto const& corner : corners)
                m_boundingBox.Extend(corner);

            break;
        }
        case GeometryType::AssimpModel: {

            m_boundingBox.Init(m_modelData.getSceneMin(true));
            m_boundingBox.Extend(m_modelData.getSceneMax(true));
            m_boundingBox.Multiply(m_modelData.getNormalizedScale());
            m_boundingBox.Translate(m_modelData.getPosition());
            break;
        }
    }
}


void datGeometry::draw() const {

    ofPushMatrix();
	ofMultMatrix(m_transform);

    switch (m_type) {
        case GeometryType::Polyline:
            {
            // For some reason, calling draw on ofPolyline doesn't apply fill properly
            if (m_polylineData.isClosed()) {
                ofBeginShape();
                for (uint32_t i = 0; i < m_polylineData.getVertices().size(); ++i) {
                    ofVertex(m_polylineData[i].x, m_polylineData[i].y);
                }
                ofEndShape();
            }
            else
                m_polylineData.draw();

            break;
            }
        case GeometryType::Mesh:
            m_meshData.draw();
            break;
        case GeometryType::TextString:
            m_textStringData.draw();
            break;
        case GeometryType::Image:
            m_imageData.draw();
            break;
        case GeometryType::AssimpModel:
            const_cast<ofxAssimpModelLoader&>(m_modelData).drawFaces();
            break;
    }

    ofPopMatrix();
}


void datGeometry::drawWithDisplayParams() const {

    ofSetLineWidth(m_displayParams.lineWidth);

    ofFill();
    ofSetColor(m_displayParams.fillColor);

    draw();

    ofNoFill();
    ofSetColor(m_displayParams.lineColor);

    draw();
}
