﻿#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>
#include <dbghelp.h>
#include <thread>
#include <fstream>

extern "C" void enterFunction(void* returnAddress);
extern "C" void exitFunction();
void getFunctionNameFromAddress(void* address);

typedef void(__stdcall* HelloFunc)();
typedef void(__stdcall* ByeFunc)();
HelloFunc hello;
ByeFunc bye;


// スレッドローカル変数で再帰防止フラグを管理
thread_local bool isInPenter = false;
thread_local bool isInPexit = false;
thread_local int indent = 0;
struct CallNode {
    std::string functionName;
    CallNode* parent;
    std::vector<CallNode*> children;
};

//std::stack<CallNode*> callStack;
//CallNode* root = nullptr;

//std::ofstream debugLog("debug_log.txt", std::ios::out);

extern "C" void __declspec(naked) _penter() {
    __asm {
        push eax
        mov eax, [esp + 4] // リターンアドレスを取得
        push eax
    }

    if (!isInPenter && hello != nullptr) {
        isInPenter = true;
        __asm {
            call hello
            call enterFunction
        }
        isInPenter = false;
    }

    __asm {
        pop eax
        pop eax
        ret
    }
}

extern "C" void __declspec(naked) _pexit() {

    if (bye != nullptr) {
        __asm {
            call bye
            ret
        }
    }
    else {
        __asm {
            ret
        }
    }
    //if (!isInPexit) {
    //    isInPexit = true;
    //    __asm {
    //        //call exitFunction
    //        ret
    //    }
    //    isInPexit = false;
    //}
    //else {
    //    __asm {
    //        ret
    //    }
    //}
}

void enterFunction(void* returnAddress) {
    //debugLog << "enterFunction called with address: " << returnAddress << std::endl;
    //std::string functionName = getFunctionNameFromAddress(returnAddress);

    getFunctionNameFromAddress(returnAddress);

    //CallNode* node = new CallNode{functionName, nullptr, {}};
    //if (!callStack.empty()) {
    //    node->parent = callStack.top();
    //    callStack.top()->children.push_back(node);
    //} else {
    //    root = node;
    //}
    //callStack.push(node);
    //printf("hello %x\n", returnAddress);
}

void exitFunction() {
    if (!isInPexit && bye != nullptr) {
        isInPexit = true;
        indent--;
        isInPexit = false;
    }
    //indent--;
    //if (!callStack.empty()) {
    //    callStack.pop();
    //}
}

void getFunctionNameFromAddress(void* address) {
    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = MAX_SYM_NAME;

    HANDLE process = GetCurrentProcess();
    //SymInitialize(process, NULL, TRUE);

    if (SymFromAddr(process, (DWORD64)address, 0, symbol)) {
        for (int i = 0; i < indent; i++)
            printf("  ");
        printf("get %s\n", symbol->Name);
        //return symbol->Name;
    }
    return;
}

//void printCallTree(CallNode* node, int depth = 0) {
//    if (!node) return;
//    for (int i = 0; i < depth; ++i) std::cout << "  ";
//    std::cout << node->functionName << std::endl;
//    for (auto child : node->children) {
//        printCallTree(child, depth + 1);
//    }
//}

void testFunctionA() {
    //std::cout << "Inside testFunctionA" << std::endl;
    printf("Inside testFunctionA\n");
}

void testFunctionB() {
    //std::cout << "Inside testFunctionB" << std::endl;
    printf("Inside testFunctionB\n");
    testFunctionA();
}

//int main() {
//    HANDLE process = GetCurrentProcess();
//    SymInitialize(process, NULL, TRUE);
//
//    testFunctionB();
//    //printCallTree(root);
//    return 0;
//}


int main() {
    HMODULE dll = LoadLibraryA("PenterPexit.dll");
    //HMODULE dll = GetModuleHandle(TEXT("PenterPexit.dll"));
    if (!dll) {
        std::cerr << "DLL 読み込み失敗" << std::endl;
        return 1;
    }

    hello = (HelloFunc)GetProcAddress(dll, "helloFromDll");
    if (!hello) {
        std::cerr << "hello関数取得失敗" << std::endl;
        return 1;
    }

    bye = (HelloFunc)GetProcAddress(dll, "byeFromDll");
    if (!hello) {
        std::cerr << "bye関数取得失敗" << std::endl;
        return 1;
    }

    testFunctionB();
    
    //__asm {
    //    call hello
    //}

    return 0;
}