//=======================================================================================
// datUtilities.cpp
// IFT3100-13
//=======================================================================================
#include "datUtilities.h"

USING_DAT_NAMESPACE

std::string datUtilities::GetAssetsFolder() {

    std::string exeDir = ofFilePath::getCurrentExeDir();
    exeDir.append("../../assets/");
    return ofFilePath::getAbsolutePath(exeDir);
}


ofImage* datUtilities::LoadImageFromAssetsFolder(std::string const& fileName) {

    std::string filePath = GetAssetsFolder();
    filePath.append(fileName);

    ofImage* pImage = new ofImage();
    if (pImage->load(filePath))
        return pImage;

    assert(false); // We should never fail to load an image
    delete pImage;
    return nullptr;
}


bool datUtilities::OpenFileDialog(std::string& filePath, bool fileMustExist) {

    WCHAR wideChars[260];

    // Open windows file browser to populate images to place
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = wideChars;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(wideChars);
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST;
    
    if (fileMustExist)
        ofn.Flags |= OFN_FILEMUSTEXIST;

    if (!GetOpenFileName(&ofn)) {
        // Dialog closed without picking any file
        return false;
    }

    char defaultChar = ' ';
    char chars[260];
    WideCharToMultiByte(CP_ACP, 0, wideChars, -1, chars, 260, &defaultChar, false);

    filePath = std::string(chars);
    return true;
}


bool datUtilities::ExecuteProgram(std::string const& pathToExe, bool isRelative) {

    std::string absPath;

    if (isRelative) {
        std::string relPath = ofFilePath::getCurrentExeDir() + pathToExe;
        absPath = ofFilePath::getAbsolutePath(relPath);
    }
    else
        absPath = pathToExe;


    // additional information
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // start the program up
    if (!CreateProcessA(absPath.c_str(), nullptr, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        return false;

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return true;
}


bool datUtilities::ExecuteRayTracer() {
    std::string relPath = ofFilePath::getCurrentExeDir() + "/raytracer/RayTracer.exe";
    std::string absPath = ofFilePath::getAbsolutePath(relPath);
    return ExecuteProgram(absPath, false/*isRelative*/);
}


bool datUtilities::OpenWithDefaultProgram(std::string const& relativePathToFile) {

    std::string relPath = ofFilePath::getCurrentExeDir() + relativePathToFile;
    std::string absPath = ofFilePath::getAbsolutePath(relPath);

    std::wstring wstr = std::wstring(absPath.begin(), absPath.end());
    return ShellExecute(0, 0, wstr.c_str(), 0, 0, SW_SHOW);
}
