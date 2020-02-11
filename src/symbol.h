#include "tree.h"

#define HashSize 317

typedef struct SymbolTable SymbolTable;
typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *parent;
} SymbolTable;

//Root symbol table
SymbolTable *symbolTable