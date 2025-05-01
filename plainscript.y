%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customStructs.h" 

#define SYMBOL_LIMIT 100
Variable symbolTable[SYMBOL_LIMIT];
int symbolCount = 0;

FILE* logFile = NULL;
extern int currentLine;

#define ERROR(fmt, ...) do { \
    if (logFile) fprintf(logFile, "[Error] Line %d: " fmt "\n", currentLine, ##__VA_ARGS__); \
} while(0)

#define INFO(fmt, ...) do { \
    if (logFile) fprintf(logFile, "[Info] Line %d: " fmt "\n", currentLine, ##__VA_ARGS__); \
} while(0)

int skip_level = 0; 
static int if_chain_executed_flag = 0;
static int mra1_if_block_skipped = 0;      
static int mra3_elseif_block_skipped = 0;   
static int mra5_else_block_skipped = 0;    

// Function declarations
void updateSymbolVal(char* name, int type, TypedValue val);
TypedValue symbolVal(char* name);
void addVariable(char* name, int type);
void inputHandler(char* name, char* message); 	
void printHandler(TypedValue value); 	
int evaluateCondition(TypedValue left, int operator, TypedValue right);
int evaluateLogic(int leftCondition, int operator, int rightCondition); 
void executeWhileLoop(int condition);
void executeForLoop(char* var, double start, double end);
void defineFunction(char* name, char** params, int paramCount);
TypedValue callFunction(char* name, TypedValue* args, int argCount);
void throwException(TypedValue value);
void handleTryCatch();

void yyerror(const char *s);
int yylex(void);
%}

%code requires {
    #include "customStructs.h"
}

%union {
    int boolean;
    double number;
    char* string;
    char* identifier;
    int num;
    TypedValue typedval;
}

%start program

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

%type <num> type operator logic_operator
%type <typedval> expression term func_call
%type <boolean> condition
%type <num> if_stmt optional_elseif_list optional_else_clause

%%

program:
    statement_list
    ;

statement_list:
    /* empty */
    | statement statement_list
    ;

statement:
    assignment |
    var_decl |
    input_stmt |
    print_stmt |
    if_stmt |
    while_stmt |
    for_stmt |
    func_decl |
    func_call |
    return_stmt |
    throw_stmt |
    try_catch_stmt
    ;

assignment:
    IDENTIFIER SET expression '!'
    {
        if(skip_level == 0) {
            updateSymbolVal($1, $3.type, $3);
        }
    }
    ;

var_decl:
    DECLARE IDENTIFIER AS type '!'
    {
        if(skip_level == 0) {
            addVariable($2, $4);
        }
    }
    ;

input_stmt:
    ASK '(' IDENTIFIER ')' '!'
    {
        if(skip_level == 0) {
            inputHandler($3, " \" Enter a value: \" "); 
        }
    }
    | ASK '(' IDENTIFIER ',' STRING ')' '!'
    {
        if(skip_level == 0) {
            inputHandler($3, $5);
        }
    }
    ;

print_stmt:
    SAY '(' expression ')' '!'
    {
        if(skip_level == 0) {
            printHandler($3);
        }
    }
    ;

while_stmt:
    DURING '(' condition ')' '{' statement_list '}'
    {
        if(skip_level == 0) {
            while($3) {
                executeWhileLoop($3);
            }
        }
    }
    ;

for_stmt:
    COUNT IDENTIFIER FROM expression TO expression '{' statement_list '}'
    {
        if(skip_level == 0) {
            executeForLoop($2, $4.value.number, $6.value.number);
        }
    }
    ;

func_decl:
    DO IDENTIFIER '(' param_list ')' '{' statement_list '}'
    {
        if(skip_level == 0) {
            defineFunction($2, $4.names, $4.count);
        }
    }
    ;

param_list:
    /* empty */ { $$.names = NULL; $$.count = 0; }
    | IDENTIFIER AS type { 
        $$.names = malloc(sizeof(char*)); 
        $$.names[0] = strdup($1);
        $$.count = 1;
      }
    | IDENTIFIER AS type ',' param_list {
        $$.names = realloc($5.names, ($5.count + 1) * sizeof(char*));
        $$.names[$5.count] = strdup($1);
        $$.count = $5.count + 1;
      }
    ;

func_call:
    IDENTIFIER '(' arg_list ')' '!'
    {
        if(skip_level == 0) {
            TypedValue result = callFunction($1, $3.args, $3.count);
            // Handle return value if needed
        }
    }
    ;

arg_list:
    /* empty */ { $$.args = NULL; $$.count = 0; }
    | expression { 
        $$.args = malloc(sizeof(TypedValue)); 
        $$.args[0] = $1;
        $$.count = 1;
      }
    | expression ',' arg_list {
        $$.args = realloc($3.args, ($3.count + 1) * sizeof(TypedValue));
        $$.args[$3.count] = $1;
        $$.count = $3.count + 1;
      }
    ;

return_stmt:
    RETURN expression '!'
    {
        if(skip_level == 0) {
            // Handle return value
        }
    }
    ;

throw_stmt:
    THROW expression '!'
    {
        if(skip_level == 0) {
            throwException($2);
        }
    }
    ;

try_catch_stmt:
    TRY '{' statement_list '}' CATCH '{' statement_list '}'
    {
        if(skip_level == 0) {
            handleTryCatch();
        }
    }
    | TRY '{' statement_list '}' CATCH '{' statement_list '}' FINALLY '{' statement_list '}'
    {
        if(skip_level == 0) {
            handleTryCatch();
            // Execute finally block
        }
    }
    ;

[Previous type, term, condition rules remain the same...]

%%

[Previous function implementations remain the same...]

// New function implementations
void executeWhileLoop(int condition) {
    // Implementation for while loop execution
}

void executeForLoop(char* var, double start, double end) {
    // Implementation for for loop execution
}

void defineFunction(char* name, char** params, int paramCount) {
    // Implementation for function definition
}

TypedValue callFunction(char* name, TypedValue* args, int argCount) {
    // Implementation for function call
    TypedValue result;
    return result;
}

void throwException(TypedValue value) {
    // Implementation for exception throwing
}

void handleTryCatch() {
    // Implementation for try-catch handling
}

int main() {
    logFile = fopen("program_log.txt", "w");

    if (logFile == NULL) {
        printf("Failed to open log file.\n");
        return 1;
    }

    int result = yyparse();
    if(result == 1){
        fprintf(logFile, "\nSyntax Error at line %d.",currentLine);
    }
    fclose(logFile);

    return result;
}