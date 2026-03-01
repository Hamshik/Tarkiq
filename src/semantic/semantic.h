#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ASTNode.h"
#include <stdbool.h>
typedef struct symboltable{
    DataTypes_t type;
    const char* name;
    UT_hash_handle hh;
}Symboltable_t;

void semantic_check(ASTNode_t *root);
DataTypes_t check_expr(ASTNode_t *n);
void type_error(ASTNode_t *n, const char *msg);
int is_numeric(DataTypes_t t);
DataTypes_t promote(DataTypes_t a, DataTypes_t b);

DataTypes_t lookup(const char* name);
bool declare(const char* name,DataTypes_t type);
bool exits(const char* name, DataTypes_t type);
bool assign_check(const char* name, DataTypes_t rhs_type);
void set_var(const char *name, DataTypes_t datatype);

#endif