#ifndef CUSTOM_STRUCTS_H
#define CUSTOM_STRUCTS_H

// Type definitions for values and variables
typedef struct {
    int type;        // 1: NUMBER, 2: TEXT, 3: LOGIC
    union {
        double number;
        char* text;
        int logic;
    } value;
} TypedValue;

typedef struct {
    char* name;
    int type;        // 1 for NUMBER, 2 for TEXT, 3 for LOGIC
    union {
        double number;
        char* text;
        int logic;
    } value;
} Variable;

// yeni
typedef struct {
    char* name;
    int type;
} Param;

typedef struct {
    Param* params;
    int paramCount;
} ParamList;

typedef struct {
    TypedValue* args;
    int argCount;
} ArgList;

typedef struct {
    char* name;
    ParamList params;
    // Diğer fonksiyon özellikleri...
} Function;

extern Function functionTable[50];
extern int functionCount;

void addFunction(char* name, ParamList params);
void callFunction(char* name, ArgList args);

#endif // CUSTOM_STRUCTS_H
