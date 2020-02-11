STMT *makeStmtDeclarationInferred(char *name, int lineno) { return NULL; }
STMT *makeStmtDeclaration(char *name, Type type, , int lineno){ return NULL; }

STMT *makeStmtAssignment(char *name, EXP *exp, , int lineno){ return NULL; }

//STMT *makeStmtSequence(STMT *next, STMT *rest) { return NULL; }
STMT *makeStmtIf(EXP *condition, STMT *block) { return NULL; }
STMT *makeStmtIfElse(EXP *condition, STMT *block1, STMT *block2) { return NULL; }
STMT *makeStmtWhile(EXP *condition, STMT *block) { return NULL; }
STMT *makeStmtRead(EXP *condition) { return NULL; }
STMT *makeStmtPrint(EXP *condition) { return NULL; }

EXP *makeExpIntLiteral(int val, int lineno) { return NULL; }
EXP *makeExpboolLiteral(char val, int lineno) { return NULL; }
EXP *makeExpFloatLiteral(double val, int lineno) { return NULL; }
EXP *makeExpstringLiteral(char *val, int lineno) { return NULL; }
EXP *makeExpIdentifier(char *name, int lineno) { return NULL; }
EXP *makeExpOr(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpAnd(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpEqual(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpLess(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpGreater(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpLessOrEqual(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpGreaterOrEqual(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpNotEqual(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpAddition(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpSubtraction(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpMultiplication(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpDivision(EXP *lhs, EXP *rhs, int lineno) { return NULL; }
EXP *makeExpNot(EXP *not, int lineno) { return NULL; }
EXP *makeExpUnaryMinus(EXP *uminus, int lineno) { return NULL; }