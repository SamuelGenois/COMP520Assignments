%{
#include "parser.tab.h" // Token definitions from the parser
#include <string.h>
#include <stdlib.h>

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

char mode;
%}

DIGIT [0-9]

%option yylineno
%option noinput
%option nounput

/* The second section of a flex file contains the regular expressions, using helper definitions
 * where appropriate ({<helper name>}). Sections in flex are divided by %%.
 *
 * Each line contains the regex, followed by the scanner action. Actions are executed when
 * a token is matched. A missing action is treated as a NOP.
 *
 * When building a scanner+parser combo, the parser is responsible for fetching the next token
 * from the scanner, which returns scans and returns a single token at a time. As part of the
 * action, we thus return the next token. Tokens can either be (a) a character; or (b) a token
 * defined in bison (included in y.tab.h).
 */

/* Note the use of 3 keywords:
 *    - yytext: Matched text
 *    - yylineno: Convenience variable for the line number provided by %option yylineno
 *    - yylval: Scanners transform input text into tokens (internally stored as an int) and pass
 *              them to the parser. For some the tokens (identifiers, constants), the original
 *              text is required in later phases. bison provides a variable yylval for each token
 *              to store this extra data. The definition of the yylval struct is provided as
 *              part of the bison grammar file.
 */
%%
[ \t\r\n]+

"+"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKEN) printf("+\n"); return '+'; }
"-"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKEN) printf("-\n"); return '-'; }
"*"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKEN) printf("*\n"); return '*'; }
"/"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKEN) printf("/\n"); return '/'; }
"("     { if (mode == SCAN) printf("OK\n"); if (mode == TOKEN) printf("(\n"); return '('; }
")"     { if (mode == SCAN) printf("OK\n"); if (mode == TOKEN) printf(")\n"); return ')'; }

0|([1-9]{DIGIT}*) {
    if (mode == SCAN)
        printf("OK\n");
    if (mode == TOKEN)
        fprintf("Interger value: %s\n", yytext);
	yylval.intval = atoi(yytext);
	return tINTVAL;
}
[a-zA-Z_][a-zA-Z0-9_]* {
    if (mode == SCAN)
        printf("OK\n");
    if (mode == TOKEN)
        fprintf("identifier: %s\n", yytext);
	yylval.identifier = strdup(yytext);
	return tIDENTIFIER;
}

. 	{ fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }
%%