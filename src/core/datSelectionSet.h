//=======================================================================================
// datSelectionSet.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"
#include "datGeometry.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// This class is used to keep track of selected elements
//=======================================================================================
struct datSelectionSet {

private:
    std::set<datGeometry*> m_selection;
    ofEvent<void> m_onSelectionChangedEvent;

public:
    datSelectionSet();
    ~datSelectionSet();

    void SetSelection(std::vector<datGeometry*> const& geometries);
    void RemoveFromSelection(datGeometry* pGeometry, bool sendEvent = true);
    void ClearSelection();
    bool IsSelected(datGeometry* pGeometry) const;

    std::set<datGeometry*> const& GetSelection() const { return m_selection; }
    ofEvent<void>& GetSelectionChangedEvent() { return m_onSelectionChangedEvent; }
};

END_DAT_NAMESPACE
