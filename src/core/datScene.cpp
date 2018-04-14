//=======================================================================================
// datScene.cpp
// IFT3100-13
//=======================================================================================
#pragma once

#include "datScene.h"

USING_DAT_NAMESPACE

datScene::datScene():
    m_nextId(1) {
}


datScene::~datScene() {

}


datId datScene::GetNextId() {
    return datId(m_nextId++);
}


void datScene::CloneSourceInDest(ElementMap& dest, ElementMap const& source) const {
    for (auto const& entry : source) {
        dest[entry.first] = entry.second->Clone();
    }
}


void datScene::RecalculateBVHierarchy() {
    const std::vector<datElement const*> elements = QueryAllElements();
    m_boundingVolumeHierarchy.Build(elements);
}


void datScene::SetLightsState(ElementMap& map, bool enabledDisabled) {

    for (auto& entry : map) {

        if (nullptr == entry.second->ToLightElement())
            continue;

    datLight* pLight = static_cast<datLight*>(entry.second.get());
    pLight->SetEnabled(enabledDisabled);
    }
}



datElement const* datScene::GetElement(datId id) const {

    auto it = m_elementMap.find(id);
    if (it != m_elementMap.end())
        return it->second.get();

    return nullptr;
}


datId datScene::InsertElement(std::unique_ptr<datElement>&& element) {

    assert(!element->GetId().IsValid());

    ElementMap copy;
    CloneSourceInDest(copy, m_elementMap);
    m_undoStack.push_back(std::move(copy));
    m_redoStack.clear();

    const datId id = GetNextId();
    element->AssignId(id);
    m_elementMap.insert(std::make_pair(id, std::move(element)));
    element.reset();

    RecalculateBVHierarchy();
    ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
    return id;
}


void datScene::UpdateElements(std::vector<std::unique_ptr<datElement>>&& elements) {

    ElementMap copy;
    CloneSourceInDest(copy, m_elementMap);
    m_undoStack.push_back(std::move(copy));
    m_redoStack.clear();
    
    for (auto& element : elements) {
        assert(element->GetId().IsValid());
        m_elementMap[element->GetId()] = std::move(element);
    }

    elements.clear();
    RecalculateBVHierarchy();
    ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
}


void datScene::DeleteElements(std::set<datId> const& ids) {

    ElementMap copy;
    CloneSourceInDest(copy, m_elementMap);
    m_undoStack.push_back(std::move(copy));
    m_redoStack.clear();

    for (auto const& id : ids) {
        m_elementMap.erase(id);
    }

    RecalculateBVHierarchy();
    ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
}


void datScene::Undo() {

    if (!m_undoStack.empty()) {
        SetLightsState(m_elementMap, false);                // Turn off lights
        m_redoStack.push_back(std::move(m_elementMap));     // move elements to redo stack
        m_elementMap = std::move(m_undoStack.back());       // restore elements from undo stack
        m_undoStack.pop_back();                             // remove entry from undo stack
        SetLightsState(m_elementMap, true);                 // Turn on active lights
        RecalculateBVHierarchy();
        ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
    }
}


void datScene::Redo() {

    if (!m_redoStack.empty()) {
        SetLightsState(m_elementMap, false);                // Turn off lights
        m_undoStack.push_back(std::move(m_elementMap));     // move elements to undo stack
        m_elementMap = std::move(m_redoStack.back());       // restore elements from redo stack
        m_redoStack.pop_back();                             // remove entry from redo stack
        SetLightsState(m_elementMap, true);                 // Turn on active lights
        RecalculateBVHierarchy();
        ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
    }
}


bool datScene::IsSelected(datId id) {
    return m_selectionSet.find(id) != m_selectionSet.end();
}


void datScene::AddToSelection(datId id) {

    auto result = m_selectionSet.insert(id);

    if (result.second) {
        ofNotifyEvent(m_onSelectionChangedEvent);
    }
}


void datScene::RemoveFromSelection(datId id) {

    if (m_selectionSet.find(id) != m_selectionSet.end()) {
        m_selectionSet.erase(id);
        ofNotifyEvent(m_onSelectionChangedEvent);
    }
}


void datScene::SetSelection(std::set<datId> const& ids) {

    m_selectionSet = ids;
    ofNotifyEvent(m_onSelectionChangedEvent);
}


void datScene::ClearSelection() {

    const bool hasEntries = 0 < m_selectionSet.size();
    m_selectionSet.clear();

    if (hasEntries) {
        ofNotifyEvent(m_onSelectionChangedEvent);
    }
}


std::vector<datElement const*> datScene::QueryAllElements() const {

    std::vector<datElement const*> results;

    for (auto const& entry : m_elementMap) {
        results.push_back(entry.second.get());
    }

    return results;
}


std::vector<datElement const*> datScene::QueryElements(datBoundingBox const& box, bool strictlyInside) const {

    const std::set<datId> ids = m_boundingVolumeHierarchy.Query(box, strictlyInside);
    std::vector<datElement const*> results;

    for (auto const& id : ids) {
        results.push_back(m_elementMap.find(id)->second.get());
    }

    return results;
}


std::vector<datElement const*> datScene::QueryHitElements(datRay const& ray) const {

    // Quickly eliminate some geometries that would not intersect anyway
    datBoundingBox box;
    box.Extend(ray.GetOrigin());
    box.Extend(ray.GetOrigin() + (1E10 * ray.GetDirection()));

    std::vector<datElement  const*> candidateResults = QueryElements(box, false);
    std::vector<datElement const*> results;

    for (auto const& candidateResult : candidateResults) {

        if (candidateResult->IsHitByRay(ray)) {
            results.push_back(candidateResult);
        }
    }

    return results;
}
