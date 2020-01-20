#include <stdio.h>
#include <string.h>

char g_tokens;
void yyflex();
void yyparse();

int main( int argc, const char* argv[] ) {

    if ( argc != 1 ) {
        //print error message
        exit(1);
    }

    if ( strncmp(argv[0], "scan" , 4) ) {
        g_tokens = 0;
        while(yylex()){}
        exit(0);
    }

    if ( strncmp(argv[0], "token" , 5) ) {
        g_tokens = 1;
        while(yylex()){}
        exit(0);
    }

    if ( strncmp(argv[0], "parser" , 6) ) {
        yyparse();
        exit(0);
    }

    //print error message
    exit(1);
}