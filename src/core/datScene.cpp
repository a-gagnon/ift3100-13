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


void datScene::CloneSourceInDest(GeometryMap& dest, GeometryMap const& source) const {
    for (auto const& entry : source) {
        dest[entry.first] = entry.second->Clone();
    }
}


void datScene::RecalculateBVHierarchy() {
    const std::vector<datGeometry const*> geometries = QueryAllGeometries();
    m_boundingVolumeHierarchy.Build(geometries);
}


void datScene::SetLightsState(GeometryMap& map, bool enabledDisabled) {

    for (auto& entry : map) {

        if (datGeometry::GeometryType::Light == entry.second->GetType()) {
            ofLight& light = entry.second->GetAsLight();

            if (enabledDisabled)
                light.enable();
            else
                light.disable();
        }
    }

}



datGeometry const* datScene::GetGeometry(datId id) const {

    auto it = m_geometryMap.find(id);
    if (it != m_geometryMap.end())
        return it->second.get();

    return nullptr;
}


datId datScene::InsertGeometry(std::unique_ptr<datGeometry>&& geometry) {

    assert(!geometry->GetId().IsValid());

    GeometryMap copy;
    CloneSourceInDest(copy, m_geometryMap);
    m_undoStack.push_back(std::move(copy));
    m_redoStack.clear();

    const datId id = GetNextId();
    geometry->AssignId(id);
    m_geometryMap.insert(std::make_pair(id, std::move(geometry)));
    geometry.reset();

    RecalculateBVHierarchy();
    ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
    return id;
}


void datScene::UpdateMultipleGeometries(std::vector<std::unique_ptr<datGeometry>>&& geometries) {

    GeometryMap copy;
    CloneSourceInDest(copy, m_geometryMap);
    m_undoStack.push_back(std::move(copy));
    m_redoStack.clear();
    
    for (auto& geometry : geometries) {
        assert(geometry->GetId().IsValid());
        m_geometryMap[geometry->GetId()] = std::move(geometry);
    }

    geometries.clear();
    RecalculateBVHierarchy();
    ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
}


void datScene::DeleteMultipleGeometries(std::set<datId> const& ids) {

    GeometryMap copy;
    CloneSourceInDest(copy, m_geometryMap);
    m_undoStack.push_back(std::move(copy));
    m_redoStack.clear();

    for (auto const& id : ids) {
        m_geometryMap.erase(id);
    }

    RecalculateBVHierarchy();
    ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
}


void datScene::Undo() {

    if (!m_undoStack.empty()) {
        SetLightsState(m_geometryMap, false);               // Turn off lights
        m_redoStack.push_back(std::move(m_geometryMap));    // move geometries to redo stack
        m_geometryMap = std::move(m_undoStack.back());      // restore geometries from undo stack
        m_undoStack.pop_back();                             // remove entry from undo stack
        SetLightsState(m_geometryMap, true);                // Turn on active lights
        RecalculateBVHierarchy();
        ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
    }
}


void datScene::Redo() {

    if (!m_redoStack.empty()) {
        SetLightsState(m_geometryMap, false);               // Turn off lights
        m_undoStack.push_back(std::move(m_geometryMap));    // move geometries to undo stack
        m_geometryMap = std::move(m_redoStack.back());      // restore geometries from redo stack
        m_redoStack.pop_back();                             // remove entry from redo stack
        SetLightsState(m_geometryMap, true);                // Turn on active lights
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


std::vector<datGeometry const*> datScene::QueryAllGeometries() const {

    std::vector<datGeometry const*> results;

    for (auto const& entry : m_geometryMap) {
        results.push_back(entry.second.get());
    }

    return results;
}


std::vector<datGeometry const*> datScene::QueryGeometries(datBoundingBox const& box, bool strictlyInside) const {

    const std::set<datId> ids = m_boundingVolumeHierarchy.Query(box, strictlyInside);
    std::vector<datGeometry const*> results;

    for (auto const& id : ids) {
        results.push_back(m_geometryMap.find(id)->second.get());
    }

    return results;
}

