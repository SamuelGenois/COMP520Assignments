#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

char g_tokens;
void yyflex();
void yyparse();

int main( int argc, const char* argv[] ) {

    if ( argc != 2 ) {
        printf("Wrong number of arguments\n");
        exit(1);
    }

    if ( strncmp(argv[1], "scan" , 4) ) {
        g_tokens = 0;
        while(yylex()){}
        exit(0);
    }

    if ( strncmp(argv[1], "token" , 5) ) {
        g_tokens = 1;
        while(yylex()){}
        exit(0);
    }

    if ( strncmp(argv[1], "parser" , 6) ) {
        yyparse();
        exit(0);
    }

    printf("Invalid mode\n");
    exit(1);
}
