//=======================================================================================
// datToolbar.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../core/datCore.h"
#include "../tools/datToolManager.h"
#include "../tools/datPlacePolylineTool.h"
#include "../tools/datPlaceTextTool.h"
#include "../tools/datSelectTool.h"
#include "../tools/datPlaceImageTool.h"
#include "../ui/datViewManager.h"
#include "../ui/datButton.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datToolbar {

private:
    static datToolbar* s_activeToolbar; // pointer to active ViewManager or nullptr
    std::vector<datButton*> m_toolButtons;

private:
    void setToggleAllButtonsOff();

    static void onSelectPressed(datButton& button);
    static void onPlacePolylinePressed(datButton& button);
    static void onPlaceTextPressed(datButton& button);
    static void onPlaceImagePressed(datButton& button);

    static void onPlaceImageCompleted();


public:
    // Private button names so we can refer to a specific button at runtime. Not exposed to users
    static std::string NameSelectButton()           { "btn_selectTool"; }
    static std::string NamePlacePolylineButton()    { "btn_placePolylineTool"; }
    static std::string NamePlaceTextButton()        { "btn_placeTextTool"; }
    static std::string NamePlaceImageButton()       { "btn_placeImageTool"; }

public:
    datToolbar();
    ~datToolbar();
    static datToolbar& GetActiveToolbar();

    void InitToolbar(datView& mainView);
};

END_DAT_NAMESPACE
