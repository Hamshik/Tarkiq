#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "ASTNode.h"

ASTNode_t* new_num(char *rawval, DataTypes_t datatype, int line, int col) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_NUM;
    node->datatype = datatype;
    node->line = line;
    node->col = col;
    node->literal.raw = strdup(rawval);   // copy value

    return node;
}

ASTNode_t *new_str(char *rawval, int line, int col)
{
    ASTNode_t *node = ast_alloc();
    node->kind = AST_STR;
    node->datatype = STRINGS;
    node->line = line;
    node->col = col;
    node->literal.raw = strdup(rawval);   // copy value
    return node;
}

ASTNode_t* new_var(const char *name, DataTypes_t datatype, int line, int col) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_VAR;
    node->var = strdup(name);
    node->datatype = datatype;
    node->line = line;
    node->col = col;
    return node;
}

ASTNode_t* new_unop(ASTNode_t *operand, int line, int col, OP_kind_t op) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_UNOP;
    node->unop.op = op;
    node->datatype = operand->datatype;
    node->unop.operand = operand;
    node->line = line;
    node->col = col;
    return node;
}

ASTNode_t* new_binop(ASTNode_t *left, ASTNode_t *right, int line, int col, OP_kind_t op) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_BINOP;
    node->datatype = UNKNOWN;
    node->bin.op = op;
    node->bin.left = left;
    node->bin.right = right;
    node->line = line;
    node->col = col;
    return node;
}

ASTNode_t* new_assign(ASTNode_t *lhs, ASTNode_t *rhs, DataTypes_t datatype, int line, int col,OP_kind_t op) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_ASSIGN;
    node->assign.op = op;
    node->assign.lhs = lhs;
    node->assign.rhs = rhs;
    node->datatype = datatype;
    node->line = line;
    node->col = col;
    return node;
}

ASTNode_t* new_seq(ASTNode_t *a, ASTNode_t *b) {
    ASTNode_t *node = ast_alloc();
    node->kind = AST_SEQ;
    node->seq.a = a;
    node->seq.b = b;
    return node;
}

ASTNode_t* new_if(ASTNode_t *cond, ASTNode_t *thenB, ASTNode_t *elseB, int line, int col) {
    ASTNode_t *node = ast_alloc();
    node->kind = NODE_IF;
    node->ifnode.cond = cond;
    node->ifnode.then_branch = thenB;
    node->ifnode.else_branch = elseB;
    node->line = line;
    node->col = col;
    return node;
}

ASTNode_t* new_for(ASTNode_t *init, ASTNode_t *end, ASTNode_t *step, ASTNode_t *body, int line, int col) {
    ASTNode_t *node = ast_alloc();
    node->kind = NODE_FOR;
    node->fornode.init = init;
    node->fornode.end = end;
    node->fornode.step = step;
    node->fornode.body = body;
    node->line = line;
    node->col = col;
    return node;
}
