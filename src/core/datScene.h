//=======================================================================================
// datScene.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datId.h"
#include "datNonCopyableClass.h"
#include "datElement.h"
#include "datEvents.h"
#include "datBVHierarchy.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Scene holds every element that is in memory
//=======================================================================================
struct datScene : datNonCopyableClass {

    typedef std::map<datId, std::unique_ptr<datElement>> ElementMap;

private:
    uint32_t m_nextId;

    std::vector<ElementMap> m_undoStack;
    std::vector<ElementMap> m_redoStack;
    ofEvent<void> m_onUndoRedoStatusChangedEvent;

    ElementMap m_elementMap;
    datBVHierarchy m_boundingVolumeHierarchy;

    std::set<datId> m_selectionSet;
    ofEvent<void> m_onSelectionChangedEvent;

private:
    datId GetNextId();
    void CloneSourceInDest(ElementMap& dest, ElementMap const& source) const;
    void RecalculateBVHierarchy();
    void SetLightsState(ElementMap& map, bool enabledDisabled);
    
public:
    datScene();
    ~datScene();

    datElement const* GetElement(datId id) const;
    datId InsertElement(std::unique_ptr<datElement>&& element);
    void UpdateElements(std::vector<std::unique_ptr<datElement>>&& elements);
    void DeleteElements(std::set<datId> const& ids);

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

    std::vector<datElement const*> QueryAllElements() const;
    std::vector<datElement const*> QueryElements(datBoundingBox const& box, bool strictlyInside) const;
};

END_DAT_NAMESPACE
