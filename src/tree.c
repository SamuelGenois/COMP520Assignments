#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

STMT *makeStmtDeclarationInferred(char *name, EXP *exp, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = k_Decl;
    s->val.declaration.exp = exp;
    s->val.declaration.type = Type.type_infer;
    s->val.declaration.identifier = strdup(name);
    return s;
}
STMT *makeStmtDeclaration(char *name, EXP *exp, Type type, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = k_Decl;
    s->val.declaration.exp = exp;
    s->val.declaration.type = type;
    s->val.declaration.identifier = strdup(name);
    return s;
}

STMT *makeStmtExp(EXP *exp, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = k_exp;
    s->val.exp = exp;
    return s;
}

STMT *makeStmtIf(EXP *condition, STMT *block, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = k_if;
    s->val.ifWhile.condition = condition;
    s->val.ifWhile.block = block;
    return s;
}
STMT *makeStmtIfElse(EXP *condition, STMT *block1, STMT *block2, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = k_ifelse;
    s->val.ifWhile.condition = condition;
    s->val.ifWhile.block1 = block1;
    s->val.ifWhile.block2 = block2;
    return s;
}
STMT *makeStmtWhile(EXP *condition, STMT *block, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = k_while;
    s->val.ifElse.condition = condition;
    s->val.ifElse.block = block;
    return s;
}
STMT *makeStmtRead(char *readIdentifier, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = k_read;
    s->val.readIdentifier = readIdentifier;
    return s;
}
STMT *makeStmtPrint(EXP *output, int lineno)  {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = k_print;
    s->val.exp = output;
    return s;
}
STMT *makeStmtBlock(STMT *statements, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = k_print;
    s->val.blockContent = statements;
    return s;
}

EXP *makeExpAssignment(char *name, EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_Assign;
    e->val.assignment.exp = exp;
    e->val.assignment.identifier = strdup(name);
    return e;
}
EXP *makeExpIntLiteral(int val, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_IntLiteral;
    e->val.intLiteral = val;
    return e;
}
EXP *makeExpBoolLiteral(char val, int lineno) {
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
    e->val.identifierExp.identifier = strdup(name);
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
