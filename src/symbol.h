#define HashSize 317

typedef struct SymbolTable SymbolTable;
typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *parent;
    STMT *declaration;
} SymbolTable;

void sym(STMT *ast);