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
#include "symbol.h"

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
%type <exp> decl exp
%type <stmt> prog stmts stmt body

%left tAND tOR
%left tEQUAL tNOTEQUAL tATMOST tATLEAST tGREATER tLESS
%left '+' '-'
%left '*' '/'
%left '!'

%start prog

%locations
%error-verbose

%% 
prog : prog decl
     | prog stmt
     | %empty
; 

decl : tVAR tIDENTIFIER ':' tINT '=' exp ';' { $$ = makeStmtAssignment($6, Type.type_int, @1.first_line); }
     | tVAR tIDENTIFIER ':' tBOOL '=' exp ';' { $$ = makeStmtAssignment($6, Type.type_bool, @1.first_line); }
     | tVAR tIDENTIFIER ':' tFLOAT '=' exp ';' { $$ = makeStmtAssignment($6, type_float, @1.first_line); }
     | tVAR tIDENTIFIER ':' tSTRING '=' exp ';' { $$ = makeStmtAssignment($6, type_string, @1.first_line); }
     | tVAR tIDENTIFIER '=' exp ';' { $$ = makeStmtAssignmentInferred($6, @1.first_line); }
;

stmts : stmts stmt
      | stmts decl
      | %empty
;

stmt : tIDENTIFIER '=' exp ';'
     | tIF '(' exp ')' body
     | tIF '(' exp ')' body tELSE body
     | tWHILE '(' exp ')' body
     | tREAD '(' tIDENTIFIER ')' ';'
     | tPRINT '(' exp ')' ';'
;

body : stmt
     | decl
     | '{' stmts '}'
;

exp : tIDENTIFIER
    | tINTVAL { $$ = makeExpIntLiteral($1, @1.first_line); }
    | tBOOLVAL
    | tFLOATVAL
    | tSTRVAL
    | '-' exp
    | '!' exp
    | exp '*' exp
    | exp '/' exp
    | exp '+' exp
    | exp '-' exp
    | exp tEQUAL exp
    | exp tNOTEQUAL exp
    | exp tATLEAST exp
    | exp tATMOST exp
    | exp tGREATER exp
    | exp tLESS exp
    | exp tAND exp
    | exp tOR exp
    | '(' exp ')' { }
;

%%
