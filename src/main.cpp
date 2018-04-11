//=======================================================================================
// main.cpp
// IFT3100-13
//=======================================================================================
#include "app/datApplication.h"

USING_DAT_NAMESPACE

int main() {

    ofSetupOpenGL(1024, 768, OF_WINDOW); // setup gl context
    ofSetWindowTitle("IFT-3100 Equipe 13");
    ofSetBackgroundColor(ofColor::midnightBlue);

    // Infinite loop!
    std::shared_ptr<datApplication> datApp(new datApplication());//
    ofRunApp(datApp);
    return 0;
}
