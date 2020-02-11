//Type and variable struct
typedef enum {
    type_infer,
    type_int,
    type_bool,
    type_float,
    type_string
} Type;

typedef struct SYMBOL SYMBOL;
struct SYMBOL {
    char *name;
    Type type;
    struct SYMBOL *next;
};

//Expression node
typedef enum {
    k_Decl,
    k_Assign,
    k_Identifier,
    k_IntLiteral,
    k_FloatLiteral,
    k_BoolLiteral,
    k_StringLiteral,
    k_Addition,
    k_Subtraction,
    k_Multiplication,
    k_Division,
    k_UnaryMinus,
    k_Assignment,
    k_Or,
    k_And,
    k_Not,
    k_Equal,
    k_NotEqual,
    k_Greater,
    k_GreaterOrEqual,
    k_Less,
    k_LessOrEqual
} ExpKind;

typedef struct EXP EXP;
struct EXP {
    int lineno;
    Type type;
    ExpKind kind;
    union {
        char *identifier;
        int intLiteral;
        double floatLiteral;
        char boolLiteral;
        char *strLiteral;
        struct {
            EXP *lhs;
            EXP *rhs;
        } binary;
        struct {
            EXP *expression;
            SYMBOL *sym;
            Type type;
            char *identifier;
        } declaration;
        struct {
            EXP *expression;
            SYMBOL *sym;
            char *identifier;
        } assignment;
        EXP *exp;
    } val;
};

typedef enum {
    k_exp,
    k_if,
    k_ifelse,
    k_while,
    k_read,
    k_print,
    k_block
} StmtKind;

//STMT node
typedef struct STMT STMT;
struct STMT {
    int lineno;
    StmtKind kind;
    union {
        struct {
            struct EXP *condition;
            struct STMT *block;
        } ifWhile;
        struct {
            struct EXP *condition;
            struct STMT *block1;
            struct STMT *block2;
        } ifElse;
        STMT *blockContent;
        char *readIdentifier;
    } val;
    STMT *next;
};

//The root node
STMT *astRoot;

//AST building functions
STMT *makeStmtExp(EXP *condition, int lineno);
STMT *makeStmtIf(EXP *condition, STMT *block, int lineno);
STMT *makeStmtIfElse(EXP *condition, STMT *block1, STMT *block2, int lineno);
STMT *makeStmtWhile(EXP *condition, STMT *block, int lineno);
STMT *makeStmtRead(EXP *input, int lineno);
STMT *makeStmtPrint(EXP *output, int lineno);
STMT *makeStmtBlock(STMT *statements, int lineno);

EXP *makeExpDeclarationInferred(char *name, EXP *exp, int lineno);
EXP *makeExpDeclaration(char *name, EXP *exp, Type type, int lineno);
EXP *makeExpAssignment(char *name, EXP *exp, int lineno);
EXP *makeExpIntLiteral(int val, int lineno);
EXP *makeExpboolLiteral(int val, int lineno);
EXP *makeExpFloatLiteral(double val, int lineno);
EXP *makeExpStringLiteral(char *val, int lineno);
EXP *makeExpIdentifier(char *name, int lineno);
EXP *makeExpOr(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpAnd(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpEqual(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpLess(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpGreater(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpLessOrEqual(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpGreaterOrEqual(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpNotEqual(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpAddition(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpSubtraction(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpMultiplication(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpDivision(EXP *lhs, EXP *rhs, int lineno);
EXP *makeExpNot(EXP *exp, int lineno);
EXP *makeExpUnaryMinus(EXP *exp, int lineno);
