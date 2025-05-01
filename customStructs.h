#ifndef CUSTOM_STRUCTS_H
#define CUSTOM_STRUCTS_H

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

typedef struct {
    char** names;
    int count;
} ParamList;

typedef struct {
    TypedValue* args;
    int count;
} ArgList;

typedef struct {
    char* name;
    ParamList params;
    TypedValue* body;
} Function;

#endif // CUSTOM_STRUCTS_H