//=======================================================================================
// datGeometry.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDefinitions.h"
#include "datNonCopyableClass.h"
#include "datTextString.h"
#include "datImage.h"

BEGIN_DAT_NAMESPACE

// Small tolerance for comparisons
#define datEpsilon 1e-03


//=======================================================================================
// Wrapper for openframeworks geometry classes
//=======================================================================================
struct datGeometry : datNonCopyableClass {

public:
    enum class GeometryType {
        Polyline,
        Mesh,
        TextString,
        Image
    };

private:
    ofColor m_color;
    GeometryType m_type;

    union {
        ofPolyline m_polylineData;
        ofMesh m_meshData;
        datTextString m_textStringData;
        datImage m_imageData;
    };

private:
    datGeometry(ofPolyline const& polyline);
    datGeometry(ofMesh const& mesh);
    datGeometry(datTextString const& textString);
    datGeometry(datImage const& image);

public:
    ~datGeometry() {}
    static std::unique_ptr<datGeometry> Create(ofPolyline const& polyline);
    static std::unique_ptr<datGeometry> Create(ofMesh const& mesh);
    static std::unique_ptr<datGeometry> Create(datTextString const& textString);
    static std::unique_ptr<datGeometry> Create(datImage const& image);

    void SetColor(ofColor const& color) { m_color = color; }
    ofColor const& GetColor() const { return m_color; }

    GeometryType GetType() const        { return m_type; }
    ofPolyline& GetAsPolyline()         { assert(GeometryType::Polyline == m_type); return m_polylineData; }
    ofMesh& GetAsMesh()                 { assert(GeometryType::Mesh == m_type); return m_meshData; }
    datTextString& GetAsTextString()    { assert(GeometryType::TextString == m_type); return m_textStringData; }
    datImage& GetAsImage()              { assert(GeometryType::Image == m_type); return m_imageData; }

    void draw() const;
};


END_DAT_NAMESPACE
