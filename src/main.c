#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "modes.h"
#include "printer.h"
#include "symbol.h"

void yyflex();
void yyparse();

int main( int argc, const char* argv[] ) {

    if ( argc != 2 ) {
        printf("Wrong number of arguments\n");
        exit(1);
    }

    if ( strncmp(argv[1], "scan" , 4) ==0 ) {
        mode = SCAN;
        while(yylex()){}
        exit(0);
    }

    if ( strncmp(argv[1], "tokens" , 6) ==0 ) {
        mode = TOKENS;
        while(yylex()){}
        exit(0);
    }

    if ( strncmp(argv[1], "parse" , 5) == 0 ) {
        mode = PARSE;
        yyparse();
        printf("OK\n");
        exit(0);
    }

    if ( strncmp(argv[1], "pretty" , 6) == 0 ) {
        mode = PRETTY;
        yyparse();
        pretty(astRoot);
        exit(0);
    }

    if ( strncmp(argv[1], "symbol" , 6) == 0 ) {
        mode = SYMBOLPRINT;
        yyparse();
        sym(astRoot);
        exit(0);
    }

    if ( strncmp(argv[1], "typecheck" , 7) == 0 ) {
        mode = TYPECHECK;
        yyparse();
        sym(astRoot);
        //TODO typecheck
        exit(0);
    }

    if ( strncmp(argv[1], "codegen" , 7) == 0 ) {
        mode = CODEGEN;
        yyparse();
        //TODO typecheck
        codeGen(astRoot);
        exit(0);
    }

    fprintf(stderr, "Error: Invalid mode\n");
    exit(1);
}
