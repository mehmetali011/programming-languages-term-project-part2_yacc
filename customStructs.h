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
    int type;        // 1 for NUMBER , 2 for TEXT , 3 for LOGIC
    union {
        double number;
        char* text;
        int logic;
    } value;
} Variable;

typedef struct {
    char* name;
    char** paramNames;
    int paramCount;
    struct stmt_node* body; 
} Function;

struct stmt_node; // forward declaration

struct param_list_node {
    char** names;
    int count;
};

struct expr_list_node {
    TypedValue* args;
    int count;
};

extern Function functionTable[50];
extern int functionCount;


//Other structs can be added here

#endif // CUSTOM_STRUCTS_H
