%{
#include "parser.tab.h" // Token definitions from the parser
#include <string.h>
#include <stdlib.h>
#include "modes.h"

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

%}

DIGIT [0-9]

%option yylineno
%option noinput
%option nounput

%%
#[^\n]*\n
[ \t\r\n]+

"+"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("+\n"); return '+'; }
"-"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("-\n"); return '-'; }
"*"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("*\n"); return '*'; }
"!"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("!\n"); return '!'; }
"="     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("=\n"); return '='; }
":"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf(":\n"); return ':'; }
";"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf(";\n"); return ';'; }
"/"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("/\n"); return '/'; }
"("     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("(\n"); return '('; }
")"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf(")\n"); return ')'; }
"{"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("{\n"); return '{'; }
"}"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("}\n"); return '}'; }
"&&"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("&&\n"); return tAND; }
"||"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("||\n"); return tOR; }
"=="     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("==\n"); return tEQUAL; }
"!="     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("!=\n"); return tNOTEQUAL; }
"<="     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("<=\n"); return tATMOST; }
">="     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf(">=\n"); return tATLEAST; }
">"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf(">\n"); return tGREATER; }
"<"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("<\n"); return tLESS; }

var     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("var\n"); return tVAR; }
int     { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("int\n"); return tINT; }
bool    { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("bool\n"); return tBOOL; }
float   { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("float\n"); return tFLOAT; }
string  { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("string\n"); return tSTRING; }
if      { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("if\n"); return tIF; }
else    { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("else\n"); return tELSE; }
while   { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("while\n"); return tWHILE; }
read    { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("read\n"); return tREAD; }
print   { if (mode == SCAN) printf("OK\n"); if (mode == TOKENS) printf("print\n"); return tPRINT; }

(0|([1-9]{DIGIT}*))\.{DIGIT}+ {
    if (mode == SCAN)
        printf("OK\n");
    if (mode == TOKENS)
        printf("Float value: %s\n", yytext);
	yylval.floatval = atof(yytext);
	return tFLOATVAL;
}
0|([1-9]{DIGIT}*) {
    if (mode == SCAN)
        printf("OK\n");
    if (mode == TOKENS)
        printf("Interger value: %s\n", yytext);
	yylval.intval = atoi(yytext);
	return tINTVAL;
}
(True)|(False) {
    if (mode == SCAN)
        printf("OK\n");
    if (mode == TOKENS)
        printf("Boolean value: %s\n", yytext);
	yylval.boolval = strcmp(yytext, "True") == 0;
	return tBOOLVAL;
}
\"[^\"]*\" {
    if (mode == SCAN)
        printf("OK\n");
    if (mode == TOKENS)
        printf("String value: %s\n", yytext);
	yylval.strval = strdup(yytext);
	return tSTRVAL;
}
[a-zA-Z_][a-zA-Z0-9_]* {
    if (mode == SCAN)
        printf("OK\n");
    if (mode == TOKENS)
        printf("identifier: %s\n", yytext);
	yylval.identifier = strdup(yytext);
	return tIDENTIFIER;
}



. 	{ fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%
