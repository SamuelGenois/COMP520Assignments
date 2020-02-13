#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

void printIndent(int indent){
    for(int i=0;i<indent;i++)
        printf("  ");
}

//Pretty printer
void prettyEXP(EXP *exp)
{
    switch (exp->kind) {
        case k_Identifier:
            printf("%s", exp->val.identifierExp.identifier);
            break;
        case k_IntLiteral:
            printf("%i", exp->val.intLiteral);
            break;
        case k_FloatLiteral:
            printf("%f", exp->val.floatLiteral);
            break;
        case k_BoolLiteral:
            if(exp->val.boolLiteral)
                printf("True");
            else
                printf("False");
            break;
        case k_StringLiteral:
            printf("%s", exp->val.strLiteral);
            break;
        case k_Addition:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" + ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Subtraction:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" - ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Multiplication:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" * ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Division:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" / ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_UnaryMinus:
            printf("-( ");
            prettyEXP(exp->val.exp);
            printf(" )");
            break;
        case k_Assignment:
            printf("%s = ", exp->val.assignment.identifier);
            prettyEXP(exp->val.assignment.exp);
            break;
        case k_Or:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" || ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_And:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" && ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Not:
            printf("!( ");
            prettyEXP(exp->val.exp);
            printf(" )");
            break;
        case k_Equal:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" == ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_NotEqual:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" != ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Greater:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" > ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_GreaterOrEqual:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" >= ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Less:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" < ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_LessOrEqual:
            printf("( ");
            prettyEXP(exp->val.binary.lhs);
            printf(" <= ");
            prettyEXP(exp->val.binary.rhs);
            printf(" )");
            break;
    }
}

void prettySTMT(STMT *stmt, int indent) {
    if(stmt == 0)
        return;
    
    prettySTMT(stmt->next, indent);

    if(stmt->kind == k_block)
        indent -= 1;

    printIndent(indent);

    switch(stmt->kind) {
        case k_decl:
            switch(stmt->val.declaration.type) {
                case type_int:
                    printf("var %s : int = ", stmt->val.declaration.identifier);
                    break;
                case type_bool:
                    printf("var %s : bool = ", stmt->val.declaration.identifier);
                    break;
                case type_float:
                    printf("var %s : float = ", stmt->val.declaration.identifier);
                    break;
                case type_string:
                    printf("var %s : string = ", stmt->val.declaration.identifier);
                    break;
                case type_infer:
                    printf("var %s = ", stmt->val.declaration.identifier);
                    break;
            }
            prettyEXP(stmt->val.declaration.exp);
            printf(";\n");
            break;
        case k_exp:
            prettyEXP(stmt->val.exp);
            printf(";\n");
            break;
        case k_if:
            printf("if ( ");
            prettyEXP(stmt->val.ifWhile.condition);
            printf(" )\n");
            prettySTMT(stmt->val.ifWhile.block, indent + 1);
            break;
        case k_ifelse:
            printf("if ( ");
            prettyEXP(stmt->val.ifElse.condition);
            printf(" )\n");
            prettySTMT(stmt->val.ifElse.block1, indent + 1);
            printIndent(indent);
            printf("else\n");
            prettySTMT(stmt->val.ifElse.block2, indent + 1);
            break;
        case k_while:
            printf("while ( ");
            prettyEXP(stmt->val.ifWhile.condition);
            printf(" )\n");
            prettySTMT(stmt->val.ifWhile.block, indent + 1);
            break;
        case k_read:
            printf("read(%s);\n", stmt->val.read.identifier);
            break;
        case k_print:
            printf("print(");
            prettyEXP(stmt->val.exp);
            printf(");\n");
            break;
        case k_block:
            printf("{\n");
            prettySTMT(stmt->val.blockContent, indent + 1);
            printIndent(indent);
            printf("}\n");
            break;
    }
}

void pretty(STMT *ast) {
    prettySTMT(ast, 0);
}

//Codegen
void codeGenEXP(EXP *exp) {
    switch (exp->kind) {
        case k_Identifier:
            printf("%s", exp->val.identifierExp.identifier);
            break;
        case k_BoolLiteral:
        case k_IntLiteral:
            printf("%i", exp->val.intLiteral);
            break;
        case k_FloatLiteral:
            printf("%f", exp->val.floatLiteral);
            break;
        case k_StringLiteral:
            printf("%s", exp->val.strLiteral);
            break;
        case k_Addition:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" + ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Subtraction:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" - ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Multiplication:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" * ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Division:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" / ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_UnaryMinus:
            printf("-( ");
            codeGenEXP(exp->val.exp);
            printf(" )");
            break;
        case k_Assignment:
            printf("%s = ", exp->val.assignment.identifier);
            codeGenEXP(exp->val.assignment.exp);
            break;
        case k_Or:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" || ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_And:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" && ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Not:
            printf("!( ");
            codeGenEXP(exp->val.exp);
            printf(" )");
            break;
        case k_Equal:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" == ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_NotEqual:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" != ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Greater:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" > ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_GreaterOrEqual:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" >= ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_Less:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" < ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
        case k_LessOrEqual:
            printf("( ");
            codeGenEXP(exp->val.binary.lhs);
            printf(" <= ");
            codeGenEXP(exp->val.binary.rhs);
            printf(" )");
            break;
    }
}

void codeGenSTMT(STMT *stmt, int indent) {
    if(stmt == 0)
        return;
    
    codeGenSTMT(stmt->next, indent);

    if(stmt->kind == k_block)
        indent -= 1;

    printIndent(indent);

    switch(stmt->kind) {
        case k_decl:
            switch(stmt->val.declaration.sym->type) {
                case type_bool:
                case type_int:
                    printf("int %s = ", stmt->val.declaration.identifier);
                    break;
                case type_float:
                    printf("float %s = ", stmt->val.declaration.identifier);
                    break;
                case type_string:
                    printf("char *%s = ", stmt->val.declaration.identifier);
                    break;
            }
            codeGenEXP(stmt->val.declaration.exp);
            printf(";\n");
            break;
        case k_exp:
            codeGenEXP(stmt->val.exp);
            printf(";\n");
            break;
        case k_if:
            printf("if ( ");
            codeGenEXP(stmt->val.ifWhile.condition);
            printf(" )\n");
            codeGenSTMT(stmt->val.ifWhile.block, indent + 1);
            break;
        case k_ifelse:
            printf("if ( ");
            codeGenEXP(stmt->val.ifElse.condition);
            printf(" )\n");
            codeGenSTMT(stmt->val.ifElse.block1, indent + 1);
            printIndent(indent);
            printf("else\n");
            codeGenSTMT(stmt->val.ifElse.block2, indent + 1);
            break;
        case k_while:
            printf("while ( ");
            codeGenEXP(stmt->val.ifWhile.condition);
            printf(" )\n");
            codeGenSTMT(stmt->val.ifWhile.block, indent + 1);
            break;
        case k_read:
            printf("scanf(");
            switch(stmt->val.read.sym->type) {
                case type_bool:
                case type_int:
                    printf("\"%%i\"");
                    break;
                case type_float:
                    printf("\"%%f\"");
                    break;
                case type_string:
                    printf("\"%%s\"");
                    break;
            }
            printf(",%s);\n", stmt->val.read.identifier);
            break;
        case k_print:
            printf("printf(");
            switch(stmt->val.exp->type) {
                case type_bool:
                case type_int:
                    printf("\"%%i\",");
                    break;
                case type_float:
                    printf("\"%%f\",");
                    break;
                case type_string:
                    printf("\"%%s\",");
                    break;
            }
            codeGenEXP(stmt->val.exp);
            printf(");\n");
            break;
        case k_block:
            printf("{\n");
            codeGenSTMT(stmt->val.blockContent, indent + 1);
            printIndent(indent);
            printf("}\n");
            break;
    }
}

void codeGen(STMT *ast) {
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n");
    printf("#include <string.h>\n\n");
    printf("void main() {\n");
    codeGenSTMT(ast, 1);
    printf("}\n");
}