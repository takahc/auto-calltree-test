#include "PenterPexitx64.h"

int indent = 0;


extern "C" PENTERPEXITX64_API void enterFunction(void* rbp, void* return_address) {
    indent++;
    for(int i = 0; i < indent; i++) {
		printf("  ");
	}
    printf("[ENTER] RBP=%p, Return=%p\n", rbp, return_address);
}



extern "C" PENTERPEXITX64_API void exitFunction(void* rbp, void* return_address) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
    printf("[EXIT]  RBP=%p, Return=%p\n", rbp, return_address);
    indent--;
}
