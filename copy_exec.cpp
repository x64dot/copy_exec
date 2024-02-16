#include <iostream>
#include <windows.h>
#include <shlobj_core.h>
#include <shlwapi.h>

#pragma warning(disable : 4996)

using namespace std;

void hide_console();
int make_dup();

int main() {
    hide_console();

    int result = make_dup();

    if (result != 0) {
        MessageBoxW(NULL, L"Something went wrong!", NULL, MB_OK);

        return -1;
    }
    
    MessageBoxW(NULL, L"Check your documents folder :)", L"Successful", MB_OK);

    return 0;
}


void hide_console() {
    HWND hWnd = GetConsoleWindow();

    ShowWindow(hWnd, SW_HIDE);
}

int make_dup() {
    wchar_t buffer1[250];
    PWSTR buffer2 = NULL;
    

    DWORD result1 = GetModuleFileNameW(NULL, buffer1, 250);

    
    if (result1 == 0) {
        return 1;
    }

    PathStripPathW(buffer1);


    HRESULT result2 = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &buffer2);

    if (result2 != S_OK) {
        return 1;
    }
    wcscat(buffer2, L"\\");
    wcscat(buffer2, buffer1);


    BOOL result3 = CopyFileW(buffer1, buffer2, 0);

    if (result3 == 0) {
        return 1;
    }

    return 0;
}
