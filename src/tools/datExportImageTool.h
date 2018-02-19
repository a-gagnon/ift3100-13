//=======================================================================================
// datExportImageTool.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datTool.h"

BEGIN_DAT_NAMESPACE

// Define pointer-to-function. Called when the tool has no more images to place
typedef void(*datExportImageDoneCallback)(void);

//=======================================================================================
struct datExportImageTool : datEditTool {

private:
    datExportImageDoneCallback m_pCallbackFunction;

protected:
    virtual void onStartTool() override;

public:
    datExportImageTool(datExportImageDoneCallback callback);
    virtual ~datExportImageTool();
};

END_DAT_NAMESPACE
