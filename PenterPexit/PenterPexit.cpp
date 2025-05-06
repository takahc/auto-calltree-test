#include "PenterPexit.h"

extern "C" __declspec(dllexport) void helloFromDll() {
    MessageBoxA(NULL, "Hello from DLL!", "DLL", MB_OK);
}



extern "C" __declspec(dllexport) void byeFromDll() {
    MessageBoxA(NULL, "Bye from DLL.", "DLL", MB_OK);
}