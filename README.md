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
