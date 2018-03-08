//=======================================================================================
// datSelectionSet.cpp
// IFT3100-13
//=======================================================================================
#include "datSelectionSet.h"

USING_DAT_NAMESPACE

datSelectionSet::datSelectionSet() {

}


datSelectionSet::~datSelectionSet() {

}


void datSelectionSet::SetSelection(std::vector<datGeometry*> const& geometries) {

    m_selection.clear();
    for (auto const& geometry : geometries)
        m_selection.insert(geometry);

    ofNotifyEvent(m_onSelectionChangedEvent);
}


void datSelectionSet::RemoveFromSelection(datGeometry* pGeometry, bool sendEvent) {
    m_selection.erase(pGeometry);

    if (sendEvent)
        ofNotifyEvent(m_onSelectionChangedEvent);
}


void datSelectionSet::ClearSelection() {

    bool wasEmpty = m_selection.empty();
    m_selection.clear();

    if (!wasEmpty)
        ofNotifyEvent(m_onSelectionChangedEvent);

}


bool datSelectionSet::IsSelected(datGeometry* pGeometry) const {
    return m_selection.end() != m_selection.find(pGeometry);
}


