//=======================================================================================
// datApplication.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../core/datDefinitions.h"
#include "../tools/datToolManager.h"
#include "../tools/datPlacePolylineTool.h"
#include "../tools/datPlaceTextTool.h"
#include "../tools/datSelectTool.h"
#include "../ui/datViewManager.h"
#include "../ui/datButton.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datApplication : ofBaseApp {

DEFINE_T_SUPER(ofBaseApp)

private:
    std::unique_ptr<datToolManager> m_toolManager;
    std::unique_ptr<datViewManager> m_viewManager;
    int m_width;
    int m_height;

protected:

 test
    void CreateToolbar();
	void dragged(ofDragInfo& info);


	bool SendMouseEvent(ofMouseEventArgs& ev);

    void SetupUI();

    // Make sure x and y values are inside the app window
    void ClampEvent(datMouseEvent& ev) const;
    bool SendMouseEvent(ofMouseEventArgs& ev);
 master
    bool SendKeyEvent(ofKeyEventArgs& ev);

    virtual void setup() override;
    virtual void draw() override;
    virtual void mousePressed(ofMouseEventArgs& ev) override;
    virtual void mouseReleased(ofMouseEventArgs& ev) override;
    virtual void mouseMoved(ofMouseEventArgs& ev) override;
    virtual void mouseDragged(ofMouseEventArgs & ev) override;
    virtual void keyPressed(ofKeyEventArgs& ev) override;
test
	virtual void exit();

    virtual void windowResized(ofResizeEventArgs& resize) override;
 master

public:
	vector <ofImage> draggedImages;
	ofPoint dragPt;
	ofImage img;
    datApplication();
    virtual ~datApplication();

    datToolManager& GetToolManager();
    datViewManager& GetViewManager();

    static datApplication& GetApp();
};

END_DAT_NAMESPACE
