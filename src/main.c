#include <stdio.h>
#include "ast/ASTNode.h"
#include "parser/parser.h"
#include "semantic/semantic.h"
#include "eval/eval.h"

int main() {
    yyparse();
    if (root != NULL) {
        semantic_check(root);
        ast_eval(root);
    }
    return 0;
}