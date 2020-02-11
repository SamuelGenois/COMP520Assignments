#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

//Pretty printer
void pretty(STMT *ast) {
    prettySTMT(STMT *ast);
}

void prettySTMT(STMT *stmt) {
    if(stmt == 0)
        return;
    
    prettySTMT(stmt->next);

    switch(stmt->kind) {
        case k_exp:
            prettyEXP(stmt->exp);
            printf(";\n");
            break;
        case k_if:
            printf("if ( ");
            prettyEXP(stmt->ifWhile.condition);
            printf(" )\n");
            prettySTMT(stmt->ifWhile.block);
            break;
        case k_ifelse:
            printf("if ( ");
            prettyEXP(stmt->ifElse.condition);
            printf(" )\n");
            prettySTMT(stmt->ifElse.block1);
            printf("else\n");
            prettySTMT(stmt->ifElse.block2);
            break;
        case k_while:
            printf("while ( ");
            prettyEXP(stmt->ifWhile.condition);
            printf(" )\n");
            prettySTMT(stmt->ifWhile.block);
            break;
        case k_read:
            printf("read(%s);\n", stmt->readIdentifier);
            break;
        case k_print:
            printf("print(");
            prettyEXP(stmt->exp);
            printf(")\n");
            break;
        case k_block:
            printf("{\n");
            prettySTMT(stmt->blockContent);
            printf("\n}\n");
            break;
    }
}

void prettyEXP(EXP *exp)
{
    switch (exp->kind) {
        case k_Decl:
            switch(exp->declaration) {
                case type_int:
                    printf("var %s : int = ", exp->declaration.identifier)
                    break;
                case type_bool:
                    printf("var %s : bool = ", exp->declaration.identifier)
                    break;
                case type_float:
                    printf("var %s : float = ", exp->declaration.identifier)
                    break;
                case type_string:
                    printf("var %s : string = ", exp->declaration.identifier)
                    break;
                case type_infer:
                    printf("var %s = ", exp->declaration.identifier)
                    break;
            }
            prettyEXP(exp->declaration.exp);
            break;
        case k_Identifier:
            printf("%s", exp->identifierExp.identifier);
            break;
        case k_IntLiteral:
            printf("%i", exp->intLiteral);
            break;
        case k_FloatLiteral:
            printf("%f", exp->floatLiteral);
            break;
        case k_BoolLiteral:
            if(exp->boolLiteral)
                printf("True");
            else
                printf("False");
            break;
        case k_StringLiteral:
            printf("%s", exp->strLiteral);
            break;
        case k_Addition:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" + ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_Subtraction:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" - ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_Multiplication:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" * ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_Division:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" / ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
        case k_UnaryMinus:
            printf("-( ");
            prettyEXP(exp->exp);
            printf(" )");
        case k_Assignment:
            printf("%s = ", exp->assignment.identifier);
            break;
        case k_Or:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" || ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_And:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" && ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_Not:
            printf("!( ");
            prettyEXP(exp->exp);
            printf(" )");
            break;
        case k_Equal:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" == ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_NotEqual:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" != ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_Greater:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" > ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_GreaterOrEqual:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" >= ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_Less:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" < ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
        case k_LessOrEqual:
            printf("( ");
            prettyEXP(exp->binary.lhs);
            printf(" <= ");
            prettyEXP(exp->binary.rhs);
            printf(" )");
            break;
    }
}

//Codegen
void codeGen(STMT *ast) {
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n");
    printf("#include <string.h>\n");
    genCodeSTMT(stmt);
}

void codeGenSTMT(STMT *stmt) {
    fprintf(stderr, "Error: Not Implemented\n");
	exit(1);
}

void codeGenEXP(EXP *exp, int indentCount) {
}
