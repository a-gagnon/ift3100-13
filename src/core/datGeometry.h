//=======================================================================================
// datGeometry.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"
#include "datBoundingBox.h"
#include "datId.h"
#include "datNonCopyableClass.h"
#include "datTextString.h"
#include "datImage.h"
#include "datTransform.h"

BEGIN_DAT_NAMESPACE

// Small tolerance for comparisons
#define datEpsilon 1e-03

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
struct datGeometry {

public:
    enum class GeometryType {
        Polyline,
        Mesh,
        TextString,
        Image,
        AssimpModel
    };

private:

    datId m_id;
    datBoundingBox m_boundingBox;
    datTransform m_transform;
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
    datGeometry(datGeometry const&);
    datGeometry& operator= (datGeometry const&) = delete;


public:
    ~datGeometry() {}
    static std::unique_ptr<datGeometry> Create(ofPolyline const& polyline);
    static std::unique_ptr<datGeometry> Create(ofMesh const& mesh);
    static std::unique_ptr<datGeometry> Create(datTextString const& textString);
    static std::unique_ptr<datGeometry> Create(datImage const& image);
    static std::unique_ptr<datGeometry> Create(ofxAssimpModelLoader const& model);

    std::unique_ptr<datGeometry> Clone() const;

    // only scene should call this
    void AssignId(datId id) { m_id = id; }
    datId GetId() const { return m_id; }

	datBoundingBox const& GetBoundingBox() const { return m_boundingBox; }
    void CalculateBoundingBox();

    datTransform const& GetTransform() const { return m_transform; }
    void SetTransform(datTransform const& transform) { m_transform = transform; }

    datDisplayParams const& GetDisplayParams() const { return m_displayParams; }
    datDisplayParams& GetDisplayParamsR() { return m_displayParams; }
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
