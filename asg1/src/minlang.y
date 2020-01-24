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
    byte boolval;
    float floatval;
    char *strval;
	char *identifier;
}

/* Token directives define the token types to be returned by the scanner (excluding character
 * tokens). Each token definition takes [optionally, a reference to the associated field in the
 * yylval union] and an identifier. Multiple tokens can eb defined per directive by using a list
 * of identifiers separated by spaces.
 */
%token tVAR tINT tBOOL tFLOAT tSTRING
%token tEQUAL tNOTEQUAL tATMOST tATLEAST tGREATER tLESS
%token tIF tELSE tWHILE
%token tREAD tPRINT
%token <intval> tINTVAL
%token <boolval> tBOOLVAL
%token <floatval> tFLOATVAL
%token <strval> tSTRVAL
%token <identifier> tIDENTIFIER 

/* Precedence directives resolve grammar ambiguities by breaking ties between shift/reduce
 * operations. Tokens are grouped into precendence levels, with lower precedence coming first
 * and then higher precedence in later directives. Tokens specified in the same directive have
 * the same precedence. Ties at the same level are broken using either %left or %right, which
 * denote left-associative and right-associative respectively.
 */
%left tAND tOR
%left tEQUAL tNOTEQUAL tATMOST tATLEAST tGREATER tLESS
%left '+' '-'
%left '*' '/'
%left '!'

/* Start token (by default if this is missing it takes the first production */
%start prog

/* Generate the yylloc structure used for storing line numbers with tokens */
%locations
/* Generate detailed error messages */
%error-verbose

/* The second section of a bison file contains the productions. Note that rules with the
 * same LHS may be joined together and separated with a pipe.
 */
%% 
prog : prog decl
     | prog stmt
     | %empty
; 

decl : tVAR tIDENTIFIER ':' type '=' exp ';'
     | tVAR tIDENTIFIER '=' exp ';'
;

type : tINT
     | tBOOL
     | tFLOAT
     | tSTRING
;

stmts : stmts stmt
      | %empty
;

stmt : tIDENTIFIER '=' exp ';'
     | tIF '(' exp ')' body
     | tIF '(' exp ')' body tELSE body
     | tWHILE '(' exp ')' body
     | tREAD '(' exp ')' ';'
     | tPRINT '(' exp ')' ';'
;

body : stmt
     | '{' stmts '}'
;

exp : tIDENTIFIER { printf("Load %s\n", $1); }
    | tINTVAL     { printf("Push %i\n", $1); }
    | tINTVAL     { printf("Push %i\n", $1); }
    | tINTVAL     { printf("Push %i\n", $1); }
    | '!' exp     { printf("Neg\n"); }
    | exp '*' exp { printf("Mult\n"); }
    | exp '/' exp { printf("Div\n"); }
    | exp '+' exp { printf("Plus\n"); }
    | exp '-' exp { printf("Minus\n"); }
    | exp tEQUAL exp { printf("Equal\n"); }
    | exp tNOTEQUAL exp { printf("Not Equal\n"); }
    | exp tATLEAST exp { printf("Greater or Equal Than\n"); }
    | exp tATMOST exp { printf("Less or Equal Than\n"); }
    | exp tGREATER exp { printf("Greater Than\n"); }
    | exp tLESS exp { printf("Less Than\n"); }
    | exp tAND exp { printf("And\n"); }
    | exp tOR exp { printf("Or\n"); }
    | '(' exp ')' { }
;

%%
