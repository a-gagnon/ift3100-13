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
    
	std::set<datId> m_neverDraw;
    datDisplayParams m_activeDisplayParams;
    CursorType m_activeCursorType;
    bool m_drawBoundingBox;
    bool m_drawSelectedInHilite;

public:
    datRenderer(datScene& scene);
    ~datRenderer();

	datScene& GetScene() { return m_scene; }

	void Render() const;
    void DrawCursorType() const;
    void DrawGeometry(datGeometry const& geometry, bool useDisplayParams = true) const;
    void DrawBoundingBox(datGeometry const& geometry) const;

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
