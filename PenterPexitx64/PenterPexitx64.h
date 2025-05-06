#pragma once

#include <stdio.h>

#ifdef PENTERPEXITX64_EXPORTS
#define PENTERPEXITX64_API __declspec(dllexport)
#else
#define PENTERPEXITX64_API __declspec(dllimport)
#endif

extern "C" PENTERPEXITX64_API void enterFunction(void* rbp, void* return_address);
extern "C" PENTERPEXITX64_API void exitFunction(void* rbp, void* return_address);