#pragma once

#include <stdio.h>
#include <windows.h>
#include <dbghelp.h>


#ifdef PENTERPEXITX64_EXPORTS
#define PENTERPEXITX64_API __declspec(dllexport)
#else
#define PENTERPEXITX64_API __declspec(dllimport)
#endif

extern "C" PENTERPEXITX64_API void enterFunction(void* return_address, void* rbp, void* rsp);
extern "C" PENTERPEXITX64_API void exitFunction(void* rbp, void* return_address);
extern "C" PENTERPEXITX64_API void indentPrint(const char* s);
