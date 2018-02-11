//=======================================================================================
// datApplication.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "../datDefinitions.h"
#include "../tools/datToolManager.h"
#include "../tools/datPlacePolylineTool.h"
#include "../tools/datPlaceTextTool.h"
#include "../ui/datInputManager.h"
#include "../ui/datButton.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datApplication : ofBaseApp {

DEFINE_T_SUPER(ofBaseApp)

private:
    std::unique_ptr<datToolManager> m_toolManager;
    std::unique_ptr<datInputManager> m_inputManager;

protected:

    void CreateToolbar();
	void dragged(ofDragInfo& info);


	bool SendMouseEvent(ofMouseEventArgs& ev);
    bool SendKeyEvent(ofKeyEventArgs& ev);

    virtual void setup() override;
    virtual void draw() override;
    virtual void mousePressed(ofMouseEventArgs& ev) override;
    virtual void mouseReleased(ofMouseEventArgs& ev) override;
    virtual void mouseMoved(ofMouseEventArgs& ev) override;
    virtual void keyPressed(ofKeyEventArgs& ev) override;
	virtual void exit();

public:
	vector <ofImage> draggedImages;
	ofPoint dragPt;
	ofImage img;
    datApplication();
    virtual ~datApplication();

    datToolManager& GetToolManager();
    datInputManager& GetInputManager();

    static datApplication& GetApp();
};

END_DAT_NAMESPACE
