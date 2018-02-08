//=======================================================================================
// datGeometry.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../datDefinitions.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
//&&AG NEEDSWORK. Make a better wrapper for text strings!
struct datText {

public:
    ofTrueTypeFont m_ttf;
    std::string m_text;
    ofVec2f m_position;

public:
    ~datText() {}
    datText(ofTrueTypeFont const& ttf, std::string const& text, ofVec2f const& position) :
        m_ttf(ttf), m_text(text), m_position(position) {}

    void draw() { m_ttf.drawString(m_text, m_position.x, m_position.y); }
};


//=======================================================================================
// Wrapper for openframeworks geometry classes
//=======================================================================================
struct datGeometry : NonCopyableClass {

public:
    enum class GeometryType {
        Polyline,
        Mesh,
        Text
    };

private:
    ofColor m_color;
    GeometryType m_type;

    union {
        ofPolyline m_polylineData;
        ofMesh m_meshData;
        datText m_textData;
    };

public:
    datGeometry(ofPolyline const& polyline);
    datGeometry(ofMesh const& mesh);
    datGeometry(datText const& text);
    ~datGeometry() {}

    void SetColor(ofColor const& color) { m_color = color; }
    ofColor const& GetColor() const { return m_color; }

    GeometryType GetType() const    { return m_type; }
    ofPolyline& GetAsPolyline()     { assert(GeometryType::Polyline == m_type); return m_polylineData; }
    ofMesh& GetAsMesh()             { assert(GeometryType::Mesh == m_type); return m_meshData; }
    datText& GetAsText()            { assert(GeometryType::Text == m_type); return m_textData; }

    void draw();
};


//&&AG NEEDSWORK even more
// Static cache for geometry.. until we have some persistence
//=======================================================================================
struct GeometryCache {

private:
    std::vector<std::unique_ptr<datGeometry>> m_geometries;

    GeometryCache() {}
    ~GeometryCache() {}

public:
    static GeometryCache& GetCache();
    void addGeometry(datGeometry* pGeometry);
    void drawCachedGeometries();
};

END_DAT_NAMESPACE
