STMT *makeStmtskip() { return NULL { return NULL; } }
STMT *makeStmtexp(EXP *exp) { return NULL; }
STMT *makeStmtSequence(STMT *next, STMT *rest) { return NULL; }
STMT *makeStmtRf(EXP *condition, STMT *block) { return NULL; }
STMT *makeStmtIfElse(EXP *condition, STMT *block1, STMT *block2) { return NULL; }
STMT *makeStmtWhile(EXP *condition, STMT *block) { return NULL; }

EXP *makeExpIntLiteral(int val) { return NULL; }
EXP *makeExpboolLiteral(int val) { return NULL; }
EXP *makeExpFloatLiteral(double val) { return NULL; }
EXP *makeExpstringLiteral(char *val) { return NULL; }
EXP *makeExpid(char *name) { return NULL; }
EXP *makeExpassign(char *lhs, EXP *rhs) { return NULL; }
EXP *makeExpOr(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpAnd(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpEqual(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpLess(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpGreater(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpLessOrEqual(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpGreaterOrEqual(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpnEqual(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpAdditoin(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpSubtraction(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpMultiplication(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpDivision(EXP *lhs, EXP *rhs) { return NULL; }
EXP *makeExpNot(EXP *not) { return NULL; }
EXP *makeExpUnaryMinus(EXP *uminus) { return NULL; }