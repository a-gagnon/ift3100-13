//=======================================================================================
// datQuadTree.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"
#include "datElement.h"
#include "datBoundingBox.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
// Implementation of a Bounding Volume Hierarchy (BVH)
//=======================================================================================
struct datBVHierarchy {

private:
    datBoundingBox m_box;
    datId m_id;

    std::unique_ptr<datBVHierarchy> m_left;
    std::unique_ptr<datBVHierarchy> m_right;

    void _Query(std::set<datId>& ids, datBoundingBox const& box, bool strictlyInside) const;

public:
    datBVHierarchy();
    ~datBVHierarchy();

    void Clear();
    void Build(std::vector<datElement const*> elements);

    std::set<datId> Query(datBoundingBox const& box, bool strictlyInside) const;
};

END_DAT_NAMESPACE
