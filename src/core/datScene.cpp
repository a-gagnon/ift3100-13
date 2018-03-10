//=======================================================================================
// datScene.cpp
// IFT3100-13
//=======================================================================================
#pragma once

#include "datScene.h"

USING_DAT_NAMESPACE

datScene::datScene():
	m_nextId(1) {
	m_worldToView.makeIdentityMatrix();
	m_viewToWorld.makeIdentityMatrix();
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


void datScene::SetWorldToView(datTransform const& transform) {
    m_worldToView = transform;
    m_viewToWorld.makeInvertOf(transform);
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

	ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
}


void datScene::Undo() {

	if (!m_undoStack.empty()) {
		m_redoStack.push_back(std::move(m_geometryMap));
		m_geometryMap = std::move(m_undoStack.back());
		m_undoStack.pop_back();
		ofNotifyEvent(m_onUndoRedoStatusChangedEvent);
	}
}


void datScene::Redo() {

	if (!m_redoStack.empty()) {
		m_undoStack.push_back(std::move(m_geometryMap));
		m_geometryMap = std::move(m_redoStack.back());
		m_redoStack.pop_back();
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


std::vector<datGeometry const*> datScene::QueryGeometries() const {

	std::vector<datGeometry const*> results;

	//&&AG return all elements for now.
	// We might want to filter out based on the position of the element and current view parameters!
	for (auto const& entry : m_geometryMap) {
		results.push_back(entry.second.get());
	}

	return results;
}


std::vector<datGeometry const*> datScene::QueryGeometries(datBoundingBox const& box, bool strictlyInside) const {

	std::vector<datGeometry const*> results;

	for (auto const& entry : m_geometryMap) {

		datBoundingBox geometryBox = entry.second->GetBoundingBox();
		entry.second->GetTransform().Multiply(geometryBox);
		
		if (box.Intersects(geometryBox, strictlyInside))
			results.push_back(entry.second.get());
	}

	return results;
}
