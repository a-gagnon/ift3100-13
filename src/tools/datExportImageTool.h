//=======================================================================================
// datExportImageTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datExportImageTool : datEditTool {

protected:
    virtual void onStartTool() override;
    virtual void onDraw() override;

public:
    datExportImageTool();
    virtual ~datExportImageTool();
};

END_DAT_NAMESPACE
