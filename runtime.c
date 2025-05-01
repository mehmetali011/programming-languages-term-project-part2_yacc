#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customStructs.h"

Function functions[50];
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
    
    functions[functionCount].name = strdup(name);
    functions[functionCount].params.names = params;
    functions[functionCount].params.count = paramCount;
    functionCount++;
}

TypedValue callFunction(char* name, TypedValue* args, int argCount) {
    for (int i = 0; i < functionCount; i++) {
        if (strcmp(functions[i].name, name) == 0) {
            if (functions[i].params.count != argCount) {
                fprintf(stderr, "Argument count mismatch for function %s\n", name);
                exit(1);
            }
            
            TypedValue result;
            return result;
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