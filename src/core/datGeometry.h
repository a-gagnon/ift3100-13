//=======================================================================================
// datGeometry.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"
#include "datBoundingBox.h"
#include "datNonCopyableClass.h"
#include "datTextString.h"
#include "datImage.h"

BEGIN_DAT_NAMESPACE

// Small tolerance for comparisons
#define datEpsilon 1e-03

typedef ofMatrix4x4 Transform;

//=======================================================================================
// Display parameters for geometries
//=======================================================================================
struct datDisplayParams {

public:
    ofColor fillColor;
    ofColor lineColor;
    float lineWidth;
};

//=======================================================================================
// Wrapper for openframeworks geometry classes
//=======================================================================================
struct datGeometry : datNonCopyableClass {

public:
    enum class GeometryType {
        Polyline,
        Mesh,
        TextString,
        Image,
        AssimpModel
    };

private:

    datBoundingBox m_boundingBox;
    Transform m_transform;
    datDisplayParams m_displayParams;

    GeometryType m_type;

    union {
        ofPolyline m_polylineData;
        ofMesh m_meshData;
        datTextString m_textStringData;
        datImage m_imageData;
        ofxAssimpModelLoader m_modelData;
    };

private:
    datGeometry(ofPolyline const& polyline);
    datGeometry(ofMesh const& mesh);
    datGeometry(datTextString const& textString);
    datGeometry(datImage const& image);
    datGeometry(ofxAssimpModelLoader const& model);

public:
    ~datGeometry() {}
    static std::unique_ptr<datGeometry> Create(ofPolyline const& polyline);
    static std::unique_ptr<datGeometry> Create(ofMesh const& mesh);
    static std::unique_ptr<datGeometry> Create(datTextString const& textString);
    static std::unique_ptr<datGeometry> Create(datImage const& image);
    static std::unique_ptr<datGeometry> Create(ofxAssimpModelLoader const& model);

    datBoundingBox GetBoundingBox() const { return m_boundingBox; }
    void CalculateBoundingBox();

    Transform const& GetTransform() const { return m_transform; }
    void SetTransform(Transform const& transform) { m_transform = transform; }

    datDisplayParams const& GetDisplayParams() const { return m_displayParams; }
    void SetDisplayParams(datDisplayParams const& displayParams) { m_displayParams = displayParams; }

    void draw() const;
    void drawWithDisplayParams() const;

    GeometryType GetType() const        { return m_type; }
    ofPolyline& GetAsPolyline()         { assert(GeometryType::Polyline == m_type); return m_polylineData; }
    ofMesh& GetAsMesh()                 { assert(GeometryType::Mesh == m_type); return m_meshData; }
    datTextString& GetAsTextString()    { assert(GeometryType::TextString == m_type); return m_textStringData; }
    datImage& GetAsImage()              { assert(GeometryType::Image == m_type); return m_imageData; }
    ofxAssimpModelLoader& GetAsModel()  { assert(GeometryType::AssimpModel == m_type); return m_modelData; }
};


END_DAT_NAMESPACE
