This project includes CSE 434 Programming Languages lesson's term project.

Group Members:
-İsmail Babacan  -Umut Altun -Muharrem Kocabıyık -Mehmet Ali Keskin


--------------------------------------------------------------------------------
Programming Language Name is PlainScript
--------------------------------------------------------------------------------


Intoduction to PlainScript


PlainScript is a programming language that is easy to read and write and is aimed at being very simple to use, even for users with no experience in coding. The language focuses on clarity and natural syntax, making it easy for novices to learn while still allowing for fundamental programming concepts like variables, conditionals, loops, functions, and input/output.

One of the basic design choices in PlainScript is the use of English-like keywords that are extremely close to natural language, such as:

DECLARE for variable declaration
SET for assignment
ISIT for conditionals
DURING and COUNT for loops
SAY for output
ASK for input
DO for function declarations


--------------------------------------------------------------------------------
Design Decisions for our programming language:
--------------------------------------------------------------------------------
1- Statement Termination with ! Instead of ;
    +To differentiate from traditional languages and improve readability, statements end with ! instead of ;

2- Text-based Syntax for better readability
    +Instead of using symbols like ==, !=, <, >, we use natural words:
        SAME (for ==)
        DIFFERENT (for !=)
        SMALLER, BIGGER, SMALLER_EQUAL, BIGGER_EQUAL (for comparisons)


--------------------------------------------------------------------------------
PlainScript's BNF
--------------------------------------------------------------------------------

	<program> ::= <statement_list>

	<statement_list> ::= <statement> | <statement> <statement_list>

	<statement> ::= <assignment> 
             	| <if_stmt> 
             	| <while_stmt> 
             	| <for_stmt> 
             	| <print_stmt> 
              	| <func_decl> 
              	| <func_call> 
              	| <var_decl> 
              	| <input_stmt> 
              	| <return_stmt> 
              	| <throw_stmt> 
              	| <try_catch_stmt> 
              	| <comment>

	<var_decl> ::= "DECLARE" <identifier> "AS" <type> "!"

	<type> ::= "NUMBER" | "TEXT" | "LOGIC"

	<assignment> ::= <identifier> "SET" <expression> "!"

	<input_stmt> ::= "ASK" "(" <identifier> ")!"

	<return_stmt> ::= "RETURN" <expression> "!"
	<throw_stmt> ::= "THROW" <expression> "!"

	<try_catch_stmt> ::= "TRY" "{" <statement_list> "}" 
                   	"CATCH" "(" <identifier> ")" "{" <statement_list> "}" 
                   	| "TRY" "{" <statement_list> "}" 
                     	"CATCH" "(" <identifier> ")" "{" <statement_list> "}" 
                     	"FINALLY" "{" <statement_list> "}"

	<if_stmt> ::= "ISIT" "(" <condition> ")" "{" <statement_list> "}"
             	| "ISIT" "(" <condition> ")" "{" <statement_list> "}" <elseif_list> "OTHERWISE" "{" <statement_list> "}"
             	| "ISIT" "(" <condition> ")" "{" <statement_list> "}" <elseif_list>

	<elseif_list > ::= "MAYBE" "(" <condition> ")" "{" <statement_list> "}" 
                	| "MAYBE" "(" <condition> ")" "{" <statement_list> "}" <elseif_list>

	<while_stmt> ::= "DURING" "(" <condition> ")" "{" <statement_list> "}"

	<for_stmt> ::= "COUNT" <identifier> "FROM" <expression> "TO" <expression> "{" <statement_list> "}"

	<print_stmt> ::= "SAY" "(" <expression> ")!"

	<func_decl> ::= "DO" <identifier> "(" <param_list> ")" "{" <statement_list> "}"
	<param_list> ::= <identifier> "AS" <type> | <identifier> "AS" <type> "," <param_list>

	<func_call> ::= <identifier> "(" <arg_list> ")!"

	<arg_list> ::= <expression> | <expression> "," <arg_list>

	<expression> ::= <term> | <expression> ("PLUS" | "MINUS" | "TIMES" | "DIVIDE") <term>

	<term> ::= <identifier> | <number> | <logic> | <string>

	<condition> ::= <expression> ("SAME" | "DIFFERENT" | "SMALLER" | "BIGGER" | "SMALLER_EQUAL" | "BIGGER_EQUAL") <expression>
             | <condition> ("BOTH" | "EITHER") <condition>

	<identifier> ::= [a-zA-Z_][a-zA-Z0-9_]*

	<number> ::= [0-9]+ | [0-9]+"."[0-9]+

	<logic> ::= "RIGHT" | "WRONG"

	<string> ::= "\"" .* "\""

	<comment> ::= "//" .*

--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
PlainScript Syntax
--------------------------------------------------------------------------------


Variable Declaration and Assignment
DECLARE: Used to declare a variable.

	DECLARE x AS NUMBER!
	DECLARE name AS TEXT!

SET: Used to assign a value to a variable.

	x SET 10!
	name SET "John"!

--------------------------------------------------------------------------------
Conditional Statements
--------------------------------------------------------------------------------

ISIT: Represents an if statement.
MAYBE: Represents an else if statement.
OTHERWISE: Represents an else statement.
	
	ISIT (x SAME 10) {
	    SAY("X is 10")!
	} MAYBE (x SMALLER 5) {
	    SAY("X is less than 5")!
	} OTHERWISE {
	    SAY("X is something else")!
	}

--------------------------------------------------------------------------------
Loops
--------------------------------------------------------------------------------

DURING: Represents a while loop.

	DURING (x SMALLER 10) {
	    SAY(x)!
	    x SET x PLUS 1!
	}

COUNT: Represents a for loop.

	COUNT i FROM 1 TO 5 {
	    SAY(i)!
	}


--------------------------------------------------------------------------------
Input and Output
--------------------------------------------------------------------------------

ASK: Used to take user input.

 	ASK(name)!

SAY: Used to print output.

	SAY("Hello, " PLUS name)!

--------------------------------------------------------------------------------
Functions
--------------------------------------------------------------------------------

DO: Used to define a function.

	DO greet(name AS TEXT) {
	    SAY("Hello, " PLUS name)!
	}

Function Call:

	greet("John")!

--------------------------------------------------------------------------------
Operators
--------------------------------------------------------------------------------

Arithmetic Operators:

	PLUS → +
	
	MINUS → -
	
	TIMES → *
	
	DIVIDE → /

Logical Operators:

	BOTH → AND
	
	EITHER → OR
	
	Comparison Operators:
	
	SAME → ==
	
	DIFFERENT → !=
	
	SMALLER → <
	
	BIGGER → >
	
	SMALLER_EQUAL → <=

	BIGGER_EQUAL → >=

	//: Used to add comments 


# pl-yacc-starter-kit

This is a logic language which allows only conjunction and printing the result.

\<program\> : \<stmts\>

\<stmts\> : \<stmt\>
	| \<stmt\> ; \<stmts\>

\<stmt\> : print \<expr\>;
	| \<assign\>;

\<assign\> : \<lhs\> = \<rhs\>;

\<lhs\> : \<var\>

\<rhs\> : \<var\>
	| \<expr\>

\<var\> : [a-zA-Z][a-zA-Z0-9_]*

\<expr\> : \<expr\> 
	| \<expr\> and \<expr\>
	| ( \<expr\> and \<expr\> )


## Running instructions:

> make

> ./calc < example.ext

...(some output)...

> make clean
