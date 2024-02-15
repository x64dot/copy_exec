#include <iostream>
#include <windows.h>
#include <shlobj_core.h>
#include <shlwapi.h>

#pragma warning(disable : 4996)

using namespace std;

int make_dup();

int main() {

    int result = make_dup();

    if (result != 0) {
        cout << "Something went wrong!\n";
    }

    cin.get();


    return 0;
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