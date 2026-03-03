#include <stdio.h>
#include <stdlib.h>
#include "../ast/ASTNode.h"
#include "semantic.h"

static void force_numeric_type(ASTNode_t *n, DataTypes_t t) {
    if (!n || t == UNKNOWN) return;

    switch (n->kind) {
    case AST_NUM:
        if (n->datatype == UNKNOWN) n->datatype = t;
        break;
    case AST_UNOP:
        force_numeric_type(n->unop.operand, t);
        if (n->datatype == UNKNOWN) n->datatype = t;
        break;
    case AST_BINOP:
        force_numeric_type(n->bin.left, t);
        force_numeric_type(n->bin.right, t);
        if (n->datatype == UNKNOWN) n->datatype = t;
        break;
    default:
        break;
    }
}

void semantic_check(ASTNode_t *root) {
    if (!root) return;
    check_expr(root);
    printf("Test is passes!\n");
}

/* Helpers */
void type_error(ASTNode_t *n,const char* msg) {
    fprintf(stderr, "Error: %s\n\n", msg);
    n->datatype = UNKNOWN;
    exit(1);
}

int is_numeric(DataTypes_t t) {
    return t == INT || t == FLOAT || t == DOUBLE || t == SHORT;
}

DataTypes_t promote(DataTypes_t a, DataTypes_t b) {
    if (a == DOUBLE || b == DOUBLE) return DOUBLE;
    if (a == FLOAT  || b == FLOAT)  return FLOAT;
    if (a == INT    || b == INT)    return INT;
    return SHORT;
}

/* Main recursive checker */
DataTypes_t check_expr(ASTNode_t *n) {
    if (!n) return UNKNOWN;
    exitcode_t exit_code;

    switch (n->kind) {

    case AST_NUM:
        return n->datatype;

    case AST_STR:
        return STRINGS;

    case AST_VAR:
        exit_code = exists(n->var, n->datatype);
        switch (exit_code)
        {
        case NOT_DECLARED:
            fprintf(stderr, "Error: %s is not defined\n", n->var);
            exit(EXIT_FAILURE);
        case TYPE_MISMATCH:
            type_error(n, "Type Mismatch");
        default: break;
        }
        return n->datatype;

    case AST_BINOP: {
        DataTypes_t lt = check_expr(n->bin.left);
        DataTypes_t rt = check_expr(n->bin.right);

        /* string ops */
        if (lt == STRINGS || rt == STRINGS) {
            if (n->bin.op != OP_ADD || lt != STRINGS || rt != STRINGS) {
                type_error(n, "Only string + string is allowed");
            }
            n->datatype = STRINGS;
            return STRINGS;
        }

        /* numeric ops */
        if (!is_numeric(lt) || !is_numeric(rt)) {
            type_error(n, "Invalid operands for binary operator");
        }

        n->datatype = promote(lt, rt);
        return n->datatype;
    }

    case AST_UNOP: {
        DataTypes_t t = check_expr(n->unop.operand);

        if (n->unop.op == OP_NOT) {
            if (t != BOOL) type_error(n, "Operator ! expects bool");
            n->datatype = BOOL;
            return BOOL;
        }

        if (!is_numeric(t)) {
            type_error(n, "Unary operator requires numeric type");
        }

        n->datatype = t;
        return t;
    }

    case AST_ASSIGN: {
        if (n->assign.lhs->kind != AST_VAR) {
            type_error(n, "Left side of assignment must be a variable");
        }

        if (n->datatype != UNKNOWN && n->assign.lhs->datatype == UNKNOWN) {
            n->assign.lhs->datatype = n->datatype;
        }

        DataTypes_t lhs_t = n->assign.lhs->datatype;
        force_numeric_type(n->assign.rhs, lhs_t);
        DataTypes_t rhs_t = check_expr(n->assign.rhs);

        if (lhs_t != rhs_t) {
            type_error(n, "Type mismatch in assignment");
        }

        //if(!declare(n->assign.lhs->var, n->assign.lhs->datatype)) type_error(n, "Redeclaration of variable");
        printf("assign lhs=%d rhs=%d node=%d\n", lhs_t, rhs_t, n->datatype);
        n->datatype = lhs_t;
        return lhs_t;
    }

    case AST_SEQ:
        check_expr(n->seq.a);
        return check_expr(n->seq.b);

    case NODE_IF: {
        DataTypes_t ct = check_expr(n->ifnode.cond);
        if (ct != BOOL) type_error(n, "if condition must be boolean");

        check_expr(n->ifnode.then_branch);
        if (n->ifnode.else_branch)
            check_expr(n->ifnode.else_branch);

        return UNKNOWN;
    }

    default:
        type_error(n, "Unknown AST node in semantic analysis");
        return UNKNOWN;
    }
}
