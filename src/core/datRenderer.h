//=======================================================================================
// datRenderer.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datNonCopyableClass.h"
#include "datEvents.h"
#include "datGeometry.h"
#include "datSelectionSet.h"

BEGIN_DAT_NAMESPACE

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
    std::vector<std::unique_ptr<datGeometry>> m_geometries;
    datSelectionSet m_selectionSet;
    
    datDisplayParams m_activeDisplayParams;
    CursorType m_activeCursorType;
    bool m_displayBoundingBox;
    bool m_drawSelectedInHilite;

private:
    // Returns the visible entries given current transform
    std::vector<datGeometry*> GetVisibleGeometries() const;

public:
    datRenderer();
    ~datRenderer();

    // Adds a geometry to the renderer. Source is cleared
    void AddGeometry(std::unique_ptr<datGeometry>&& geometry);
    void RemoveGeometry(datGeometry* pGeometry);
    std::vector<datGeometry*> QueryGeometries(datBoundingBox const& boundingBox) const;

    void Render() const;
    void DrawCursorType() const;
    void DrawGeometry(datGeometry const& geometry, bool useDisplayParams = true) const;
    void DrawBoundingBox(datGeometry const& geometry) const;

    datSelectionSet& GetSelectionSet() { return m_selectionSet; }

    void SetActiveDisplayParams(datDisplayParams const& displayParams) { m_activeDisplayParams = displayParams; }
    datDisplayParams& GetActiveDisplayParamsR() { return m_activeDisplayParams; }
    datDisplayParams const& GetActiveDisplayParams() const { return m_activeDisplayParams; }

    CursorType GetActiveCursorType() const { return m_activeCursorType; }
    void SetActiveCursorType(CursorType type) { m_activeCursorType = type; }

    ofColor GetBackgroundColor() const { return ofGetBackgroundColor(); }
    void SetBackgroundColor(ofColor const& color) { ofSetBackgroundColor(color); }

    bool GetDisplayBoundingBox() const { return m_displayBoundingBox; }
    void SetDisplayBoundingBox(bool yesNo) { m_displayBoundingBox = yesNo; }

    void SetDrawSelectedInHilite(bool yesNo) { m_drawSelectedInHilite = yesNo;  }
};

END_DAT_NAMESPACE
