#include "PenterPexitx64.h"

int indent = 0;
char functionName[1024];


void getFunctionNameFromAddress(void* address) {
    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = MAX_SYM_NAME;

    HANDLE process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);

    if (SymFromAddr(process, (DWORD64)address, 0, symbol)) {
        //for (int i = 0; i < indent; i++)
        //    printf("  ");
        //printf("get %s\n", symbol->Name);
        strcpy_s(functionName, 1024, symbol->Name);
        //return symbol->Name;
    }
    return;
}


extern "C" PENTERPEXITX64_API void enterFunction(void* return_address, void* rbp, void* rsp) {
    getFunctionNameFromAddress(return_address);


    for(int i = 0; i < indent; i++) {
		printf("\t");
	}
    printf("[CALL]%s (Return=%p, RBP=%p, RSP=%p) \n", functionName, return_address, rbp, rsp);
    for (int i = 0; i < indent; i++) {
        printf("\t");
    }
    printf("{\n");
    indent++;
}



extern "C" PENTERPEXITX64_API void exitFunction(void* rbp, void* return_address) {
    indent--;
    for (int i = 0; i < indent; i++) {
        printf("\t");
    }
    printf("}\n");
}


extern "C" PENTERPEXITX64_API void indentPrint(const char* s) {
    for (int i = 0; i < indent; i++) {
		printf("\t");
	}
	printf("%s", s);
}
