#include <iostream>
#include <Windows.h>

int main()
{   
    //Window name
    LPCWSTR windowName = L"Half-Life";

    //Get window handle
    HWND hwnd = FindWindow(NULL, windowName);

    if (!hwnd) {
        std::cerr << "Window not found! " << std::fflush;
        return -1;
    }else {
        std::cout << "Success! Window Found! " << std::fflush;
    }

    DWORD procID;
    //Get the process ID
    GetWindowThreadProcessId(hwnd, &procID);

    //Get object handle
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, procID);
    if (!handle) {
        std::cerr << "Failed to grab handle! " << std::fflush;
        return -1;
    }else {
        std::cout << "Success! Handle found" << std::fflush;
    }


    return 0;

}

