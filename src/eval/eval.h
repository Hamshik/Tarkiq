#include "math.h"
/* ---------- common helpers ---------- */
#define DIE(msg) do { fprintf(stderr, "%s\n", (msg)); exit(EXIT_FAILURE); } while (0)

#define CHECK_INT_ZERO(op, b) \
    do { \
        if (((op) == OP_DIV || (op) == OP_MOD) && (b) == 0) DIE("division/mod by zero"); \
    } while (0)

#define INT_CASES(field, a, b) \
    case OP_ADD: return (Value){ .field = (a) + (b) }; \
    case OP_SUB: return (Value){ .field = (a) - (b) }; \
    case OP_MUL: return (Value){ .field = (a) * (b) }; \
    case OP_DIV: return (Value){ .field = (a) / (b) }; \
    case OP_MOD: return (Value){ .field = (a) % (b) }; \
    case OP_POW: return (Value){ .field = pow(a,b) };  \
    case OP_LSHIFT: return (Value){ .field = (a) << (b) }; \
    case OP_RSHIFT: return (Value){ .field = (a) >> (b) }; \
    case OP_BITAND: return (Value){ .field = (a) & (b) }; \
    case OP_BITOR:  return (Value){ .field = (a) | (b) }; \
    case OP_BITXOR: return (Value){ .field = (a) ^ (b) };    \
    case OP_EQ: return (Value){.field = (a) == (b)};\
    case OP_NEQ: return (Value){.field = (a) != (b)};\
    case OP_GT: return (Value){.field = (a) > (b)};\
    case OP_LT: return (Value){.field = (a) < (b)};\
    case OP_GE: return (Value){.field = (a) >= (b)};\
    case OP_LE: return (Value){.field = (a) <= (b)};

#define FP_CASES(field, a, b, POWF, MODF) \
    case OP_ADD: return (Value){ .field = (a) + (b) }; \
    case OP_SUB: return (Value){ .field = (a) - (b) }; \
    case OP_MUL: return (Value){ .field = (a) * (b) }; \
    case OP_DIV: return (Value){ .field = (a) / (b) }; \
    case OP_POW: return (Value){ .field = POWF((a), (b)) }; \
    case OP_MOD: return (Value){ .field = MODF((a), (b)) }; \
    case OP_EQ: return (Value){.field = (a) == (b)};\
    case OP_NEQ: return (Value){.field = (a) != (b)};\
    case OP_GT: return (Value){.field = (a) > (b)};\
    case OP_LT: return (Value){.field = (a) < (b)};\
    case OP_GE: return (Value){.field = (a) >= (b)};\
    case OP_LE: return (Value){.field = (a) <= (b)};


#ifndef EVAL_H
#define EVAL_H
#include "../ast/ASTNode.h"


Value ast_eval(ASTNode_t *node);
char* do_operation_str(const char* a, const char* b, OP_kind_t op);
Value eval_bool(OP_kind_t op, bool a, bool b);
void do_unop_operation(Value *result, Value *operand,DataTypes_t datatype,OP_kind_t op);
Value eval_binop_double(OP_kind_t op, double a, double b);
Value eval_binop_float(OP_kind_t op, float a, float b);
Value eval_binop_int(OP_kind_t op, bool isShort, int a, int b);
OP_kind_t get_assign_op(OP_kind_t op);

#endif