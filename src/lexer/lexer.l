%option noyywrap
%option bison-bridge
%option bison-locations
%option noinput
%option nounput

%{
    #include "../parser/parser.h"
#include "../ast/ASTNode.h"
#define YY_DECL int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param)
%}

%%
[ \t\r\n]+          { /* skip */ }
"//".*               { /* skip single-line comments */ }
"/*"([^*]|\*+[^*/])*\*+"/"   { /* skip multi-line comments */ }

\"([^"\\\n]|\\.)*\" {
    size_t n = yyleng;
    char *s = malloc(n - 1);          // remove 2 quotes + keep '\0'
    if (!s) exit(1);
    memcpy(s, yytext + 1, n - 2);
    s[n - 2] = '\0';

    yylval->node = new_str(s, yylloc->first_line, yylloc->first_column);
    free(s);
    return STRING_LITERAL;
}

if                  { return IF; }
else                { return ELSE; }
for                 { return FOR; }
loop                { return LOOP; }
int                 { yylval->datatype = INT; return DATATYPES; }
short               { yylval->datatype = SHORT; return DATATYPES; }
real32              { yylval->datatype = FLOAT; return DATATYPES; }
real64              { yylval->datatype = DOUBLE; return DATATYPES; }
str                 { yylval->datatype = STRINGS; return DATATYPES; }
char                { yylval->datatype = CHARACTER; return DATATYPES;}
logic               { yylval->datatype = BOOL; return DATATYPES;}
[0-9]+(\.[0-9]+)? {
    yylval->node = new_num(yytext, UNKNOWN, yylloc->first_line, yylloc->first_column);
    return NUMBER;
}
"++"                { return INC; }
"--"                { return DEC; }
":"                 { return COLON;}
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return STAR; }
"/"                 { return SLASH; }
"%"                 { return MOD; }
"**"                { return POWER; }
"["                 { return LSQUARE;}
"]"                 { return RSQUARE;}
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"="                 { return ASSIGN; }
"+="                { return PLUS_ASSIGN; }
"-="                { return MINUS_ASSIGN; }
"*="                { return STAR_ASSIGN; }
"/="                { return SLASH_ASSIGN; }
"%="                { return MOD_ASSIGN; }
"**="               { return POWER_ASSIGN; }
";"                 { return SEMICOLON; }
">>"                { return RSHIFT; }
"<<"                { return LSHIFT; }
"<<="               { return LSHIFT_ASSIGN; }
">>="               { return RSHIFT_ASSIGN; }
"&&"                { return AND; }
"||"                { return OR; }
"!"                 { return NOT; }
"&"                 { return AMP; }
"|"                 { return PIPE; }
"^"                 { return BITXOR; }
"~"                 { return BITNOT; }
"=="                { return EQ; }
"!="                { return NEQ; }
"<="                { return LE; }
">="                { return GE; }
"<"                 { return LT; }
">"                 { return GT; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
[a-zA-Z_][a-zA-Z0-9_]*|[a-zA-Z_] {
    yylval->node = new_var(yytext, UNKNOWN, yylloc->first_line, yylloc->first_column);
    return IDENTIFIER;
}
.                  { printf("Unknown char: %s\n", yytext); }
<<EOF>>             { return 0;  }
%%
