#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modes.h"
#include "symbol.h"

#define NULL 0

int Hash(char *str) {
    unsigned int hash = 0;
    while (*str) hash = (hash << 1) + *str++;
    return hash % HashSize;
}

void printSymTable(SymbolTable *symbolTable, int lineno) {
    printf("SymbolTable (starting line %i) :\n", lineno);
    for (int i = 0; i < HashSize; i++) {
        SYMBOL *sym = t->table[i];
        while(sym != 0) {
            printf("  Symbol:");
            printf("    name: %s\n", sym->name);
            switch(sym->type) {
                case type_infer:
                    printf("    type: inferred\n");
                    break;
                case type_int:
                    printf("    type: int\n");
                    break;
                case type_bool:
                    printf("    type: bool\n");
                    break;
                case type_float:
                    printf("    type: float\n");
                    break;
                case type_string:
                    printf("    type: string\n");
                    break;
            }
            sym = sym->next;
        }
    }
}

SymbolTable *initSymbolTable() {
    SymbolTable *t = malloc(sizeof(SymbolTable));
    for (int i = 0; i < HashSize; i++) {
        t->table[i] = NULL;
    }
    t->parent = NULL;
    return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *s) {
    SymbolTable *t = initSymbolTable();
    t->parent = s;
    return t;
}

SYMBOL *getSymbol(char *name, SymbolTable *t) {
    int i = Hash(name);
    
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name) == 0) return s;
    }
    
    if (t->parent == NULL)
        return NULL;
    
    return getSymbol(t->parent, name);
}

SYMBOL *putSymbol(char *name, Type type, SymbolTable *t, int lineno) {
    int i = Hash(name);
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name) == 0) {
            fprintf(stderr, "Error: (line %d) variable %s is already declared\n", lineno, name);
            exit(1);
        }
    SYMBOL *s = malloc(sizeof(SYMBOL));
    s->name = name;
    s->type = type;
    s->next = t->table[i];
    t->table[i] = s;
    return s;
}

void symExp(EXP *exp, SymbolTable *symbolTable) {
    printf("Entering exp, kind: %i", exp->kind);
    switch (exp->kind) {
        case k_Identifier:
            exp->val.identifierExp.sym = getSymbol(exp->val.assignment.identifier, symbolTable);
            break;
        case k_Assignment:
            exp->val.assignment.sym = getSymbol(exp->val.assignment.identifier, symbolTable);
            symImplementationEXP(exp->val.assignment.exp, symbolTable);
            break;
        case k_Addition:
        case k_Subtraction:
        case k_Multiplication:
        case k_Division:
        case k_Or:
        case k_And:
        case k_Equal:
        case k_NotEqual:
        case k_Greater:
        case k_GreaterOrEqual:
        case k_Less:
        case k_LessOrEqual:
            symImplementationEXP(exp->val.binary.lhs, symbolTable);
            symImplementationEXP(exp->val.binary.lhs, symbolTable);
            break;
        case k_UnaryMinus:
            printf("-( ");
            prettyEXP(exp->val.exp);
            printf(" )");
            break;
        case k_Not:
            symImplementationEXP(exp->val.exp, symbolTable);
            break;
    }
}

void symStmt(STMT *stmt, SymbolTable *symbolTable) {
    printf("Entering stmt, kind: %i", stmt->kind);
    if (stmt == NULL) {
        return;
    }
    symStmt(stmt->next, symbolTable);
    switch (stmt->kind) {
        case k_decl:
            stmt->val.declaration.sym = putSymbol(
                stmt->val.declaration.identifier,
                stmt->val.declaration.type,
                symbolTable,
                stmt->lineno);
            break;
        case k_exp:
            symImplementationEXP(stmt->val.expS,this,sym,stat);
            break;
        case k_if:
            symImplementationEXP(->val.ifS.condition,this,sym,stat);
            symStmt(s->val.ifS.body,this,sym,stat);
            break;
        case k_ifelse:
            symImplementationEXP(s->val.ifelseS.condition,this,sym,stat);
            symStmt(s->val.ifelseS.thenpart,this,sym,stat);
            symStmt(s->val.ifelseS.elsepart,this,sym,stat);
            break;
        case k_while:
            symImplementationEXP(s->val.whileS.condition,this,sym,stat);
            symStmt(s->val.whileS.body,this,sym,stat);
            break;
        case k_read:
            //TODO
            break;
        case k_print:
            //TODO
            break;
        case k_block:
            SymbolTable *subTable = scopeSymbolTable(symbolTable);
            symStmt(stmt->val.blockContent, subTable);
            if(mode == SYMBOLPRINT)
                printSymTable(subTable, stmt->lineno)
            break;
    }

    void sym(STMT *ast) {
        SymbolTable *table = initSymbolTable()
        symStmt(ast, table);
        if(mode == SYMBOLPRINT)
            printSymTable(table, 0);
    }
}