#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customStructs.h"

Function functionTable[50];
int functionCount = 0;
extern int skip_level;  // skip_level değişkenini extern olarak tanımlıyoruz

// While döngüsü için gerekli değişkenler
int while_condition = 0;
int while_body_executed = 0;
int while_loop_count = 0;

void executeWhileLoop(int condition) {
    printf("DEBUG: executeWhileLoop called with condition: %d\n", condition);
    while_condition = condition;
    if (condition) {
        skip_level = 0;
        while_body_executed = 1;
        while_loop_count++;
        printf("DEBUG: Setting skip_level to 0 and while_body_executed to 1 (loop count: %d)\n", while_loop_count);
    } else {
        skip_level++;
        while_body_executed = 0;
        printf("DEBUG: Incrementing skip_level and setting while_body_executed to 0\n");
    }
}

void checkWhileCondition() {
    printf("DEBUG: checkWhileCondition called (loop count: %d)\n", while_loop_count);
    printf("DEBUG: Current while_condition: %d\n", while_condition);
    
    if (while_body_executed) {
        if (!while_condition) {
            skip_level++;
            printf("DEBUG: Condition is false, incrementing skip_level\n");
        } else {
            skip_level = 0;
            printf("DEBUG: Condition is still true, resetting skip_level\n");
        }
        while_body_executed = 0;
    }
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
