#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"

void reportError(char *msg, int lineno) {
    fprintf(stderr, "Error: (line %d) %s\n", lineno, msg);
    exit(1);
}

void checkBOOL(Type type, int lineno) {
    if (type != type_bool)
        reportError("bool type expected", lineno);
}

void checkFLOAT(Type type, int lineno) {
    if (type != type_float && type != type_int)
        reportError("int or float type expected", lineno);
}

void checkINT(Type type, int lineno) {
    if (type != type_int)
        reportError("int type expected", lineno);
}

void checkSTRING(Type type, int lineno) {
    if (type != type_string)
        reportError("string type expected", lineno);
}

int assignType(Type type1, Type type2) {
    if(type1 == type_float)
        return type2 == type_float || type2 == type_int;
    return type1 == type2;
}

void typeExp(EXP *e) {
    printf("Entering exp of kind %i on line %i\n", e->kind, e->lineno);
    switch (e->kind) {
        case k_Identifier:
            e->type = typeVar(e->val.identifierExp.sym);
            break;
        case k_Assignment:
            e->type = e->val.assignment.sym->type;
            typeExp(e->val.assignment.exp);
            if (!assignType(e->type, e->val.assignment.exp->type))
                reportError("illegal assignment", e->lineno);
            break;
        case k_Or:
        case k_And:
            typeExp(e->val.binary.lhs);
            typeExp(e->val.binary.rhs);
            checkBOOL(e->val.binary.lhs->type, e->lineno);
            checkBOOL(e->val.binary.rhs->type, e->lineno);
            e->type = type_bool;
            break;
        case k_Less:
        case k_Greater:
        case k_LessOrEqual:
        case k_GreaterOrEqual:
            typeExp(e->val.binary.lhs);
            typeExp(e->val.binary.rhs);
            checkFLOAT(e->val.binary.lhs->type, e->lineno);
            checkFLOAT(e->val.binary.rhs->type, e->lineno);
            e->type = type_bool;
            break;
        case k_Equal:
        case k_NotEqual:
            typeExp(e->val.binary.lhs);
            typeExp(e->val.binary.rhs);
            if (!assignType(e->val.binary.lhs->type, e->val.binary.rhs->type) &&
                !assignType(e->val.binary.rhs->type, e->val.binary.lhs->type)) {
                    if(e->kind == k_Equal)
                        reportError("arguments for == have wrong types", e->lineno);
                    else
                        reportError("arguments for != have wrong types", e->lineno);
            }
            e->type = type_bool;
            break;
        case k_Addition:
            typeExp(e->val.binary.lhs);
            typeExp(e->val.binary.rhs);
            if (e->val.binary.lhs->type == type_int && e->val.binary.rhs->type == type_int)
                e->type = type_int;
            else if (
                (e->val.binary.lhs->type == type_int || e->val.binary.lhs->type == type_float) &&
                (e->val.binary.rhs->type == type_int || e->val.binary.rhs->type == type_float))
                e->type = type_float;
            else if (e->val.binary.lhs->type == type_string && e->val.binary.rhs->type == type_string)
                e->type = type_string;
            else
                reportError("arguments for + have wrong types", e->lineno);
            break;
        case k_Subtraction:
        case k_Multiplication:
        case k_Division:
            typeExp(e->val.binary.lhs);
            typeExp(e->val.binary.rhs);
            if (e->val.binary.lhs->type == type_int && e->val.binary.rhs->type == type_int)
                e->type = type_int;
            else if (
                (e->val.binary.lhs->type == type_int || e->val.binary.lhs->type == type_float) &&
                (e->val.binary.rhs->type == type_int || e->val.binary.rhs->type == type_float))
                e->type = type_float;
            else
                switch (kind) {
                    case k_Subtraction:
                        reportError("arguments for - have wrong types", e->lineno);
                        break;
                    case k_Multiplication:
                        reportError("arguments for * have wrong types", e->lineno);
                        break;
                    case k_Division:
                        reportError("arguments for / have wrong types", e->lineno);
                        break;
                }
            break;
        case k_Not:
            typeExp(e->val.exp);
            checkBOOL(e->val.exp->type, e->lineno);
            e->type = type_bool;
            break;
        case k_UnaryMinus:
            typeExp(e->val.exp);
            checkFLOAT(e->val.exp->type, e->lineno);
            e->type = e->val.exp->type;
            break;
        case k_IntLiteral:
            e->type = type_int;
            break;
        case k_BoolLiteral:
            e->type = type_bool;
            break;
        case k_FloatLiteral:
            e->type = type_float;
            break;
        case k_StringLiteral:
            e->type = type_string;
            break;
    }
}

void typeStmt(STMT *s) {
    Type type;
    if (s == NULL)
        return;
    printf("Entering stmt of kind %i on line %i\n", s->kind, s->lineno);
    switch (s->kind) {
        case k_exp:
            typeExp(s->val.exp);
            break;
        case k_if:
            typeExp(s->val.ifWhile.condition);
            checkBOOL(s->val.ifWhile.condition->type, s->lineno);
            typeStmt(s->val.ifWhile.block);
            break;
        case k_ifelse:
            typeExp(s->val.ifElse.condition);
            checkBOOL(s->val.ifElse.condition->type, s->lineno);
            typeStmt(s->val.ifElse.block1);
            typeStmt(s->val.ifElse.block2);
            break;
        case k_while:
            typeExp(s->val.ifWhile.condition);
            checkBOOL(s->val.ifWhile.condition->type, s->lineno);
            typeStmt(s->val.ifWhile.block);
            break;
        case k_block:
            typeStmt(s->val.blockContent);
            break;
        case k_decl:
            if(s->val.declaration.type == type_infer)
                s->val.declaration.sym->type = typeExp(s->val.declaration.exp);
            else
                if(!assignType(s->val.declaration.sym->type, s->val.declaration.exp->type))
                    reportError("illegal assignment", e->lineno);
            break;
        case k_print:
        case k_read:
            break;
    }
}

void type(STMT *ast) {
    typeStmt(ast);
}