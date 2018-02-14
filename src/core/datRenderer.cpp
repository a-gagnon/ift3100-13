//=======================================================================================
// datRenderer.cpp
// IFT3100-13
//=======================================================================================
#include "datRenderer.h"

USING_DAT_NAMESPACE

//=======================================================================================
datRenderer::Entry::Entry(std::unique_ptr<datGeometry>& geometry) :
    m_geometry(geometry.release()) {
    m_worldToGeometry.makeTranslationMatrix({ 0, 0, 0 });
}


datRenderer::Entry::~Entry() {

}


//=======================================================================================
datRenderer* datRenderer::s_activeRenderer = nullptr;

datRenderer::datRenderer() {
    assert(nullptr == s_activeRenderer);
    s_activeRenderer = this;
}


datRenderer::~datRenderer() {
    s_activeRenderer = nullptr;
}


datRenderer& datRenderer::GetRenderer() {
    assert(nullptr != s_activeRenderer);
    return *s_activeRenderer;
}


std::vector<datRenderer::Entry*> datRenderer::GetVisibleEntries() {

    std::vector<Entry*> visibleEntries;

    for (auto& entry : m_entries) {
        visibleEntries.push_back(entry.get());
    }

    return visibleEntries;
}


void datRenderer::addGeometry(std::unique_ptr<datGeometry>& geometry) {

    std::unique_ptr<Entry> entry(new Entry(geometry));
    m_entries.push_back(std::move(entry));
}


void datRenderer::render() {

    const std::vector<Entry*> visibleEntries = GetVisibleEntries();
    for (auto const& entry : visibleEntries) {

        ofPushMatrix(); // save transform to top of stack
                        //ofLoadMatrix(node->GetWorldToNodeTransform());
        entry->GetGeometry().draw();

        ofPopMatrix(); // load transform from top of stack
    }
}
