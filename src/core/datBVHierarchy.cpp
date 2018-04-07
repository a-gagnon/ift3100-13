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

void datBVHierarchy::Build(std::vector<datElement const*> elements) {

    Clear();

    if (elements.empty())
        return;

    for (auto const& element : elements) {
        m_box.Extend(element->CalculateBoundingBox());
    }


    if (1 == elements.size()) {
        m_id = elements.front()->GetId();
        return;
    }
    
    // More than 1 entry to place. Find longest axis and sort
    const float xLength = m_box.GetXLength();
    const float yLength = m_box.GetYLength();
    const float zLength = m_box.GetZLength();

    if (xLength > yLength && xLength > zLength) {
        std::sort(elements.begin(), elements.end(), [](datElement const* lhs, datElement const* rhs)
        { return lhs->CalculateBoundingBox().GetCenter().x < rhs->CalculateBoundingBox().GetCenter().x; });
    }
    else if (yLength > xLength && yLength > zLength) {
        std::sort(elements.begin(), elements.end(), [](datElement const* lhs, datElement const* rhs)
        { return lhs->CalculateBoundingBox().GetCenter().y < rhs->CalculateBoundingBox().GetCenter().y; });
    }
    else { // zLength
        std::sort(elements.begin(), elements.end(), [](datElement const* lhs, datElement const* rhs)
        { return lhs->CalculateBoundingBox().GetCenter().z < rhs->CalculateBoundingBox().GetCenter().z; });
    }

    
    size_t halfSize = elements.size() / 2;
    std::vector<datElement const*> leftElements;
    std::vector<datElement const*> rightElements;
    leftElements.insert(leftElements.end(), elements.begin(), elements.begin() + halfSize);
    rightElements.insert(rightElements.end(), elements.begin() + halfSize, elements.end());

    m_left = std::make_unique<datBVHierarchy>();
    m_left->Build(leftElements);

    m_right = std::make_unique<datBVHierarchy>();
    m_right->Build(rightElements);
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

