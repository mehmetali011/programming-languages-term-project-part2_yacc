%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customStructs.h" 


//Variable array size:100 can be extended in future.
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


int in_try_block = 0;
int exception_thrown = 0;
int catch_block_skipped = 0;
char* exception_message = NULL;


static int if_chain_executed_flag = 0; 


static int mra1_if_block_skipped = 0;      
static int mra3_elseif_block_skipped = 0;   
static int mra5_else_block_skipped = 0;    



void updateSymbolVal(char* name, int type, TypedValue val);
TypedValue symbolVal(char* name);
TypedValue callFunction(char* name, TypedValue* args, int argCount);
void addVariable(char* name, int type);
void inputHandler(char* name, char* message); 	
void printHandler(TypedValue value); 	
int evaluateCondition(TypedValue left, int operator, TypedValue right);
int evaluateLogic(int leftCondition, int operator, int rightCondition); 

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
    struct param_list_node* paramList;
    struct expr_list_node* exprList;
}


%start program


%token DO
%token DECLARE AS SET ASK RETURN THROW TRY CATCH FINALLY ISIT MAYBE OTHERWISE DURING COUNT FROM TO SAY
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
%type <boolean> condition // condition evaluates to a boolean (int 0 or 1)
%type <num> if_stmt optional_elseif_list optional_else_clause
%type <paramList> param_list
%type <exprList> arg_list

%%

program:
	statement_list
	;

statement_list:
	/* empty */
	| statement statement_list
	;

statement:
	assignment
    | var_decl
    | input_stmt
    | print_stmt
    | if_stmt
    | func_decl
    | func_call
    | try_stmt
    | throw_stmt
    ;

assignment:
	IDENTIFIER SET expression '!'
	{
		if(skip_level == 0) {
			updateSymbolVal($1, $3.type, $3);
		}
	}
	;

func_decl:
    DO IDENTIFIER '(' param_list ')' '{' statement_list '}'
    {
        if (functionCount >= 50) {
            ERROR("Function limit reached.");
            exit(1);
        }

        functionTable[functionCount].name = strdup($2);
        functionTable[functionCount].paramCount = $4->count;
        functionTable[functionCount].paramNames = $4->names;
        INFO("Function defined: %s", $2);
        functionCount++;
    }
    ;
    
param_list:
    IDENTIFIER AS type
    {
        $$ = malloc(sizeof(struct param_list_node));
        $$->count = 1;
        $$->names = malloc(sizeof(char*));
        $$->names[0] = $1;
    }
    | IDENTIFIER AS type ',' param_list
    {
        $$ = malloc(sizeof(struct param_list_node));
        $$->count = $5->count + 1;
        $$->names = malloc(sizeof(char*) * $$->count);
        $$->names[0] = $1;
        for (int i = 0; i < $5->count; i++) {
            $$->names[i + 1] = $5->names[i];
        }
        free($5);
    }
    ;
    
func_call:
    IDENTIFIER '(' arg_list ')' '!'
    {
        TypedValue result = callFunction($1, $3->args, $3->count);
        // sonucu SAY ile yazdırmak istersen printHandler(result);
    }
    ;

arg_list:
    expression
    {
        $$ = malloc(sizeof(struct expr_list_node));
        $$->count = 1;
        $$->args = malloc(sizeof(TypedValue));
        $$->args[0] = $1;
    }
    | expression ',' arg_list
    {
        $$ = malloc(sizeof(struct expr_list_node));
        $$->count = $3->count + 1;
        $$->args = malloc(sizeof(TypedValue) * $$->count);
        $$->args[0] = $1;
        for (int i = 0; i < $3->count; i++) {
            $$->args[i + 1] = $3->args[i];
        }
        free($3);
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
    | expression PLUS expression {
    if ($1.type == 1 && $3.type == 1) {
        // NUMBER + NUMBER
        $$ = (TypedValue){ .type = 1 };
        $$.value.number = $1.value.number + $3.value.number;
    } else if ($1.type == 2 && $3.type == 2) {
        const char* s1 = $1.value.text;
        const char* s2 = $3.value.text;

        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);

        const char* core1 = s1;
        size_t core1_len = len1;
        if (s1[0] == '"' && s1[len1 - 1] == '"') {
            core1 = s1 + 1;
            core1_len = len1 - 2;
        }

        const char* core2 = s2;
        size_t core2_len = len2;
        if (s2[0] == '"' && s2[len2 - 1] == '"') {
            core2 = s2 + 1;
            core2_len = len2 - 2;
        }

        char* result = malloc(core1_len + core2_len + 3); // quotes + null terminator
        if (!result) {
            ERROR("Memory allocation failed in string concatenation.");
            exit(1);
        }

        sprintf(result, "\"%.*s%.*s\"", (int)core1_len, core1, (int)core2_len, core2);

        $$ = (TypedValue){ .type = 2 };
        $$.value.text = result;
    } else {
        ERROR("Type mismatch in PLUS operation: left type %d, right type %d.", $1.type, $3.type);
        exit(1);
    }
}
    | expression MINUS expression {
        if ($1.type == 1 && $3.type == 1) {
            $$ = (TypedValue){ .type = 1 };
            $$.value.number = $1.value.number - $3.value.number;
        } else {
            ERROR("MINUS operation only supported for NUMBER type.");
            exit(1);
        }
    }
    | expression TIMES expression {
        if ($1.type == 1 && $3.type == 1) {
            $$ = (TypedValue){ .type = 1 };
            $$.value.number = $1.value.number * $3.value.number;
        } else {
            ERROR("TIMES operation only supported for NUMBER type.");
            exit(1);
        }
    }
    | expression DIVIDE expression {
        if ($1.type == 1 && $3.type == 1) {
            if ($3.value.number == 0) {
                ERROR("Division by zero.");
                $$ = (TypedValue){ .type = 1, .value.number = 0 };
            } else {
                $$ = (TypedValue){ .type = 1 };
                $$.value.number = $1.value.number / $3.value.number;
            }
        } else {
            ERROR("DIVIDE operation only supported for NUMBER type.");
            exit(1);
        }
    }
    | '(' expression ')' {
        $$ = $2;
    }
    | IDENTIFIER {
        $$ = symbolVal($1);
    }
    | IDENTIFIER '(' arg_list ')' {
        $$ = callFunction($1, $3->args, $3->count);
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
    | IDENTIFIER {
    TypedValue temp = symbolVal($1);
    if (temp.type != 3) {
        ERROR("Non-LOGIC variable used in condition: %s", $1);
        exit(1);
    }
    $$ = temp.value.logic == 1 ? 1 : 0;
    }
	;

operator:
	SAME { $$= 1; } | DIFFERENT {$$ = 2; } | SMALLER { $$= 3; } | BIGGER {$$ = 4; } | SMALLER_EQUAL { $$= 5; } | BIGGER_EQUAL {$$ = 6; }

logic_operator:
	BOTH { $$= 1; } | EITHER {$$ = 2; }
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
	
throw_stmt:
	THROW '(' expression ')' '!'
	{
		if(skip_level == 0) {
			if(in_try_block) {
				exception_thrown = 1;
				
				if($3.type == 2) { // TEXT
					if(exception_message != NULL) {
						free(exception_message);
					}
					exception_message = strdup($3.value.text);
					if(exception_message == NULL) {
						ERROR("Memory allocation failed for exception message");
						exit(1);
					}
				} else {
					ERROR("Exception message must be of TEXT type");
					exit(1);
				}
				
				skip_level++;
			} else {
				ERROR("THROW statement outside of TRY block");
				exit(1);
			}
		}
	}
	;

try_stmt:
	TRY 
	{
		if(skip_level == 0) {
			in_try_block = 1;
			exception_thrown = 0;
		}
	}
	'{' statement_list '}'
	{
		if(skip_level == 0) {
			in_try_block = 0;
		}
		else if(exception_thrown && skip_level == 1) {
			skip_level--;
		}
	}
	optional_catch_clause
	optional_finally_clause
	;

optional_catch_clause:
	/* empty */
	| CATCH '(' IDENTIFIER ')'
	{
		if(skip_level == 0) {
			if(exception_thrown) {
				int found = 0;
				for(int i = 0; i < symbolCount; i++) {
					if(strcmp(symbolTable[i].name, $3) == 0) {
						found = 1;
						if(symbolTable[i].type == 2) { // TEXT
							if(symbolTable[i].value.text != NULL) {
								free(symbolTable[i].value.text);
							}
							symbolTable[i].value.text = strdup(exception_message);
							if(symbolTable[i].value.text == NULL) {
								ERROR("Memory allocation failed for exception variable");
								exit(1);
							}
						} else {
							ERROR("Exception variable must be of TEXT type");
							exit(1);
						}
						break;
					}
				}
				if(!found) {
					addVariable($3, 2); // TEXT type
					TypedValue tv;
					tv.type = 2;
					tv.value.text = strdup(exception_message);
					updateSymbolVal($3, 2, tv);
				}
				
				exception_thrown = 0;
				catch_block_skipped = 0;
			} else {
				skip_level++;
				catch_block_skipped = 1;
			}
		}
	}
	'{' statement_list '}'
	{
		if(catch_block_skipped && skip_level > 0) {
			skip_level--;
			catch_block_skipped = 0;
		}
	}
	;

optional_finally_clause:
	/* empty */
	| FINALLY
	{
		if(skip_level > 0 && !in_try_block) {
			skip_level = 0;
		}
	}
	'{' statement_list '}'
	;




%%

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
    fprintf(stderr, "Parser error: %s\n", s);
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
