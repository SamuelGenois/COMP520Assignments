//Type and variable struct
typedef enum {
    type_int,
    type_bool,
    type_float,
    type_string
} Type;

typedef struct VAR VAR;
struct VAR {
    int lineno;
    char *identifier;
    Type type;
};

//Expression node
typedef enum {
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
    TYPE *type;
    ExpKind kind;
    union {
        char *identifier;
        int intLiteral;
        double floatLiteral;
        char boolLiteral;
        char *strLiteral;
        struct { EXP *lhs; EXP *rhs; } binary;
        struct { EXP *inner; } unary;
    } val;
};

typedef enum {
    k_skip,
    k_local,
    k_exp,
    k_sequence,
    k_if,
    k_ifelse,
    k_while,
} StmtKind;

//STMT node
typedef struct STMT STMT;
struct STMT {
    int lineno;
    StmtKind kind;
    union {
        struct EXP *expression;
        struct VAR *var;
        struct {
            struct STMT *next;
            struct STMT *rest;
        } sequence;
        struct {
            struct EXP *condition;
            struct STMT *block;
        } ifWhile;
        struct {
            struct EXP *condition;
            struct STMT *block1;
            struct STMT *block2;
        } ifElse;
    } val;
};

//The root node
STMT *astRoot;

//AST building functions
//STMT *makeStmtAssignment(char *name, Type type, );


STMT *makeStmtskip();
STMT *makeStmtexp(EXP *exp);
STMT *makeStmtSequence(STMT *next, STMT *rest);
STMT *makeStmtRf(EXP *condition, STMT *block);
STMT *makeStmtIfElse(EXP *condition, STMT *block1, STMT *block2);
STMT *makeStmtWhile(EXP *condition, STMT *block);

EXP *makeExpIntLiteral(int val);
EXP *makeExpboolLiteral(int val);
EXP *makeExpFloatLiteral(double val);
EXP *makeExpstringLiteral(char *val);
EXP *makeExpid(char *name);
EXP *makeExpassign(char *lhs, EXP *rhs);
EXP *makeExpOr(EXP *lhs, EXP *rhs);
EXP *makeExpAnd(EXP *lhs, EXP *rhs);
EXP *makeExpEqual(EXP *lhs, EXP *rhs);
EXP *makeExpLess(EXP *lhs, EXP *rhs);
EXP *makeExpGreater(EXP *lhs, EXP *rhs);
EXP *makeExpLessOrEqual(EXP *lhs, EXP *rhs);
EXP *makeExpGreaterOrEqual(EXP *lhs, EXP *rhs);
EXP *makeExpnEqual(EXP *lhs, EXP *rhs);
EXP *makeExpAdditoin(EXP *lhs, EXP *rhs);
EXP *makeExpSubtraction(EXP *lhs, EXP *rhs);
EXP *makeExpMultiplication(EXP *lhs, EXP *rhs);
EXP *makeExpDivision(EXP *lhs, EXP *rhs);
EXP *makeExpNot(EXP *not);
EXP *makeExpUnaryMinus(EXP *uminus);
