%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int type; // 1: NUMBER, 2: TEXT, 3: LOGIC
    union {
        double number;
        char* text;
        int logic;
    } value;
} TypedValue;

//Variable structure
typedef struct {
    char* name;
    int type;        // 1 for NUMBER , 2 for TEXT , 3 for LOGIC
    union {
        int number;
        char* text;
        int logic;
    } value;
} Variable;

//Variable array size:100 can be extended in future.
Variable symbolTable[100];
int symbolCount = 0;

//Methods for variable related operations
void updateSymbolVal(char* name, int type, void* val);
TypedValue symbolVal(char* name);
void addVariable(char* name, int type);

void yyerror(const char *s);
int yylex(void);
%}

//Type definition
%union {
    int boolean;
    double number;
    char* string;
    char* identifier;
    int num;
    TypedValue typedval;
}

%start program

//Token definition
%token DECLARE AS SET ASK RETURN THROW TRY CATCH FINALLY ISIT MAYBE OTHERWISE DURING COUNT FROM TO SAY DO
%token TYPE_NUMBER TYPE_TEXT TYPE_LOGIC
%token <boolean> LOGIC_TRUE LOGIC_FALSE 
%token <number> NUMBER 
%token <string> STRING 
%token <identifier> IDENTIFIER

%token PLUS MINUS TIMES DIVIDE
%token SAME DIFFERENT SMALLER BIGGER SMALLER_EQUAL BIGGER_EQUAL
%token BOTH EITHER

%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc '!'

%token '(' ')' '{' '}' ','

%type <num> type
%type <num> logic
%type <string> string
%type <number> number
%type <identifier> identifier
%type <num> boolean
%type <typedval> expression

%%

program:
    line
    | line program
    ;

line:
    DECLARE IDENTIFIER AS type '!' 
    {
    addVariable($2, $4);
        printf("Declared variable: %s as type %d\n", $2, $4);
    } 
    | IDENTIFIER SET expression '!'
    {
        updateSymbolVal($1, $3.type, &$3.value);
        printf("Assigned variable: %s\n", $1);
    }
    ;

type:
    TYPE_NUMBER { $$ = 1; }
    | TYPE_TEXT { $$ = 2; }
    | TYPE_LOGIC { $$ = 3; }
    ;

expression:
      NUMBER {
          $$ = (TypedValue){ .type = 1 };
          $$.value.number = $1;
      }
    | STRING {
          $$ = (TypedValue){ .type = 2 };
          $$.value.text = $1;
      }
    | LOGIC_TRUE {
          $$ = (TypedValue){ .type = 3 };
          $$.value.logic = 1;
      }
    | LOGIC_FALSE {
          $$ = (TypedValue){ .type = 3 };
          $$.value.logic = 0;
      }
    | IDENTIFIER {
          $$ = symbolVal($1);
      }
    ;

%%

void addVariable(char* name, int type) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            printf("Variable %s already declared.\n", name);
            return;
        }
    }
    symbolTable[symbolCount].name = strdup(name);
    symbolTable[symbolCount].type = type;
    symbolCount++;
}

TypedValue symbolVal(char* name) {
    TypedValue result;
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            result.type = symbolTable[i].type;

            switch (symbolTable[i].type) {
                case 1: 
                    result.value.number = symbolTable[i].value.number;
                    break;
                case 2:
                    result.value.text = symbolTable[i].value.text;
                    break;
                case 3:
                    result.value.logic = symbolTable[i].value.logic;
                    break;
                default:
                    printf("Unknown type for variable '%s'.\n", name);
            }

            return result;
        }
    }

    printf("Undeclared variable: %s\n", name);
    return result;
}


void updateSymbolVal(char* name, int type, void* val) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            if (symbolTable[i].type != type) {
                printf("Type mismatch when assigning to %s\n", name);
                return;
            }

            switch (type) {
                case 1: // NUMBER
                    symbolTable[i].value.number = *((double*)val);
                    break;
                case 2: // TEXT
                    symbolTable[i].value.text = strdup((char*)val);
                    break;
                case 3: // LOGIC
                    symbolTable[i].value.logic = *((int*)val);
                    break;
            }
            return;
        }
    }
    printf("Undeclared variable: %s\n", name);
}


void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}

int main() {
    return yyparse();
}
