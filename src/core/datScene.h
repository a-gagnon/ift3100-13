//=======================================================================================
// datScene.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datId.h"
#include "datNonCopyableClass.h"
#include "datEvents.h"
#include "datGeometry.h"
#include "datSelectionSet.h"
#include "datTransform.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Scene holds every geometry that is in memory
// Scene keeps the current transforms
//=======================================================================================
struct datScene : datNonCopyableClass {

private:
    datTransform m_worldToView;
    datTransform m_viewToWorld;

    std::map<datId, std::unique_ptr<datGeometry>> m_geometryMap;
    std::set<datGeometry*> m_selectionSet;
    ofEvent<void> m_onSelectionChangedEvent;


public:
    datScene();
    ~datScene();

    datTransform const& GetViewToWorld() const { return m_viewToWorld; }
    datTransform const& GetWorldToView() const { return m_worldToView; }
    void SetWorldToView(datTransform const& transform);
    
    void InsertGeometry(std::unique_ptr<datGeometry>&& geometry);
    void UpdateGeometry(std::unique_ptr<datGeometry>&& geometry);
    void UpdateMultipleGeometries(std::vector<std::unique_ptr<datGeometry>> geometries);
    void DeleteGeometry(datGeometry* geometry);


    std::set<datGeometry*> const& GetSelectionSet() const { return m_selectionSet; }
    ofEvent<void>& GetOnSelectionChangedEvent() { return m_onSelectionChangedEvent; }
    void AddToSelection(datGeometry* geometry);
    void RemoveFromSelection(datGeometry* geometry);



};

END_DAT_NAMESPACE
