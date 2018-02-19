//=======================================================================================
// datRenderer.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datNonCopyableClass.h"
#include "datGeometry.h"

BEGIN_DAT_NAMESPACE

// Refer to a 4x4 matrix as a 'Transform'
typedef ofMatrix4x4 Transform;

//=======================================================================================
// Class that takes care of rendering graphical objects to screen
// The app is expected to hold the renderer
//=======================================================================================
struct datRenderer : datNonCopyableClass {

public:
    enum class CursorType {
        Normal,
        Dot,        // '.'
        Cross,      // '+'
        X,          // 'x'
        Circle,     // 'o'
        Square,     // '[]' rect += 5 pixels around cursor point?
    };


private:
    //=======================================================================================
    struct Entry {
    
    private:
        Transform m_worldToGeometry;
        std::unique_ptr<datGeometry> m_geometry;

    public:
        Entry(std::unique_ptr<datGeometry>& geometry);
        ~Entry();

        Transform const& GetWorldToGeometryTransform() const { return m_worldToGeometry; }
        datGeometry const& GetGeometry() const { return *m_geometry; }
    };


private:
    static datRenderer* s_activeRenderer; // pointer to active renderer or nullptr
    std::vector<std::unique_ptr<Entry>> m_entries;
    
    ofVec2f m_cursorCoordinates;
    ofColor m_activeDrawColor;
    
private:
    // Returns the visible entries given current transform
    std::vector<Entry*> GetVisibleEntries() const;
    void drawCursorType() const;

public:
    datRenderer();
    ~datRenderer();
    static datRenderer& GetActiveRenderer();

    // Adds a geometry to the renderer. Source is cleared
    void addGeometry(std::unique_ptr<datGeometry>& geometry);

    void setCoordinates(ofVec2f const& coordinates) { m_cursorCoordinates = coordinates; }
    void render();

    ofColor getActiveDrawColor() const { return m_activeDrawColor; }
    void setActiveDrawColor(ofColor const& color) { m_activeDrawColor = color; }
};

END_DAT_NAMESPACE
