//=======================================================================================
// datNonCopyableClass.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDefinitions.h"

BEGIN_DAT_NAMESPACE

//=======================================================================================
struct datNonCopyableClass {

private:
    datNonCopyableClass(datNonCopyableClass const&) = delete;
    datNonCopyableClass& operator= (datNonCopyableClass const&) = delete;
protected:
    datNonCopyableClass() {}
    ~datNonCopyableClass() {}
};

END_DAT_NAMESPACE
