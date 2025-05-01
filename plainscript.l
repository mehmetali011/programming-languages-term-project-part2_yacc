%{
#include "y.tab.h"
#include <string.h>
#include <stdlib.h>
#include "customStructs.h"

int currentLine = 1;
int yylex();
void yyerror(char *s);
%}

%%

"DECLARE"           { return DECLARE; }
"AS"                { return AS; }
"SET"               { return SET; }
"ASK"               { return ASK; }
"RETURN"            { return RETURN; }
"THROW"             { return THROW; }
"TRY"               { return TRY; }
"CATCH"             { return CATCH; }
"FINALLY"           { return FINALLY; }
"ISIT"              { return ISIT; }
"MAYBE"             { return MAYBE; }
"OTHERWISE"         { return OTHERWISE; }
"DURING"            { return DURING; }
"COUNT"             { return COUNT; }
"FROM"              { return FROM; }
"TO"                { return TO; }
"SAY"               { return SAY; }
"DO"                { return DO; }


"NUMBER"            { return TYPE_NUMBER; }
"TEXT"              { return TYPE_TEXT; }
"LOGIC"             { return TYPE_LOGIC; }

"RIGHT"             { yylval.boolean = 1; return LOGIC_TRUE; }
"WRONG"             { yylval.boolean = 0; return LOGIC_FALSE; }

"PLUS"              { return PLUS; }
"MINUS"             { return MINUS; }
"TIMES"             { return TIMES; }
"DIVIDE"            { return DIVIDE; }

"SAME"              { return SAME; }
"DIFFERENT"         { return DIFFERENT; }
"SMALLER"           { return SMALLER; }
"BIGGER"            { return BIGGER; }
"SMALLER_EQUAL"     { return SMALLER_EQUAL; }
"BIGGER_EQUAL"      { return BIGGER_EQUAL; }

"BOTH"              { return BOTH; }
"EITHER"            { return EITHER; }

\"[^\"]*\"          { yylval.string = strdup(yytext); return STRING; }

[0-9]+\.[0-9]+      { yylval.number = atof(yytext); return NUMBER; }
[0-9]+              { yylval.number = atoi(yytext); return NUMBER; }

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.identifier = strdup(yytext); return IDENTIFIER; }

"//".*              { /* comment, ignore */ }
\n                  { currentLine++;}
[ \t\r]+            { /* whitespace, ignore */ }

"("                 { return '('; }
")"                 { return ')'; }
"{"                 { return '{'; }
"}"                 { return '}'; }
","                 { return ','; }
"!"                 { return '!'; }


.                   { yyerror("unexpected character"); }

%%

int yywrap(void) { return 1; }

