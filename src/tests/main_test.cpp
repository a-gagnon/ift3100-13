//=======================================================================================
// tests/main_test.cpp
// IFT3100-13
//=======================================================================================
#include "gtest/gtest.h"

//---------------------------------------------------------------------------------------
// @method
//---------------------------------------------------------------------------------------
int main(int argc, char** argv)
    {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    std::getchar();
    return 0;
    }