//=======================================================================================
// datRenderer.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datNonCopyableClass.h"
#include "datElement.h"
#include "datEvents.h"
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
    datBoundingBox GetWorldBox(ofPoint viewMin, ofPoint viewMax) const;
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
    std::vector<datElement*> m_transients;
    std::vector<datViewport> m_viewports;

    std::set<datId> m_neverDraw;
    datDisplayParams m_activeDisplayParams;
    CursorType m_activeCursorType;
    bool m_drawBoundingBox;
    bool m_drawSelectedInHilite;
    bool m_isLightingEnabled;

    ofMaterial m_material1;
    ofMaterial m_material2;
    ofMaterial m_material3;

private:
    void InitMaterials();
    void AddViewport();
    void DrawCursorType() const;
    void DrawBoundingBox(datElement const& element) const;

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

    void RenderElement(datElement const& element, bool useDisplayParams);
    void Render();

    void AddTransient(datElement* transient) { m_transients.push_back(transient); }
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

    bool GetIsLightingEnabled() const { return m_isLightingEnabled; }
    void SetLighting(bool yesNo) { m_isLightingEnabled = yesNo; }

    ofMaterial const& GetMaterial1() const { return m_material1; }
    ofMaterial const& GetMaterial2() const { return m_material2; }
    ofMaterial const& GetMaterial3() const { return m_material3; }
};

END_DAT_NAMESPACE
