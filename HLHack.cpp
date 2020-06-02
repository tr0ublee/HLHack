#include <iostream>
#include <Windows.h>


#define ADDED_AMMO_AMOUNT 10

typedef enum retrieve_type {
    SHOTGUN_AMMO_ADDR,
}RetrieveType;


int const_table(RetrieveType query) {

    switch (query) {
        case SHOTGUN_AMMO_ADDR:
            return 0X004235A04;
        default:
            return 0;

    }

}

int main()
{   
    //Window name
    LPCWSTR windowName = L"Half-Life";
    
    //Get window handle
    HWND hwnd = FindWindow(NULL, windowName);

    if (!hwnd) {
        std::cerr << "Window not found! " << std::endl;
        return -1;
    }else {
        std::cout << "Success! Window Found! " << std::endl;
    }

    DWORD procID;
    //Get the process ID
    GetWindowThreadProcessId(hwnd, &procID);

    //Get object handle
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, procID);
    if (!handle) {
        std::cerr << "Failed to grab handle! " << std::endl;
        return -1;
    }else {
        std::cout << "Success! Handle found" << std::endl;
    }

    while (true) {

        // Check if K is pressed
        if (GetKeyState('K') & 0x8000){
            uint64_t ammo;
            int address = const_table(SHOTGUN_AMMO_ADDR);
            ReadProcessMemory(handle, (void*)address, &ammo, sizeof(uint64_t), 0);
            std::cout << "Old ammo amount is " << ammo << std::endl;
            ammo += ADDED_AMMO_AMOUNT;
            
            if (WriteProcessMemory(handle, (void*)address, &ammo, sizeof(int), 0)) {
                
                std::cout << "Success! New ammo amount is " << ammo << std::endl;
            }else {
                std::cerr << "Fail! Probably bad address" << std::endl;
            }

            //Sleep for 0.1s
            Sleep(100);
        }
        else {
            //Sleep for 0.1s
            Sleep(100);
        }

    }

    return 0;

}

