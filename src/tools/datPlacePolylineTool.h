//=======================================================================================
// datPlacePolylineTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datPlacePolylineTool : datTool {

private:
    ofPolyline m_polyline;

protected:
    void saveShape(ofPolyline const& polyline);

    virtual void onLeftMouseButtonDown(ofVec2f const& point) override;
    virtual void onRightMouseButtonDown(ofVec2f const& point) override;
    virtual void onMouseMotion(ofVec2f const& point) override;
    virtual void onDraw() override;

public:
    datPlacePolylineTool();
    virtual ~datPlacePolylineTool();
};

END_DAT_NAMESPACE
