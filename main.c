#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "modes.h"

char mode;
void yyflex();
void yyparse();

int main( int argc, const char* argv[] ) {

    if ( argc != 2 ) {
        printf("Wrong number of arguments\n");
        exit(1);
    }

    if ( strncmp(argv[1], "scan" , 4) ) {
        mode = SCAN;
        while(yylex()){}
        exit(0);
    }

    if ( strncmp(argv[1], "tokens" , 6) ) {
        mode = TOKENS;
        while(yylex()){}
        exit(0);
    }

    if ( strncmp(argv[1], "parse" , 5) ) {
        mode = PARSE;
        yyparse();
        exit(0);
    }

    printf("Invalid mode\n");
    exit(1);
}
