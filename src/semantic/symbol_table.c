#include "../ast/ASTNode.h"
#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include <stdbool.h>
#include "../utils/uhash.h"
Symboltable_t *env = NULL;
DataTypes_t lookup(const char* name){
    Symboltable_t *v;
    HASH_FIND_STR(env, name, v);
    if (v != NULL) return v->type; 
    return UNKNOWN;
}

bool exists(const char *name) {
	Symboltable_t *v;
    HASH_FIND_STR(env, name, v);
    if (v == NULL) return false;
    return true;
}

bool declare(const char* name, DataTypes_t type){
    Symboltable_t *v;
    HASH_FIND_STR(env, name, v);
    if (v != NULL) return false;
    else {
        v = malloc(sizeof(*v));
        v->name = strdup(name);
        v->type = type;
        HASH_ADD_KEYPTR(hh, env, v->name, strlen(v->name), v);
    }
}

int assign_check(const char* name, DataTypes_t rhs_t){
    Symboltable_t *v;
    HASH_FIND_STR(env, name, v);
    if(v == NULL) return -1;
    if(v->type != rhs_t) return 0;
    return 1;
}