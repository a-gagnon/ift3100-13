//=======================================================================================
// datScene.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datId.h"
#include "datNonCopyableClass.h"
#include "datEvents.h"
#include "datGeometry.h"
#include "datTransform.h"
#include "datBVHierarchy.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Scene holds every geometry that is in memory
// Scene keeps the current transforms
//=======================================================================================
struct datScene : datNonCopyableClass {

    typedef std::map<datId, std::unique_ptr<datGeometry>> GeometryMap;

private:
    uint32_t m_nextId;
    datTransform m_worldToView;
    datTransform m_viewToWorld;

    std::vector<GeometryMap> m_undoStack;
    std::vector<GeometryMap> m_redoStack;
    ofEvent<void> m_onUndoRedoStatusChangedEvent;

    GeometryMap m_geometryMap;
    datBVHierarchy m_boundingVolumeHierarchy;

    std::set<datId> m_selectionSet;
    ofEvent<void> m_onSelectionChangedEvent;

private:
    datId GetNextId();
    void CloneSourceInDest(GeometryMap& dest, GeometryMap const& source) const;
    void RecalculateBVHierarchy();
    
public:
    datScene();
    ~datScene();

    datTransform const& GetViewToWorld() const { return m_viewToWorld; }
    datTransform const& GetWorldToView() const { return m_worldToView; }
    void SetWorldToView(datTransform const& transform);
    
    datGeometry const* GetGeometry(datId id) const;
    datId InsertGeometry(std::unique_ptr<datGeometry>&& geometry);
    void UpdateMultipleGeometries(std::vector<std::unique_ptr<datGeometry>>&& geometries);
    void DeleteMultipleGeometries(std::set<datId> const& ids);

    bool CanUndo() const { return !m_undoStack.empty(); }
    bool CanRedo() const { return !m_redoStack.empty(); }
    void Undo();
    void Redo();
    ofEvent<void>& GetOnUndoRedoStatusChangedEvent() { return m_onUndoRedoStatusChangedEvent; }

    std::set<datId> const& GetSelection() const { return m_selectionSet; }
    ofEvent<void>& GetOnSelectionChangedEvent() { return m_onSelectionChangedEvent; }
    bool IsSelected(datId id);
    void AddToSelection(datId id);
    void RemoveFromSelection(datId id);
    void SetSelection(std::set<datId> const& ids);
    void ClearSelection();

    std::vector<datGeometry const*> QueryAllGeometries() const;
    std::vector<datGeometry const*> QueryGeometries(datBoundingBox const& box, bool strictlyInside) const;
};

END_DAT_NAMESPACE
