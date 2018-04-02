//=======================================================================================
// datMenu.cpp
// IFT3100-13
//=======================================================================================
#include "datMenu.h"

USING_DAT_NAMESPACE

datMenu::datMenu(float x, float y, Layout layout) :
    T_Super(x, y, 1, 1),
    m_layout(layout) {
}


void datMenu::layout() {

    setWidth(1);
    setHeight(1);

    float posX = x;
    float posY = y;

    for (size_t i = 0; i < m_views.size(); ++i) {

        auto& view = m_views[i];
        float width = view->getWidth();
        float height = view->getHeight();

        view->x = posX;
        view->y = posY;
        growToInclude(*view);

        if (Layout::Horizontal == m_layout)
            posX += (width + Padding);
        else if (Layout::Vertical == m_layout)
            posY += (height + Padding);
    }
}


void datMenu::onViewAdded() {
    layout();
}


void datMenu::onViewRemoved() {
    layout();
}


datButton* datMenu::AddToolButton(std::string const& name, std::string const& tooltip, std::string const& iconName) {

    datButton* pButton = new datButton(0, 0, IconWidth, IconHeight);
    pButton->SetName(name);
    pButton->SetTooltip(tooltip);
    pButton->SetImage(datUtilities::LoadImageFromAssetsFolder(iconName));
    AddView(pButton);
    return pButton;

}

