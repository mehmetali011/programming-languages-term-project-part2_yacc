#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customStructs.h"

Function functionTable[50];
int functionCount = 0;

void executeWhileLoop(int condition) {
}

void executeForLoop(char* var, double start, double end) {
}

void defineFunction(char* name, char** params, int paramCount) {
    if (functionCount >= 50) {
        fprintf(stderr, "Function limit reached\n");
        exit(1);
    }
    
    functionTable[functionCount].name = strdup(name);
    functionTable[functionCount].paramNames = params;
    functionTable[functionCount].paramCount = paramCount;
    functionCount++;
}


TypedValue callFunction(char* name, TypedValue* args, int argCount) {
    for (int i = 0; i < functionCount; i++) {
      if (strcmp(functionTable[i].name, name) == 0) {
      if (functionTable[i].paramCount != argCount) {
                fprintf(stderr, "Argument count mismatch for function %s\n", name);
                exit(1);
            }

            printf("Function '%s' called with %d args:\n", name, argCount);
            for (int j = 0; j < argCount; j++) {
                if (args[j].type == 1) {
                    printf("  Arg %d: %f\n", j+1, args[j].value.number);
                } else if (args[j].type == 2) {
                    printf("  Arg %d: %s\n", j+1, args[j].value.text);
                } else if (args[j].type == 3) {
                    printf("  Arg %d: %s\n", j+1, args[j].value.logic ? "RIGHT" : "WRONG");
                }
            }

            TypedValue dummyResult;
            dummyResult.type = 1;
            dummyResult.value.number = 42; // örnek çıktı
            return dummyResult;
        }
    }

    fprintf(stderr, "Function %s not found\n", name);
    exit(1);
}


void throwException(TypedValue value) {
    fprintf(stderr, "Exception thrown: ");
    if (value.type == 1) {
        fprintf(stderr, "%f\n", value.value.number);
    } else if (value.type == 2) {
        fprintf(stderr, "%s\n", value.value.text);
    } else {
        fprintf(stderr, "%s\n", value.value.logic ? "RIGHT" : "WRONG");
    }
    exit(1);
}

void handleTryCatch() {
}
