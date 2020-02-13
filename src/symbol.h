#include "tree.h"

#define HashSize 317

typedef struct SymbolTable SymbolTable;
typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *parent;
    STMT *declaration;
} SymbolTable;

SYMBOL *getSymbol(char *name, SymbolTable *t, int lineno);

void sym(STMT *ast);