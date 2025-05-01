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
static int while_chain_executed_flag = 0;

static int mra1_if_block_skipped = 0;      
static int mra3_elseif_block_skipped = 0;   
static int mra5_else_block_skipped = 0;    
static int mra1_while_block_skipped = 0;

void updateSymbolVal(char* name, int type, TypedValue val);
TypedValue symbolVal(char* name);
void addVariable(char* name, int type);
void inputHandler(char* name, char* message); 	
void printHandler(TypedValue value); 	
int evaluateCondition(TypedValue left, int operator, TypedValue right);
int evaluateLogic(int leftCondition, int operator, int rightCondition); 
// (New)
/* Symbol table'a ekle */
Function functionTable[50];
int functionCount = 0;

void setReturnValue(TypedValue value);


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
	ParamList param_list_val;
    	ArgList arg_list_val;
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
%type <typedval> expression term
%type <boolean> condition
%type <num> if_stmt optional_elseif_list optional_else_clause
// (New types)
%type <param_list_val> param_list
%type <arg_list_val> arg_list
%type <num> func_decl func_call


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
	func_decl |
	func_call 
	//return_stmt
	;
	
// (New)
/* Fonksiyon tanımlama */
func_decl:
    DO IDENTIFIER '(' param_list ')' '{' statement_list '}' '!' 
    {
        addFunction($2, $4); // $4 param_list'i temsil eder
    }
    ;
// (New)
param_list:
    /* empty */ {
        $$.params = NULL;
        $$.paramCount = 0;
    }
    | IDENTIFIER AS type {
        $$.params = malloc(sizeof(Param));
        $$.params[0].name = strdup($1);
        $$.params[0].type = $3;
        $$.paramCount = 1;
    }
    | param_list ',' IDENTIFIER AS type {
        $$.params = realloc($1.params, ($1.paramCount + 1) * sizeof(Param));
        $$.params[$1.paramCount].name = strdup($3);
        $$.params[$1.paramCount].type = $5;
        $$.paramCount = $1.paramCount + 1;
    }
    ;

// (New)
/* Fonksiyon çağırma */


/* Fonksiyon çağırma */

    
arg_list:
    /* empty */ {
        $$.args = NULL;
        $$.argCount = 0;
    }
    | expression {
        $$.args = malloc(sizeof(TypedValue));
        $$.args[0] = $1;
        $$.argCount = 1;
    }
    | arg_list ',' expression {
        $$.args = realloc($1.args, ($1.argCount + 1) * sizeof(TypedValue));
        $$.args[$1.argCount] = $3;
        $$.argCount = $1.argCount + 1;
    }
    ;

func_call:
    IDENTIFIER '(' arg_list ')' '!' {
        callFunction($1, $3);
    }
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

type:
	TYPE_NUMBER { $$ = 1; }
	| TYPE_TEXT { $$ = 2; }
	| TYPE_LOGIC { $$ = 3; }
	;

term:
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

expression:
    term
    | expression PLUS term {
        if ($1.type == 2 && $3.type == 2) { // TEXT + TEXT
            char* newStr = malloc(strlen($1.value.text) + strlen($3.value.text) + 1);
            strcpy(newStr, $1.value.text);
            strcat(newStr, $3.value.text);
            $$.type = 2; // TEXT
            $$.value.text = newStr;
        }
        else if ($1.type == 1 && $3.type == 1) { // NUMBER + NUMBER
            $$.type = 1;
            $$.value.number = $1.value.number + $3.value.number;
        }
        else {
            ERROR("Type mismatch: Cannot add these types");
            exit(1);
        }
    }
    | expression MINUS term {
        if ($1.type != 1 || $3.type != 1) {
            ERROR("Type mismatch: Both operands must be NUMBER for subtraction");
            exit(1);
        }
        $$.type = 1; // NUMBER
        $$.value.number = $1.value.number - $3.value.number;
    }
    | expression TIMES term {
        if ($1.type != 1 || $3.type != 1) {
            ERROR("Type mismatch: Both operands must be NUMBER for multiplication");
            exit(1);
        }
        $$.type = 1; // NUMBER
        $$.value.number = $1.value.number * $3.value.number;
    }
    | expression DIVIDE term {
        if ($1.type != 1 || $3.type != 1) {
            ERROR("Type mismatch: Both operands must be NUMBER for division");
            exit(1);
        }
        if ($3.value.number == 0) {
            ERROR("Division by zero");
            exit(1);
        }
        $$.type = 1; // NUMBER
        $$.value.number = $1.value.number / $3.value.number;
    }
    ;
	
condition: expression operator expression
	{
		$$ = evaluateCondition($1, $2, $3);
	}
	| condition logic_operator condition
	{
		$$ = evaluateLogic($1, $2, $3);
	}
    | LOGIC_TRUE {$$ = 1;}  
    | LOGIC_FALSE {$$ = 0;}
	;

operator:
	SAME { $$= 1; } | DIFFERENT {$$ = 2; } | SMALLER { $$= 3; } | BIGGER {$$ = 4; } | SMALLER_EQUAL { $$= 5; } | BIGGER_EQUAL {$$ = 6; }

logic_operator:
	BOTH { $$= 1; } | EITHER {$$ = 2; }
	;

while_stmt:
    DURING '(' condition ')'
    {
        if (skip_level == 0 && $3) {  // Koşul doğruysa blok çalışır
            INFO("Loop condition true, executing once.");
        } else {
            skip_level++;  // Koşul yanlışsa blok atlanır
        }
    }
    '{' statement_list '}'
    {
        if (skip_level > 0) skip_level--;
    }
    ;

    


if_stmt:
	{
		if_chain_executed_flag = 0;
	}
	ISIT '(' condition ')'
	{
		int condition_result = $4; 
		int execute_this_block = 0;

		if (skip_level == 0 && if_chain_executed_flag == 0 && condition_result) {
			execute_this_block = 1;
			if_chain_executed_flag = 1; 
		}

		if (!execute_this_block && skip_level == 0) {
			skip_level++;
			mra1_if_block_skipped = 1; 
		} else {
			mra1_if_block_skipped = 0; 
		}
	}
	'{' statement_list '}'
	{
		if (mra1_if_block_skipped && skip_level > 0) {
			skip_level--;
		}
		mra1_if_block_skipped = 0;
	}
	optional_elseif_list
	optional_else_clause
	;

optional_elseif_list:
	/* empty */
	| optional_elseif_list MAYBE '(' condition ')'
	{
		int condition_result = $4; 
		int execute_this_block = 0; 

		if (skip_level == 0 && if_chain_executed_flag == 0 && condition_result) {
			execute_this_block = 1;
			if_chain_executed_flag = 1; 
		} 

		if (!execute_this_block && skip_level == 0) {
			skip_level++;
			mra3_elseif_block_skipped = 1;
		} else {
			mra3_elseif_block_skipped = 0; 
		}
	}
	'{' statement_list '}'
	{
		if (mra3_elseif_block_skipped && skip_level > 0) {
			skip_level--;
		}
		mra3_elseif_block_skipped = 0; 
	}
	;

optional_else_clause:
	/* empty */
	| OTHERWISE
	{
		int execute_this_block = 0;

		if (skip_level == 0 && if_chain_executed_flag == 0) {
			execute_this_block = 1;
			if_chain_executed_flag = 1; 
		} 

		if (!execute_this_block && skip_level == 0) {
			skip_level++;
			mra5_else_block_skipped = 1; 
		} else {
			mra5_else_block_skipped = 0; 
		}
	}
	'{' statement_list '}'
	{
		if (mra5_else_block_skipped && skip_level > 0) {
			skip_level--;
		}
		mra5_else_block_skipped = 0; 
	}
	;


%%

void addFunction(char* name, ParamList params) {
    if (functionCount >= 50) {
        fprintf(stderr, "Function table overflow!\n");
        exit(1);
    }
    functionTable[functionCount].name = strdup(name);
    functionTable[functionCount].params = params;
    functionCount++;
}

void callFunction(char* name, ArgList args) {
    for (int i = 0; i < functionCount; i++) {
        if (strcmp(functionTable[i].name, name) == 0) {
            // Parametre kontrolü
            if (functionTable[i].params.paramCount != args.argCount) {
                fprintf(stderr, "Parameter count mismatch for %s\n", name);
                exit(1);
            }
            // Fonksiyon gövdesini çalıştır (sonraki adım)
            printf("Calling function: %s\n", name);
            return;
        }
    }
    fprintf(stderr, "Function not found: %s\n", name);
    exit(1);
}

void addVariable(char* name, int type) {

    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            ERROR("Variable '%s' already declared.", name);
            exit(1);
        }
    }

    if (symbolCount >= SYMBOL_LIMIT) {
        ERROR("Symbol table overflow.");
        exit(1);
    }

    symbolTable[symbolCount].name = strdup(name);
    if (symbolTable[symbolCount].name == NULL) {
        ERROR("Memory allocation failed for variable '%s'.", name);
        exit(1);
    }
    symbolTable[symbolCount].type = type;
    symbolCount++;
    INFO("Declared variable: %s (type %d)", name, type);
}

TypedValue symbolVal(char* name) {
    TypedValue result;
    result.type = 0; // default olarak invalid yapalım

    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            result.type = symbolTable[i].type;

            switch (symbolTable[i].type) {
                case 1: // NUMBER
                    result.value.number = symbolTable[i].value.number;
                    break;
                case 2: // TEXT
                    result.value.text = symbolTable[i].value.text;
                    break;
                case 3: // LOGIC
                    result.value.logic = symbolTable[i].value.logic;
                    break;
                default:
                    ERROR("Unknown type for variable '%s'.", name);
                    exit(1);
            }

            return result;
        }
    }

    ERROR("Undeclared variable: '%s'", name);
    return result;
}


void updateSymbolVal(char* name, int type, TypedValue val) {
    if (name == NULL) {
        ERROR("Invalid variable name for update.");
        exit(1);
    }

    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            if (symbolTable[i].type != type) {
                ERROR("Type mismatch when assigning to '%s'.", name);
                exit(1);
            }

            switch (type) {
                case 1: // NUMBER
                    symbolTable[i].value.number = val.value.number;
                    break;
                case 2: // TEXT
                    if (symbolTable[i].value.text != NULL) {
                        free(symbolTable[i].value.text);
                    }
                    symbolTable[i].value.text = strdup(val.value.text);
                    if (symbolTable[i].value.text == NULL) {
                        ERROR("Memory allocation failed during update for '%s'.", name);
                        exit(1);
                    }
                    break;
                case 3: // LOGIC
                    symbolTable[i].value.logic = val.value.logic;
                    break;
                default:
                    ERROR("Unknown type in update for '%s'.", name);
                    exit(1);
            }
            INFO("Assigned variable: %s", name);
            return;
        }
    }

    ERROR("Undeclared variable: '%s'", name);
    exit(1);
}



void inputHandler(char* name, char* message) {
    int i;

    for (i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            break;
        }
    }

    if (i == symbolCount) {
        ERROR("Variable '%s' not found for input.", name);
        exit(1);
    }

    char buffer[256];
    printf("%.*s\n", (int)(strlen(message) - 2), message + 1); 

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        ERROR("Failed to read input for '%s'.", name);
        exit(1);
    }

    buffer[strcspn(buffer, "\n")] = 0;

    switch (symbolTable[i].type) {
        case 1: // NUMBER
        {
            double tempNumber;
            if (sscanf(buffer, "%lf", &tempNumber) == 1) {
                symbolTable[i].value.number = tempNumber;
                INFO("Input assigned to variable '%s' (NUMBER)", name);
            } else {
                ERROR("Type mismatch: Expected NUMBER for '%s'.", name);
                exit(1);
            }
            break;
        }
        case 2: // TEXT
        {
            if (buffer[0] == '"' && buffer[strlen(buffer) - 1] == '"') {
                if (symbolTable[i].value.text != NULL) {
                    free(symbolTable[i].value.text); 
                }
                symbolTable[i].value.text = strdup(buffer);
                if (symbolTable[i].value.text == NULL) {
                    ERROR("Memory allocation failed for input TEXT of '%s'.", name);
                    exit(1);
                }
                INFO("Input assigned to variable '%s' (TEXT)", name);
            } else {
                ERROR("Type mismatch: Expected quoted TEXT for '%s'.", name);
                exit(1);
            }
            break;
        }
        case 3: // LOGIC
        {
            int tempLogic;
            if (sscanf(buffer, "%d", &tempLogic) == 1 && (tempLogic == 0 || tempLogic == 1)) {
                symbolTable[i].value.logic = tempLogic;
                INFO("Input assigned to variable '%s' (LOGIC)", name);
            } else {
                ERROR("Type mismatch: Expected LOGIC (0 or 1) for '%s'.", name);
                exit(1);
            }
            break;
        }
        default:
            ERROR("Unknown type for variable '%s' during input.", name);
            exit(1);
    }
}


void printHandler(TypedValue value) {
    switch (value.type) {
        case 1: // NUMBER
            if (value.value.number == (int)value.value.number) {
                printf("%d\n", (int)value.value.number);
            } else {
                printf("%f\n", value.value.number);
            }
            break;

        case 2: // TEXT
            printf("%.*s\n", (int)(strlen(value.value.text) - 2), value.value.text + 1);
            break;

        case 3: // LOGIC
            if (value.value.logic == 1) {
                printf("RIGHT\n");
            } else {
                printf("WRONG\n");
            }
            break;

        default:
            ERROR("Unknown type for SAY statement.");
            exit(1);
    }
}


int evaluateCondition(TypedValue left, int operator, TypedValue right) {
    if (left.type != right.type) {
        ERROR("Type mismatch in condition: left.type = %d, right.type = %d", left.type, right.type);
        exit(1);
    }

    switch (left.type) {
        case 1: // NUMBER
            switch (operator) {
                case 1: return left.value.number == right.value.number;
                case 2: return left.value.number != right.value.number;
                case 3: return left.value.number < right.value.number;
                case 4: return left.value.number > right.value.number;
                case 5: return left.value.number <= right.value.number;
                case 6: return left.value.number >= right.value.number;
                default:
                    ERROR("Unknown operator '%d' in NUMBER condition.", operator);
                    exit(1);
            }

        case 2: // TEXT
            switch (operator) {
                case 1: return strcmp(left.value.text, right.value.text) == 0;
                case 2: return strcmp(left.value.text, right.value.text) != 0;
                default:
                    ERROR("Unknown operator '%d' in TEXT condition.", operator);
                    exit(1);
            }

        case 3: // LOGIC
            switch (operator) {
                case 1: return left.value.logic == right.value.logic;
                case 2: return left.value.logic != right.value.logic;
                default:
                    ERROR("Unknown operator '%d' in LOGIC condition.", operator);
                    exit(1);
            }

        default:
            ERROR("Unknown type '%d' in condition.", left.type);
            exit(1);
    }
}

int evaluateLogic(int leftCondition, int operator, int rightCondition) {
    switch (operator) {
        case 1: // BOTH 
            return leftCondition && rightCondition;
        case 2: // EITHER
            return leftCondition || rightCondition;
        default:
            ERROR("Unknown logic operator '%d'.", operator);
            exit(1);
    }
}


void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s); //Burayı silebiliriz , snytax error alınırsa zaten log dosyasında gösteriliyor.
}

int main() {
    logFile = fopen("program_log.txt" , "w");

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
