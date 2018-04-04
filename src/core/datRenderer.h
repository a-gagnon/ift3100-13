//=======================================================================================
// datRenderer.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datNonCopyableClass.h"
#include "datEvents.h"
#include "datGeometry.h"
#include "datScene.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Simple viewport class
//=======================================================================================
struct datViewport {

public:
    ofEasyCam camera;
    ofRectangle rect;

    ofPoint GetRectCenter() const { return rect.getCenter(); }
    datBoundingBox GetWorldBox() const;
};

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
    datScene& m_scene;
    std::vector<datGeometry*> m_transients;
    std::vector<datViewport> m_viewports;

    std::set<datId> m_neverDraw;
    datDisplayParams m_activeDisplayParams;
    CursorType m_activeCursorType;
    bool m_drawBoundingBox;
    bool m_drawSelectedInHilite;

private:
    void AddViewport();
    void DrawCursorType() const;
    void DrawBoundingBox(datGeometry const& geometry) const;

public:
    datRenderer(datScene& scene);
    ~datRenderer();

    datScene& GetScene() { return m_scene; }

    datViewport& GetFirstViewport() { return m_viewports[0]; }
    datViewport& GetViewport(size_t index)  { assert(index < m_viewports.size()); return m_viewports[index]; }
    size_t GetViewportIndex(ofPoint const& viewPoint) const;
    void SetUseTwoViewports(bool yesNo);
    bool GetUseTwoViewports() const { return 2 == m_viewports.size(); }
    void ResizeViewports();
    void SetUseOrthoCamera(bool yesNo); // true = orthographic, false = perspective


    void Render();

    void AddTransient(datGeometry* transient) { m_transients.push_back(transient); }
    void ClearTransients() { m_transients.clear(); }

    void SetNeverDraw(std::set<datId> const& ids) { m_neverDraw = ids; }
    void ClearNeverDraw() { m_neverDraw.clear(); }
    bool IsNeverDraw(datId id) const { return m_neverDraw.find(id) != m_neverDraw.end(); }

    void SetActiveDisplayParams(datDisplayParams const& displayParams) { m_activeDisplayParams = displayParams; }
    datDisplayParams& GetActiveDisplayParamsR() { return m_activeDisplayParams; }
    datDisplayParams const& GetActiveDisplayParams() const { return m_activeDisplayParams; }

    CursorType GetActiveCursorType() const { return m_activeCursorType; }
    void SetActiveCursorType(CursorType type) { m_activeCursorType = type; }

    ofColor GetBackgroundColor() const { return ofGetBackgroundColor(); }
    void SetBackgroundColor(ofColor const& color) { ofSetBackgroundColor(color); }

    bool GetDrawBoundingBox() const { return m_drawBoundingBox; }
    void SetDrawBoundingBox(bool yesNo) { m_drawBoundingBox = yesNo; }

    void SetDrawSelectedInHilite(bool yesNo) { m_drawSelectedInHilite = yesNo;  }
};

END_DAT_NAMESPACE
