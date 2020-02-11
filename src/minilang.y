/* The first section of a bison file contains:
 *    1. A code section for includes and other arbitrary C code. Copied to the parser verbatim
 *    2. Definition of the yylval union
 *    3. Definition of the tokens
 *    4. Precedence directives
 *    5. The start token
 *    6. Parser options
 */
%{
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

extern int yylineno;
int yylex();

// The yyerror function is called on any syntax error. When using %error-verbose, this function
// takes a single argument (a string) which contains a detailed explanation of the error.
// Otherwise it takes no arguments and it is up to the user to format the error using a minimal
// description provided in yytext.
void yyerror(const char *s) {
	fprintf(stderr, "Error: (line %d) %s\n", yylineno, s);
	exit(1);
}
%}

/* The union directive defines the yylval union used for associating (a) terminals (tokens)
 * returned by flex with additional scanning data (such as identifier/constant values); and
 * optionally (b) non-terminals (variables in productions) with AST information if any.
 */
%union {
    int intval;
    char boolval;
    float floatval;
    char *strval;
	char *identifier;
}

%token tVAR tINT tBOOL tFLOAT tSTRING
%token tEQUAL tNOTEQUAL tATMOST tATLEAST tGREATER tLESS
%token tIF tELSE tWHILE
%token tREAD tPRINT
%token <intval> tINTVAL
%token <boolval> tBOOLVAL
%token <floatval> tFLOATVAL
%token <strval> tSTRVAL
%token <identifier> tIDENTIFIER
%type <exp> exp
%type <stmt> prog decl stmts stmt body

%left tAND tOR
%left tEQUAL tNOTEQUAL tATMOST tATLEAST tGREATER tLESS
%left '+' '-'
%left '*' '/'
%left '!'

%start prog

%locations
%error-verbose

%% 
prog : prog decl { $$ = *makeStmtSequence(STMT *next, STMT *rest, int lineno); }
     | prog stmt { $$ = $2; $$->next = $1; }
     | %empty { $$ = NULL; }
; 

decl : tVAR tIDENTIFIER ':' tINT '=' exp ';' { $$ = makeStmtDeclaration($6, Type.type_int, @1.first_line); }
     | tVAR tIDENTIFIER ':' tBOOL '=' exp ';' { $$ = makeStmtDeclaration($6, Type.type_bool, @1.first_line); }
     | tVAR tIDENTIFIER ':' tFLOAT '=' exp ';' { $$ = makeStmtDeclaration($6, type_float, @1.first_line); }
     | tVAR tIDENTIFIER ':' tSTRING '=' exp ';' { $$ = makeStmtDeclaration($6, type_string, @1.first_line); }
     | tVAR tIDENTIFIER '=' exp ';' { $$ = makeStmtDeclarationInferred($4, @1.first_line); }
;

stmts : stmts stmt { $$ = $2; $$->next = $1; }
      | stmts decl { $$ = $2; $$->next = $1; }
      | %empty { $$ = NULL; }
;

stmt : tIDENTIFIER '=' exp ';' { $$ = makeStmtAssignment($1, $3, @1.first_line); }
     | tIF '(' exp ')' body { $$ = makeStmtIf($3, $5, @1.first_line); }
     | tIF '(' exp ')' body tELSE body { $$ = makeStmtIfElse($3, $5, $7, @1.first_line); }
     | tWHILE '(' exp ')' body { $$ = makeStmtWhile($3, $5, @1.first_line); }
     | tREAD '(' tIDENTIFIER ')' ';' { $$ = makeStmtRead($3, @1.first_line); }
     | tPRINT '(' exp ')' ';' { $$ = makeStmtPrint($3, @1.first_line); }
;

body : stmt { $$ = $1; }
     | '{' stmts '}' { $$ = $2; }
;

exp : tIDENTIFIER
    | tINTVAL { $$ = makeExpIntLiteral($1, @1.first_line); }
    | tBOOLVAL { $$ = makeBoolIntLiteral($1, @1.first_line); }
    | tFLOATVAL { $$ = makeExpfloatLiteral($1, @1.first_line); }
    | tSTRVAL { $$ = makeExpStringLiteral($1, @1.first_line); }
    | '-' exp { $$ = makeExpUnaryMinus($2, @1.first_line); }
    | '!' exp { $$ = makeExpNot($2, @1.first_line); }
    | exp '*' exp { $$ = makeExpMultiplication($1, $3, @1.first_line); }
    | exp '/' exp { $$ = makeExpDivision($1, $3, @1.first_line); }
    | exp '+' exp { $$ = makeExpAddition($1, $3, @1.first_line); }
    | exp '-' exp { $$ = makeExpSubtraction($1, $3, @1.first_line); }
    | exp tEQUAL exp { $$ = makeExpEqual($1, $3, @1.first_line); }
    | exp tNOTEQUAL exp { $$ = makeExpNotEqual($1, $3, @1.first_line); }
    | exp tATLEAST exp { $$ = makeExpGreaterOrEqual($1, $3, @1.first_line); }
    | exp tATMOST exp { $$ = makeExpLessOrEqual($1, $3, @1.first_line); }
    | exp tGREATER exp { $$ = makeExpGreater($1, $3, @1.first_line); }
    | exp tLESS exp { $$ = makeExpLess($1, $3, @1.first_line); }
    | exp tAND exp { $$ = makeExpAnd($1, $3, @1.first_line); }
    | exp tOR exp { $$ = makeExpOr($1, $3, @1.first_line); }
    | '(' exp ')' { $$ = $2}
;

%%
