//=======================================================================================
// datApplication.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../core/datCore.h"
#include "../tools/datToolManager.h"
#include "../tools/datPlacePolylineTool.h"
#include "../tools/datPlaceTextTool.h"
#include "../tools/datSelectTool.h"
#include "../tools/datPlaceModelTool.h"
#include "../tools/datPlaceImageTool.h"
#include "../tools/datExportImageTool.h"
#include "../tools/datEditAttributesTool.h"
#include "../tools/datAddTextureTool.h"
#include "../ui/datViewManager.h"
#include "../ui/datButton.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datApplication : ofBaseApp {

DEFINE_T_SUPER(ofBaseApp)

private:
    std::unique_ptr<datToolManager> m_toolManager;
    std::unique_ptr<datViewManager> m_viewManager;
    std::unique_ptr<datRenderer> m_renderer;
    std::shared_ptr<datScene> m_scene;

    int m_width;
    int m_height;

protected:
    void SetupUI();

    // Make sure x and y values are inside the app window
    void ClampEvent(datMouseEvent& ev) const;
    bool SendMouseEvent(ofMouseEventArgs& ev);
    bool SendKeyEvent(ofKeyEventArgs& ev);

    virtual void dragged(ofDragInfo& ev) override;
    virtual void setup() override;
    virtual void draw() override;
    virtual void mousePressed(ofMouseEventArgs& ev) override;
    virtual void mouseReleased(ofMouseEventArgs& ev) override;
    virtual void mouseMoved(ofMouseEventArgs& ev) override;
    virtual void mouseDragged(ofMouseEventArgs & ev) override;
    virtual void keyPressed(ofKeyEventArgs& ev) override;
    virtual void windowResized(ofResizeEventArgs& resize) override;

    ofRectangle getBitmapStringBoudingBox(string text);
    ofRectangle rect;

public:
    datApplication();
    virtual ~datApplication();

    datScene& GetScene();
    datToolManager& GetToolManager();
    datViewManager& GetViewManager();
    datRenderer& GetRenderer();

    void SupplyDefaultEditTool();

    static datApplication& GetApp();
};

END_DAT_NAMESPACE
