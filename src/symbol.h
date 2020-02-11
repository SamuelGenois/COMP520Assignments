#include "tree.h"

#define HashSize 317

typedef struct SYMBOL SYMBOL;
struct SYMBOL {
    char *name;
    struct VAR *variable;
    struct SYMBOL *next;
};

typedef struct SymbolTable SymbolTable;
typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *parent;
} SymbolTable;

//Root symbol table
SymbolTable *symbolTable