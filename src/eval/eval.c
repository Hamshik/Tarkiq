#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include "../ast/ASTNode.h"
#include "../utils/value_printer.h"
#include "eval.h"

OP_kind_t get_assign_op(OP_kind_t op) {
    switch (op) {
        case OP_ASSIGN: return OP_ASSIGN;
        case OP_PLUS_ASSIGN: return OP_ADD;
        case OP_MINUS_ASSIGN: return OP_SUB;
        case OP_MUL_ASSIGN: return OP_MUL;
        case OP_DIV_ASSIGN: return OP_DIV;
        case OP_MOD_ASSIGN: return OP_MOD;
        case OP_POW_ASSIGN: return OP_POW;
        case OP_LSHIFT_ASSIGN: return OP_LSHIFT;
        case OP_RSHIFT_ASSIGN: return OP_RSHIFT;
        default:
            fprintf(stderr, "Invalid assignment operator\n");
            exit(EXIT_FAILURE);
    }
}

Value eval_binop_int(OP_kind_t op, bool isShort, int a, int b) {
    if (isShort) {
        CHECK_INT_ZERO(op, b);
        switch (op) { INT_CASES(shnum, (short)a, (short)b); default: DIE("Invalid short binary op"); }
    }
    CHECK_INT_ZERO(op, b);
    switch (op) { INT_CASES(inum, a, b); default: DIE("Invalid int binary op"); }
}

Value eval_binop_float(OP_kind_t op, float a, float b) {
    if (op == OP_DIV && fabsf(b) < 1e-12f) DIE("division by zero");
    switch (op) { FP_CASES(fnum, a, b, powf, fmodf); default: DIE("Invalid float binary op"); }
}

Value eval_binop_double(OP_kind_t op, double a, double b) {
    if (op == OP_DIV && fabs(b) < 1e-12) DIE("division by zero");
    switch (op) { FP_CASES(lfnum, a, b, pow, fmod); default: DIE("Invalid double binary op"); }
}

bool isBoolOP(OP_kind_t op){
    switch (op)
    {
    case OP_AND:
    case OP_OR:
    case OP_EQ:
    case OP_NEQ:
    case OP_GT:
    case OP_LT:
    case OP_GE:
    case OP_LE:
        return true;
    default: return false;
    }
}

void do_unop_operation(Value *result, Value *operand,DataTypes_t datatype,OP_kind_t op) {
    
    switch (datatype)
    {
    case SHORT:
        switch (op) {
            case OP_NEG: result->shnum = -operand->shnum; break;
            case OP_POS: result->shnum = operand->shnum; break;
            case OP_BITNOT: result->shnum = ~((int)operand->shnum); break;
            case OP_INC: result->shnum = ((int)operand->shnum)+1; break;
            case OP_DEC: result->shnum = ((int)operand->shnum)-1; break;
            default:
                fprintf(stderr, "Invalid short unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case INT:
        switch (op) {
            case OP_NEG: result->inum = -operand->inum; break;
            case OP_POS: result->inum = operand->inum; break;
            case OP_BITNOT: result->inum = ~((int)operand->inum); break;
            case OP_INC: result->shnum = ((int)operand->shnum)+1; break;
            case OP_DEC: result->shnum = ((int)operand->shnum)-1; break;
            default:
                fprintf(stderr, "Invalid int unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case FLOAT:
        switch (op) {
            case OP_NEG: result->fnum = -operand->fnum; break;
            case OP_POS: result->fnum = operand->fnum; break;
            case OP_INC: result->shnum = ((int)operand->shnum)+1; break;
            case OP_DEC: result->shnum = ((int)operand->shnum)-1; break;
            default:
                fprintf(stderr, "Invalid float unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case DOUBLE:
        switch (op) {
            case OP_NEG: result->lfnum = -operand->lfnum; break;
            case OP_POS: result->lfnum = operand->lfnum; break;
            case OP_INC: result->shnum = ((int)operand->shnum)+1; break;
            case OP_DEC: result->shnum = ((int)operand->shnum)-1; break;
            default:
                fprintf(stderr, "Invalid double unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case BOOL:
        switch (op) {
            case OP_NOT: result->bval = !operand->bval; break;
            default:
                fprintf(stderr, "Invalid bool unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    default:
        fprintf(stderr, "Invalid datatype for unary operation\n");
        exit(EXIT_FAILURE);
    }
    printf("Result of unary operation: ");
    print_value(*result, datatype);
}

Value eval_bool(OP_kind_t op, DataTypes_t type, Value a, Value b) {
    switch(type) {
        case BOOL:
            switch (op) {
                case OP_AND: return (Value){.bval = a.bval && b.bval};
                case OP_OR:  return (Value){.bval = a.bval || b.bval};
                default: fprintf(stderr, "Invalid boolean operator\n"); exit(1); break;
            }
            break;
        case INT:
            switch (op){INT_CASES(inum, a.inum, b.inum); default: fprintf(stderr, "Invalid integer operator\n"); exit(1);}
            break;
        case SHORT:
            switch (op){INT_CASES(shnum, a.shnum, b.shnum); default: fprintf(stderr, "Invalid integer operator\n"); exit(1);}
            break;
        case FLOAT:
            switch (op){FP_CASES(fnum, a.fnum, b.fnum, powf, fmodf); default: fprintf(stderr, "Invalid float operator\n"); exit(1);}
            break;
        case DOUBLE:
            switch (op){FP_CASES(lfnum, a.lfnum, b.lfnum, pow, fmod); default: fprintf(stderr, "Invalid double operator\n"); exit(1);}
            break;
        default:
            fprintf(stderr, "Invalid datatype for boolean operation\n");
            exit(EXIT_FAILURE);
    }
}

char* do_operation_str(const char* a, const char* b, OP_kind_t op) {
    char *result = NULL;
    size_t size = strlen(a) + strlen(b) + 1;
    switch (op)
    {
    case OP_ADD:
        result = malloc(size);
        if(result == NULL) fprintf(stderr, "Memory allocation is failed for string catination");
        sprintf(result, "%s%s", a, b);  // automatically adds null terminator
        break;
    default:
        break;
    }
    return result;
}

static Value default_step(DataTypes_t type) {
    Value step = {0};
    switch (type) {
        case INT: step.inum = 1; break;
        case SHORT: step.shnum = 1; break;
        case FLOAT: step.fnum = 1.0f; break;
        case DOUBLE: step.lfnum = 1.0; break;
        default:
            fprintf(stderr, "for loop supports numeric init types only\n");
            exit(EXIT_FAILURE);
    }
    return step;
}

static int step_is_positive(DataTypes_t type, Value step) {
    switch (type) {
        case INT: return step.inum > 0;
        case SHORT: return step.shnum > 0;
        case FLOAT: return step.fnum > 0;
        case DOUBLE: return step.lfnum > 0;
        default: return 0;
    }
}

static int step_is_zero(DataTypes_t type, Value step) {
    switch (type) {
        case INT: return step.inum == 0;
        case SHORT: return step.shnum == 0;
        case FLOAT: return fabsf(step.fnum) < 1e-12f;
        case DOUBLE: return fabs(step.lfnum) < 1e-12;
        default: return 1;
    }
}

static int should_continue_for(DataTypes_t type, Value cur, Value end, Value step) {
    if (step_is_positive(type, step)) {
        switch (type) {
            case INT: return cur.inum < end.inum;
            case SHORT: return cur.shnum < end.shnum;
            case FLOAT: return cur.fnum < end.fnum;
            case DOUBLE: return cur.lfnum < end.lfnum;
            default: return 0;
        }
    }

    switch (type) {
        case INT: return cur.inum > end.inum;
        case SHORT: return cur.shnum > end.shnum;
        case FLOAT: return cur.fnum > end.fnum;
        case DOUBLE: return cur.lfnum > end.lfnum;
        default: return 0;
    }
}

static Value add_step_for(DataTypes_t type, Value cur, Value step) {
    Value next = cur;
    switch (type) {
        case INT: next.inum += step.inum; break;
        case SHORT: next.shnum += step.shnum; break;
        case FLOAT: next.fnum += step.fnum; break;
        case DOUBLE: next.lfnum += step.lfnum; break;
        default:
            fprintf(stderr, "for loop supports numeric init types only\n");
            exit(EXIT_FAILURE);
    }
    return next;
}

TypedValue ast_eval(ASTNode_t *node) {
    if (!node) return (TypedValue){0};
    TypedValue v = {0};

    switch (node->kind) {

    case AST_NUM:
        switch (node->datatype) {
            case INT:
                v.val.inum = (int)strtol(node->literal.raw, NULL, 10); break;
            case SHORT:
                v.val.shnum = (short)strtol(node->literal.raw, NULL, 10); break;
            case FLOAT:
                v.val.fnum = strtof(node->literal.raw, NULL); break;
            case DOUBLE:
                v.val.lfnum = strtod(node->literal.raw, NULL); break;
            default:
                fprintf(stderr, "Error: unsupported numeric literal type\n");
                exit(EXIT_FAILURE);
        }
        v.type = node->datatype;
        return v;

    case AST_STR:
        v.val.str = node->literal.raw;
        print_value(v.val, node->datatype);
        return v;

    case AST_CHAR:
        v.val.characters = node->literal.raw ? node->literal.raw[0] : '\0';
        print_value(v.val, node->datatype);
        return v;

    case AST_VAR: return (TypedValue){
        .type = node->datatype,
        .val = getvar(node->var, node->datatype, node->line, node->col)
    };

    case AST_BINOP: {
        TypedValue l = ast_eval(node->bin.left);
        TypedValue r = ast_eval(node->bin.right);
        v.type = node->datatype;

        switch (node->datatype) {
            case INT:
                v.val = eval_binop_int(node->bin.op, false, l.val.inum, r.val.inum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case FLOAT:
                v.val = eval_binop_float(node->bin.op, l.val.fnum, r.val.fnum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case DOUBLE:
                v.val = eval_binop_double(node->bin.op, l.val.lfnum, r.val.lfnum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case SHORT:
                v.val = eval_binop_int(node->bin.op, true, l.val.shnum, r.val.shnum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case STRINGS: v.val = (Value){.str = do_operation_str(l.val.str, r.val.str, node->bin.op)}; break;
            case BOOL: v.val = eval_bool(node->bin.op, l.type , l.val, r.val); break;
            default:
                fprintf(stderr, "Error: unsupported data type for binary Datatypes\n");
                exit(EXIT_FAILURE);
        }
        print_value(v.val, node->datatype);
        return v;
    }

    case AST_UNOP: {
        TypedValue r = ast_eval(node->unop.operand);
        do_unop_operation(&v.val, &r.val , node->datatype, node->unop.op);
        set_var(node->unop.operand->var, &v.val, node->datatype);
        return v;
    }

    case AST_ASSIGN: {
        Value val = eval_assign(node->assign.lhs,
                                node->assign.rhs,
                                node->assign.op,
                                node->datatype,
                                node->line,
                                node->col);
        return (TypedValue){.val = val, .type = node->datatype};
    }

    case AST_SEQ: {
        ast_eval(node->seq.a);
        return ast_eval(node->seq.b);
    }

    case NODE_IF:
        if (ast_eval(node->ifnode.cond).val.bval)
            return ast_eval(node->ifnode.then_branch);
        if (node->ifnode.else_branch)
            return ast_eval(node->ifnode.else_branch);
        return (TypedValue){0};

    case NODE_FOR: {
        if (!node->fornode.init || node->fornode.init->kind != AST_ASSIGN ||
            node->fornode.init->assign.lhs->kind != AST_VAR || node->fornode.init->assign.op != OP_ASSIGN) {
            fprintf(stderr, "Invalid for loop init\n");
            exit(EXIT_FAILURE);
        }

        ast_eval(node->fornode.init);
        DataTypes_t loop_type = node->fornode.init->datatype;
        const char *loop_name = node->fornode.init->assign.lhs->var;

        Value endv = ast_eval(node->fornode.end).val;
        Value stepv = node->fornode.step ? ast_eval(node->fornode.step).val : default_step(loop_type);

        if (step_is_zero(loop_type, stepv)) {
            fprintf(stderr, "for loop step cannot be zero\n");
            exit(EXIT_FAILURE);
        }

        TypedValue last = {0};
        
        while (should_continue_for(loop_type, getvar(loop_name, loop_type, node->line, node->col), endv, stepv)) {
            last = ast_eval(node->fornode.body);
            Value cur = getvar(loop_name, loop_type, node->line, node->col);
            Value next = add_step_for(loop_type, cur, stepv);
            set_var(loop_name, &next, loop_type);
        }

        print_value(last.val, last.type);
        return last;
    }

    default:
        fprintf(stderr, "Error: unknown AST node\n");
        exit(-1);
    }
}
