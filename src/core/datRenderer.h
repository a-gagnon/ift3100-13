//=======================================================================================
// datRenderer.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datNonCopyableClass.h"
#include "datEvents.h"
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
        Normal  = 1,
        Circle  = 2, // 'o'
        X       = 3, // 'x'
        Cross   = 4, // '+'
        Triangle = 5
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
    CursorType m_activeCursorType;
    
private:
    // Returns the visible entries given current transform
    std::vector<Entry*> GetVisibleEntries() const;

public:
    datRenderer();
    ~datRenderer();
    static datRenderer& GetActiveRenderer();

    void GrabMouseEvent(datMouseEvent const& ev);

    // Adds a geometry to the renderer. Source is cleared
    void AddGeometry(std::unique_ptr<datGeometry>& geometry);
    void Render() const;
    void DrawCursorType() const;

    ofColor GetActiveDrawColor() const { return m_activeDrawColor; }
    void SetActiveDrawColor(ofColor const& color) { m_activeDrawColor = color; }

    CursorType GetActiveCursorType() const { return m_activeCursorType; }
    void SetActiveCursorType(CursorType type) { m_activeCursorType = type; }
};

END_DAT_NAMESPACE
