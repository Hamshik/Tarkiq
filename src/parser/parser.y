%code requires {
    #include <stdio.h>
    #include <stdlib.h>
    #include "../utils/token_printer.h"
    #include "../ast/ASTNode.h"
    extern ASTNode_t *root;
}

%{
    #include "../ast/ASTNode.h"
    ASTNode_t *root = NULL;
%}

%define api.pure full
%define parse.error verbose
%locations

%union {
    ASTNode_t *node;
    DataTypes_t datatype;
}

%code {
    int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);
    void yyerror(YYLTYPE *loc, const char *s);
    int yyparse(void);
}

%token <node> IDENTIFIER NUMBER STRING_LITERAL

%token PLUS MINUS STAR SLASH MOD POWER
%token INC DEC
%token LSHIFT RSHIFT
%token AMP PIPE BITXOR BITNOT
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON LSQUARE RSQUARE
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN MOD_ASSIGN POWER_ASSIGN
%token LSHIFT_ASSIGN RSHIFT_ASSIGN COLON
%token AND OR NOT EQ NEQ LT LE GT GE
%token IF ELSE FOR LOOP

%type <node> program stmt_list stmt block if_stmt for_stmt expr assignment
%token <datatype> DATATYPES

%right ASSIGN PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN MOD_ASSIGN POWER_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN
%left OR
%left AND
%left PIPE
%left BITXOR
%left AMP
%left EQ NEQ
%left LT LE GT GE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR SLASH MOD
%right POWER
%right UPLUS UMINUS NOT BITNOT
%left INC DEC
%precedence POSTFIX
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program
    : /* empty */               { root = NULL; }
    | stmt_list                 { root = $1; }
    ;

stmt_list
    : stmt                      { $$ = $1; }
    | stmt stmt_list            { $$ = new_seq($1, $2); }
    ;

stmt
    : expr SEMICOLON            { $$ = $1; }
    | if_stmt                   { $$ = $1; }
    | for_stmt                  { $$ = $1; }
    | block                     { $$ = $1; }
    ;

block
    : LBRACE stmt_list RBRACE   { $$ = $2; }
    ;

if_stmt
    : IF LBRACE expr RBRACE stmt %prec LOWER_THAN_ELSE
        { $$ = new_if($3, $5, NULL, @1.first_line, @1.first_column); }
    | IF LBRACE expr RBRACE stmt ELSE stmt
        { $$ = new_if($3, $5, $7, @1.first_line, @1.first_column); }
    ;

for_stmt
    : LOOP FOR LPAREN assignment COLON expr RPAREN stmt
        { $$ = new_for($4, $6, NULL, $8, @1.first_line, @1.first_column); }
    | LOOP FOR LPAREN assignment COLON expr COLON expr RPAREN stmt
        { $$ = new_for($4, $6, $8, $10, @1.first_line, @1.first_column); }
    ;

expr
    : NUMBER                    {$$ = $1;}
	| IDENTIFIER				{$$ = $1;}
    | STRING_LITERAL            {$$ = $1;}

    | expr PLUS expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_ADD); }
    | expr MINUS expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_SUB); }
    | expr STAR expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_MUL); }
    | expr SLASH expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_DIV); }
    | expr MOD expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_MOD); }
    | expr POWER expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_POW); }

    | expr LSHIFT expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LSHIFT); }
    | expr RSHIFT expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_RSHIFT); }

    | expr AMP expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITAND); }
    | expr BITXOR expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITXOR); }
    | expr PIPE expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITOR); }

    | expr AND expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_AND); }
    | expr OR expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_OR); }

    | expr EQ expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_EQ); }
    | expr NEQ expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_NEQ); }
    | expr LT expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LT); }
    | expr LE expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LE); }
    | expr GT expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_GT); }
    | expr GE expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_GE); }

    | PLUS expr %prec UPLUS     { $$ = new_unop($2, @$.first_line, @$.first_column, OP_POS); }
    | MINUS expr %prec UMINUS   { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NEG); }
    | NOT expr                  { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NOT); }
    | BITNOT expr               { $$ = new_unop($2, @$.first_line, @$.first_column, OP_BITNOT); }

    | IDENTIFIER INC %prec POSTFIX
                                { $$ = new_unop($1, @$.first_line, @$.first_column, OP_INC); }
    | IDENTIFIER DEC %prec POSTFIX
                                { $$ = new_unop($1, @$.first_line, @$.first_column, OP_DEC); }

    | LPAREN expr RPAREN         { $$ = $2; }
    | LBRACE expr RBRACE         { $$ = $2; }
    | LSQUARE expr RSQUARE     { $$ = $2; }
    | assignment                 {$$ = $1;}
    ;
 
assignment
    : IDENTIFIER COLON DATATYPES ASSIGN expr
        {
            if ($5->datatype == UNKNOWN)  $5->datatype = $3;
            $$ = new_assign($1, $5, $3, @$.first_line, @$.first_column, OP_ASSIGN);
        }

    | IDENTIFIER ASSIGN expr
        {
            $$ = new_assign($1, $3, $1->datatype, @$.first_line, @$.first_column, OP_ASSIGN);
        }

    | IDENTIFIER PLUS_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_PLUS_ASSIGN); }
    | IDENTIFIER MINUS_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MINUS_ASSIGN); }

    | IDENTIFIER STAR_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MUL_ASSIGN); }

    | IDENTIFIER SLASH_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_DIV_ASSIGN); }

    | IDENTIFIER MOD_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MOD_ASSIGN); }

    | IDENTIFIER LSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_LSHIFT_ASSIGN); }

    | IDENTIFIER RSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_RSHIFT_ASSIGN); }
    
    | IDENTIFIER POWER_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN , @$.first_line, @$.first_column, OP_POW_ASSIGN); }
    ;
%%

void yyerror(YYLTYPE *loc, const char *s) {
    fprintf(stderr, "Error at %d:%d: %s\n",
            loc->first_line, loc->first_column, s);
}
