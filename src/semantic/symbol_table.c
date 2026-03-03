#include "../ast/ASTNode.h"
#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include <stdbool.h>
#include "../utils/uhash.h"
Symboltable_t *envs = NULL;

DataTypes_t lookup(const char* name){
    Symboltable_t *v;
    HASH_FIND_STR(envs, name, v);
    if (v != NULL) return v->type;
    printf("Warning: in func lookup the dataype of var %s is UNKNOWN\n", name); 
    return UNKNOWN;
}

exitcode_t exists(const char *name, DataTypes_t type) {
	Symboltable_t *v;
    HASH_FIND_STR(envs, name, v);
    if (v == NULL) return NOT_DECLARED;
    if (v->type != type) return TYPE_MISMATCH;
    return SUCCESS;
}

bool declare(const char* name, DataTypes_t type){
    Symboltable_t *v;
    HASH_FIND_STR(envs, name, v);
    if (v != NULL) return false;
    else {
        v = malloc(sizeof(*v));
        v->name = strdup(name);
        v->type = type;
        HASH_ADD_KEYPTR(hh, envs, v->name, strlen(v->name), v);
        return true;
    }
}

exitcode_t assign_check(const char* name, DataTypes_t rhs_t){
    Symboltable_t *v;
    HASH_FIND_STR(envs, name, v);
    if(v == NULL) return NOT_DECLARED;
    if(v->type != rhs_t) return TYPE_MISMATCH;
    return SUCCESS;
}