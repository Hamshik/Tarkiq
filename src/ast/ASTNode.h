#ifndef ASTNODE_H
#define ASTNODE_H

#include "../utils/uhash.h"
#include <stdbool.h>

typedef enum ASTKind {
    AST_NUM,
    AST_BINOP,
    AST_UNOP,
    AST_VAR,
    AST_ASSIGN,
    AST_SEQ,
    NODE_IF,
    NODE_FOR,
    AST_STR,
    AST_CHAR,
    AST_BOOL
} ASTKind_t;

typedef enum DataTypes{
    INT,
    FLOAT,
    DOUBLE,
    SHORT,
    BOOL,
    STRINGS,
    CHARACTER,
    UNKNOWN
} DataTypes_t;

typedef enum OP_kind {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_POW,
    OP_AND, OP_OR, OP_NOT,
    OP_EQ, OP_NEQ, OP_LT, OP_LE, OP_GT, OP_GE,
    OP_LSHIFT, OP_RSHIFT,
    OP_BITAND, OP_BITOR, OP_BITXOR, OP_BITNOT,
    OP_NEG, OP_POS,
    OP_ASSIGN, OP_PLUS_ASSIGN, OP_MINUS_ASSIGN,
    OP_MUL_ASSIGN, OP_DIV_ASSIGN, OP_MOD_ASSIGN, OP_POW_ASSIGN,
    OP_LSHIFT_ASSIGN, OP_RSHIFT_ASSIGN,
    OP_INC, OP_DEC
} OP_kind_t;

typedef union {
    int inum;
    float fnum;
    double lfnum;
    short shnum;
    bool bval;
    char characters;
    char* str;
} Value;

typedef struct {
    DataTypes_t type;
    Value val;
} TypedValue;
typedef struct {
    char *name;
    TypedValue typedval;
    UT_hash_handle hh;
} VarEntry;

typedef struct ASTNode {
    ASTKind_t kind;
    DataTypes_t datatype;
    int line, col;

    union {
        char *var;
        struct {
            char *raw;     // e.g. "123", "3.14", "true", "hello"
        } literal;
        struct {
            OP_kind_t op;
            struct ASTNode *left, *right;
        } bin;

        struct {
            OP_kind_t op;
            struct ASTNode *operand;
        } unop;

        struct {
            struct ASTNode *lhs, *rhs;
            OP_kind_t op;
        } assign;

        struct {
            struct ASTNode *a, *b;
        } seq;

        struct {
            struct ASTNode *cond, *then_branch, *else_branch;
        } ifnode;

        struct {
            struct ASTNode *init, *end, *step, *body;
        } fornode;
    };
} ASTNode_t;

/* Constructors */
ASTNode_t *new_num(char *rawval, DataTypes_t datatype, int line, int col);
ASTNode_t *new_str(char *rawval, int line, int col);
ASTNode_t *new_var(const char *name, DataTypes_t datatype, int line, int col);
ASTNode_t *new_binop(ASTNode_t *l, ASTNode_t *r, int line, int col, OP_kind_t op);
ASTNode_t *new_unop(ASTNode_t *e, int line, int col, OP_kind_t op);
ASTNode_t *new_assign(ASTNode_t *lhs, ASTNode_t *rhs, DataTypes_t datatype, int line, int col,OP_kind_t op);
ASTNode_t *new_if(ASTNode_t *cond, ASTNode_t *thenB, ASTNode_t *elseB, int line, int col);
ASTNode_t *new_for(ASTNode_t *init, ASTNode_t *end, ASTNode_t *step, ASTNode_t *body, int line, int col);
ASTNode_t *new_seq(ASTNode_t *a, ASTNode_t *b);

/* Eval + memory */
void ast_free(ASTNode_t *n);
ASTNode_t *ast_alloc(void);

/* Env */
void set_var(const char *name, Value *val, DataTypes_t datatype);
Value getvar(const char *name, DataTypes_t datatype, int line, int col);
void assign_value(DataTypes_t datatype, Value *dest, Value src);
Value eval_assign(ASTNode_t *lhs, ASTNode_t *rhs, OP_kind_t op, DataTypes_t datatypes , int line, int col);


#endif
