//=======================================================================================
// datBVHierarchy.cpp
// IFT3100-13
//=======================================================================================
#include "datBVHierarchy.h"

USING_DAT_NAMESPACE

datBVHierarchy::datBVHierarchy() :
    m_left(nullptr),
    m_right(nullptr) {
}


datBVHierarchy::~datBVHierarchy() {

}


void datBVHierarchy::Clear() {
    m_box.InitInvalid();
    m_id.Invalidate();
    m_left.reset();
    m_right.reset();
}

void datBVHierarchy::Build(std::vector<datGeometry const*> geometries) {

    Clear();

    if (geometries.empty())
        return;

    for (auto const& geometry : geometries) {
        m_box.Extend(geometry->GetBoundingBox());
    }


    if (1 == geometries.size()) {
        m_id = geometries.front()->GetId();
        return;
    }
    
    // More than 1 entry to place. Find longest axis and sort
    const float xLength = m_box.GetXLength();
    const float yLength = m_box.GetYLength();
    const float zLength = m_box.GetZLength();

    if (xLength > yLength && xLength > zLength) {
        std::sort(geometries.begin(), geometries.end(), [](datGeometry const* lhs, datGeometry const* rhs)
        { return lhs->GetBoundingBox().GetCenter().x < rhs->GetBoundingBox().GetCenter().x; });
    }
    else if (yLength > xLength && yLength > zLength) {
        std::sort(geometries.begin(), geometries.end(), [](datGeometry const* lhs, datGeometry const* rhs)
        { return lhs->GetBoundingBox().GetCenter().y < rhs->GetBoundingBox().GetCenter().y; });
    }
    else { // zLength
        std::sort(geometries.begin(), geometries.end(), [](datGeometry const* lhs, datGeometry const* rhs)
        { return lhs->GetBoundingBox().GetCenter().z < rhs->GetBoundingBox().GetCenter().z; });
    }

    
    size_t halfSize = geometries.size() / 2;
    std::vector<datGeometry const*> leftGeometries;
    leftGeometries.insert(leftGeometries.end(), geometries.begin(), geometries.begin() + halfSize);
    std::vector<datGeometry const*> rightGeometries;
    rightGeometries.insert(rightGeometries.end(), geometries.begin() + halfSize, geometries.end());

    m_left = std::make_unique<datBVHierarchy>();
    m_left->Build(leftGeometries);

    m_right = std::make_unique<datBVHierarchy>();
    m_right->Build(rightGeometries);
}


void datBVHierarchy::_Query(std::set<datId>& ids, datBoundingBox const& box, bool strictlyInside) const {

    if (!m_box.IsValid())
        return;

    if (box.Intersects(m_box, strictlyInside)) {

        if (m_id.IsValid())
            ids.insert(m_id);

        if (nullptr != m_left)
            m_left->_Query(ids, box, strictlyInside);

        if (nullptr != m_right)
            m_right->_Query(ids, box, strictlyInside);
    }
}


std::set<datId> datBVHierarchy::Query(datBoundingBox const& box, bool strictlyInside) const {

    std::set<datId> ids;
    _Query(ids, box, strictlyInside);
    return ids;
}

