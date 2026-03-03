#include <stdlib.h>
#include <stdio.h>
#include "ASTNode.h"
#include "../eval/eval.h"
#include "../utils/value_printer.h"

void assign_value(DataTypes_t dt, Value *dst, Value src) {
    switch (dt) {
        case INT:    dst->inum = src.inum; break;
        case FLOAT:  dst->fnum = src.fnum; break;
        case DOUBLE: dst->lfnum = src.lfnum; break;
        case SHORT:  dst->shnum = src.shnum; break;
        case BOOL:   dst->bval = src.bval; break;
        case STRINGS:
            free(dst->str);
            dst->str = strdup(src.str);
            break;
        case CHARACTER:
            dst->characters = src.characters;
            break;
        default:
            fprintf(stderr, "Invalid assignment type\n");
            exit(1);
    }
}

Value eval_assign(ASTNode_t *lhs, ASTNode_t *rhs, OP_kind_t op, DataTypes_t datatypes , 
    int line, int col) {
    if (!lhs || lhs->kind != AST_VAR) {
        printf("Error [%d:%d]: assignment target must be a variable\n", line, col);
		exit(-1);
    }

    Value r = ast_eval(rhs);
    Value v = {0};

    if (op == OP_ASSIGN) {
        set_var(lhs->var, &r, datatypes);
        return r;
    }

    Value cur = getvar(lhs->var, datatypes, line, col);
    OP_kind_t operation = get_assign_op(op);
    switch (datatypes) {
        case INT:
            v = eval_binop_int(operation, false, cur.inum, r.inum);
            break;
        case FLOAT:
            v = eval_binop_float(operation, cur.fnum, r.fnum);
            break;
        case DOUBLE:
            v = eval_binop_double(operation, cur.lfnum, r.lfnum);
            break;
        case SHORT:
            v = eval_binop_int(operation, true, cur.shnum, r.shnum);
            break;
        case BOOL:
            v = eval_bool(operation, r.bval, cur.bval);
            break;
        case STRINGS:
            v = (Value){.str = do_operation_str(r.str, cur.str, operation)};
            break;
        case CHARACTER:
            v.characters = r.characters;
            break;
        default:
            fprintf(stderr, "Error: unsupported data type for assignment\n");
            exit(EXIT_FAILURE);
    }
    set_var(lhs->var, &v, datatypes);
    print_value(v, datatypes);
    return v;
}
