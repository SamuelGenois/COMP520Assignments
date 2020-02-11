#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STMT *makeStmtDeclarationInferred(char *name, int lineno) { return NULL; }
STMT *makeStmtDeclaration(char *name, Type type, , int lineno){ return NULL; }
STMT *makeStmtAssignment(char *name, EXP *exp, , int lineno){ return NULL; }

STMT *makeStmtIf(EXP *condition, STMT *block) { return NULL; }
STMT *makeStmtIfElse(EXP *condition, STMT *block1, STMT *block2) { return NULL; }
STMT *makeStmtWhile(EXP *condition, STMT *block) { return NULL; }
STMT *makeStmtRead(EXP *condition) { return NULL; }
STMT *makeStmtPrint(EXP *condition) { return NULL; }

EXP *makeExpIntLiteral(int val, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_IntLiteral;
    e->val.intLiteral = val;
    return e;
}
EXP *makeExpboolLiteral(char val, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_BoolLiteral;
    e->val.boolLiteral = val;
    return e;
}
EXP *makeExpFloatLiteral(double val, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_FloatLiteral;
    e->val.floatLiteral = val;
    return e;
}
EXP *makeExpStringLiteral(char *val, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_StringLiteral;
    e->val.strLiteral = strdup(val);
    return e;
}
EXP *makeExpIdentifier(char *name, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Identifier;
    e->val.identifier = strdup(name);
    return e;
}
EXP *makeExpOr(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Or;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpAnd(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_And;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpEqual(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Equal;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpLess(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Less;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpGreater(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Greater;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpLessOrEqual(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_LessOrEqual;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpGreaterOrEqual(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_GreaterOrEqual;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpNotEqual(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_NotEqual;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpAddition(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Addition;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpSubtraction(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Subtraction;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpMultiplication(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Multiplication;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpDivision(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Division;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeExpNot(EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Not;
    e->val.exp = exp;
    return e;
}
EXP *makeExpUnaryMinus(EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_UnaryMinus;
    e->val.exp = exp
    return e;
}