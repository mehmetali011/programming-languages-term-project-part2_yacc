%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customStructs.h" // Assuming this contains the Variable and TypedValue definitions


//Variable array size:100 can be extended in future.
Variable symbolTable[100];
int symbolCount = 0;


//Global skip level for nested blocks/statements
int skip_level = 0; 

//Flag to track if any branch (ISIT, MAYBE, OTHERWISE) in the CURRENT chain has executed.
static int if_chain_executed_flag = 0; //If 1, then a branch in the chain has executed.

// Flags to track if skip_level was incremented specifically by the MRA for block skipping
static int mra1_if_block_skipped = 0;        // if_stmt MRA before '{'
static int mra3_elseif_block_skipped = 0;    // optional_elseif_list MRA before '{'
static int mra5_else_block_skipped = 0;      // optional_else_clause MRA before '{'


// Methods for variable related operations
void updateSymbolVal(char* name, int type, TypedValue val);
TypedValue symbolVal(char* name);
void addVariable(char* name, int type);
void inputHandler(char* name, char* message); 	
void printHandler(TypedValue value); 	
int evaluateCondition(TypedValue left, int operator, TypedValue right);
int evaluateLogic(int leftCondition, int operator, int rightCondition); 

void yyerror(const char *s);
int yylex(void);
%}


//Custom structs header file inclusion
%code requires {
	#include "customStructs.h"
}

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

%type <num> type operator logic_operator
%type <typedval> expression
%type <boolean> condition // condition evaluates to a boolean (int 0 or 1)
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
	input_stmt|
	print_stmt |
	if_stmt
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
condition: expression operator expression
	{
		$$ = evaluateCondition($1, $2, $3);
	}
	| condition logic_operator condition
	{
		$$ = evaluateLogic($1, $2, $3);
	}
	;

operator:
	SAME { $$= 1; } | DIFFERENT {$$ = 2; } | SMALLER { $$= 3; } | BIGGER {$$ = 4; } | SMALLER_EQUAL { $$= 5; } | BIGGER_EQUAL {$$ = 6; }

logic_operator:
	BOTH { $$= 1; } | EITHER {$$ = 2; }
	;



if_stmt:

	{
		if_chain_executed_flag = 0; //Reset the flag for this chain. Every new chain (if_stmt) should have this flag reset.
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
    printf("Declared variable: %s as type %d\n", name, type);
}

int symbolType(char* name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return symbolTable[i].type;
        }
    }
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

void updateSymbolVal(char* name, int type, TypedValue val) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            if (symbolTable[i].type != type) {
                printf("Type mismatch when assigning to %s\n", name);
                return;
            }

            switch (type) {
                case 1: // NUMBER
                    symbolTable[i].value.number = val.value.number;
                    break;
                case 2: // TEXT
                    symbolTable[i].value.text = strdup(val.value.text);
                    break;
                case 3: // LOGIC
                    symbolTable[i].value.logic = val.value.logic;
                    break;
            }
            printf("Assigned variable: %s\n", name);
            return;
        }
    }
    printf("Undeclared variable: %s\n", name);
}

void inputHandler(char* name, char* message) {
    int i;

    // Find the variable index
    for (i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            break;
        }
    }

    if (i == symbolCount) {
        printf("Variable %s not found\n", name);
        return;
    }

    char buffer[256];
    printf("%.*s\n", (int)(strlen(message) - 2), message + 1);

    switch (symbolTable[i].type) {
        case 1: // NUMBER
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                double tempNumber;
                if (sscanf(buffer, "%lf", &tempNumber) == 1) {
                    symbolTable[i].value.number = tempNumber;
                    printf("Input received for variable: %s\n", name);
                } else {
                    printf("Type mismatch when assigning to %s\n", name);
                }
            }
            break;

        case 2: // TEXT
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                // Remove newline character
                buffer[strcspn(buffer, "\n")] = 0;
                if (buffer[0] == 34 && buffer[strlen(buffer) - 1] == 34) {
                    if (symbolTable[i].value.text != NULL) {
                        free(symbolTable[i].value.text);
                    }
                    symbolTable[i].value.text = strdup(buffer);
                    printf("Input received for variable: %s\n", name);
                } else {
                    printf("Type mismatch when assigning to %s\n", name);
                }
            }
            break;

        case 3: // LOGIC
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                int tempLogic;
                if (sscanf(buffer, "%d", &tempLogic) == 1 && (tempLogic == 0 || tempLogic == 1)) {
                    symbolTable[i].value.logic = tempLogic;
                    printf("Input received for variable: %s\n", name);
                } else {
                    printf("Type mismatch when assigning to %s\n", name);
                }
            }
            break;

        default:
            printf("Unknown type for variable %s\n", name);
    }
}

void printHandler(TypedValue value) {
    switch (value.type) {
        case 1:
            if (value.value.number == (int)value.value.number) {
                printf("%d\n", (int)value.value.number);
            } else {
                printf("%f\n", value.value.number);
            }
            break;
        case 2:
            printf("%.*s\n", (int)(strlen(value.value.text) - 2), value.value.text + 1);
            break;
        case 3:
            if (value.value.logic == 1) {
                printf("true\n");
            } else {
                printf("false\n");
            }
            break;
        default:
            printf("Unkown type for SAY statement");
    }
}

int evaluateCondition(TypedValue left, int operator, TypedValue right) {
    if (left.type != right.type) {
        printf("Type mismatch in condition\n");
        return 0;
    }

    switch (left.type) {
        case 1:
            switch (operator) {
                case 1:
                    return left.value.number == right.value.number;
                case 2:
                    return left.value.number != right.value.number;
                case 3:
                    return left.value.number < right.value.number;
                case 4:
                    return left.value.number > right.value.number;
                case 5:
                    return left.value.number <= right.value.number;
                case 6:
                    return left.value.number >= right.value.number;
                default:
                    printf("Unknown operator in condition\n");
                    return 0;
            }
        case 2:
            switch (operator) {
                case 1:
                    return strcmp(left.value.text, right.value.text) == 0;
                case 2:
                    return strcmp(left.value.text, right.value.text) != 0;
                default:
                    printf("Unknown operator in condition\n");
                    return 0;
            }
        case 3:
            switch (operator) {
                case 1:
                    return left.value.logic == right.value.logic;
                case 2:
                    return left.value.logic != right.value.logic;
                default:
                    printf("Unknown operator in condition\n");
                    return 0;  
            }
        default:
            printf("Unknown type in condition\n");
            return 0;
    }
}

int evaluateLogic(int leftCondition, int operator, int rightCondition) {
    switch (operator) {
        case 1:
            return leftCondition && rightCondition;
        case 2:
            return leftCondition || rightCondition;
        default:
            printf("Unknown operator in logic\n");
            return 0;     
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}

int main() {
    return yyparse();
}
