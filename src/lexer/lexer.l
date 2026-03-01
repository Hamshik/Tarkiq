%option noyywrap
%option bison-bridge
%option bison-locations
%{
#include "../parser/parser.h"
#include "../ast/ASTNode.h"
#define YY_DECL int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param)
%}

%%
"//".*               { /* skip single-line comments */ }
"/*"([^*]|\*+[^*/])*\*+"/"   { /* skip multi-line comments */ }
\"([^"\\\n]|\\.)*\" {yylval->node = new_str(yytext, yylloc->first_line, yylloc->first_column); return STRING_LITERAL;}  
[ \t\r\n]+          { /* skip */ }
if                  { return IF; }
else                { return ELSE; }
int                 { yylval->datatype = INT; return DATATYPES; }
short               { yylval->datatype = SHORT; return DATATYPES; }
float               { yylval->datatype = FLOAT; return DATATYPES; }
double              { yylval->datatype = DOUBLE; return DATATYPES; }
string              { yylval->datatype = STRINGS; return DATATYPES; }
[0-9]+(\.[0-9]+)? {
    yylval->node = new_num(yytext, UNKNOWN, yylloc->first_line, yylloc->first_column);
    return NUMBER;
}
"++"                { return INC; }
"--"                { return DEC; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return STAR; }
"/"                 { return SLASH; }
"%"                 { return MOD; }
"**"                { return POWER; }
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
"&"                 { return BITAND; }
"|"                 { return BITOR; }
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
