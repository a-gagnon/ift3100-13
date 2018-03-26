//=======================================================================================
// datId.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// When a geometry is added to the scene, it is given a SceneId by the scene
// When a geometry is cloned for editing, it keeps its Id, so we can track
// changes when adding it back to the scene
//=======================================================================================
struct datId {

private:
    uint32_t m_id;

public:
    datId() : m_id(0) {}
    datId(uint32_t id) : m_id(id) {}

    bool operator< (datId const& rhs) const { return m_id < rhs.m_id; }
    bool operator==(datId const& rhs) const { return m_id == rhs.m_id; }
    bool IsValid() const { return 0 != m_id; }
    void Invalidate() { m_id = 0; }
};

END_DAT_NAMESPACE
