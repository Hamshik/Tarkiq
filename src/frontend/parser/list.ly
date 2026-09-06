list_stmt:
    LSQUARE opt_args RSQUARE    { $$ = new_list($2, @1); }
;

indexing:
    LSQUARE expr RSQUARE
    {
        idx_expr_t* idx_node = (idx_expr_t*)malloc(sizeof(idx_expr_t));
        idx_node->expr_node = $2;
        idx_node->depth = 1;
        idx_node->next = NULL;
        $$ = idx_node;
    }
    | indexing LSQUARE expr RSQUARE
    {
        idx_expr_t* idx_node = (idx_expr_t*)malloc(sizeof(idx_expr_t));
        idx_node->expr_node = $3;
        idx_node->depth = $1->depth + 1;
        idx_node->next = $1; 
        $$ = idx_node;
    }
;

index_stmt:
    expr indexing 
    { 
        $$ = new_index($1, $2, false, @1);
        $$->isglobal = $1->isglobal;
    }
;

opt_list_size:
    /* empty */                 { $$ = static_cast<size_t>(0); } 
    | SEMICOLON NUMBER          { $$ = (size_t)SA_parse_u128($2->literal.raw, NULL); }
;