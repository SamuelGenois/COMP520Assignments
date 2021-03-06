#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modes.h"
#include "symbol.h"

int Hash(char *str) {
    unsigned int hash = 0;
    while (*str) hash = (hash << 1) + *str++;
    return hash % HashSize;
}

void printSymTable(SymbolTable *symbolTable, int lineno) {
    printf("Symbol table for block starting at line %i:\n", lineno);
    for (int i = 0; i < HashSize; i++) {
        SYMBOL *sym = symbolTable->table[i];
        while(sym != 0) {
            printf("    %s : ", sym->name);
            switch(sym->type) {
                case type_infer:
                    printf("inferred\n");
                    break;
                case type_int:
                    printf("int\n");
                    break;
                case type_bool:
                    printf("bool\n");
                    break;
                case type_float:
                    printf("float\n");
                    break;
                case type_string:
                    printf("string\n");
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

SYMBOL *getSymbol(char *name, SymbolTable *t, int lineno) {
    int i = Hash(name);
    
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name) == 0) return s;
    }
    
    if (t->parent == NULL) {
        fprintf(stderr, "Error: (line %d) variable %s has not been declared\n", lineno, name);
        exit(1);
    }
    
    return getSymbol(name, t->parent, lineno);
}

SYMBOL *putSymbol(char *name, Type type, SymbolTable *t, int lineno) {
    int i = Hash(name);
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name) == 0) {
            fprintf(stderr, "Error: (line %d) variable %s is already declared\n", lineno, name);
            exit(1);
        }
    }
    SYMBOL *s = malloc(sizeof(SYMBOL));
    s->name = name;
    s->type = type;
    s->next = t->table[i];
    t->table[i] = s;
    return s;
}

void symExp(EXP *exp, SymbolTable *symbolTable) {
    switch (exp->kind) {
        case k_Identifier:
            exp->val.identifierExp.sym = getSymbol(exp->val.identifierExp.identifier, symbolTable, exp->lineno);
            break;
        case k_Assignment:
            exp->val.assignment.sym = getSymbol(exp->val.assignment.identifier, symbolTable, exp->lineno);
            symExp(exp->val.assignment.exp, symbolTable);
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
            symExp(exp->val.binary.lhs, symbolTable);
            symExp(exp->val.binary.rhs, symbolTable);
            break;
        case k_UnaryMinus:
        case k_Not:
            symExp(exp->val.exp, symbolTable);
            break;
        case k_IntLiteral:
        case k_BoolLiteral:
        case k_FloatLiteral:
        case k_StringLiteral:
            break;
    }
}

void symStmt(STMT *stmt, SymbolTable *symbolTable) {
    SymbolTable *subTable;
    if (stmt == NULL) {
        return;
    }
    symStmt(stmt->next, symbolTable);
    switch (stmt->kind) {
        case k_decl:
            symExp(stmt->val.declaration.exp, symbolTable);
            stmt->val.declaration.sym = putSymbol(
                stmt->val.declaration.identifier,
                stmt->val.declaration.type,
                symbolTable,
                stmt->lineno);
            break;
        case k_print:
        case k_exp:
            symExp(stmt->val.exp, symbolTable);
            break;
        case k_if:
            symExp(stmt->val.ifWhile.condition, symbolTable);
            symStmt(stmt->val.ifWhile.block, symbolTable);
            break;
        case k_ifelse:
            symExp(stmt->val.ifElse.condition, symbolTable);
            symStmt(stmt->val.ifElse.block1, symbolTable);
            symStmt(stmt->val.ifElse.block2, symbolTable);
            break;
        case k_while:
            symExp(stmt->val.ifWhile.condition, symbolTable);
            symStmt(stmt->val.ifWhile.block, symbolTable);
            break;
        case k_read:
            stmt->val.read.sym = getSymbol(stmt->val.read.identifier, symbolTable, stmt->lineno);
            break;
        case k_block:
            subTable = scopeSymbolTable(symbolTable);
            symStmt(stmt->val.blockContent, subTable);
            if(mode == SYMBOLPRINT)
                printSymTable(subTable, stmt->lineno);
            break;
    }
}

void sym(STMT *ast) {
    SymbolTable *table = initSymbolTable();
    symStmt(ast, table);
    if(mode == SYMBOLPRINT)
        printSymTable(table, 0);
}