/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_PARSER_H_INCLUDED
# define YY_YY_SRC_PARSER_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser/parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include "../utils/token_printer.h"
    #include "../ast/ASTNode.h"
    extern ASTNode_t *root;

#line 57 "src/parser/parser.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    NUMBER = 259,                  /* NUMBER  */
    STRING_LITERAL = 260,          /* STRING_LITERAL  */
    PLUS = 261,                    /* PLUS  */
    MINUS = 262,                   /* MINUS  */
    STAR = 263,                    /* STAR  */
    SLASH = 264,                   /* SLASH  */
    MOD = 265,                     /* MOD  */
    POWER = 266,                   /* POWER  */
    INC = 267,                     /* INC  */
    DEC = 268,                     /* DEC  */
    LSHIFT = 269,                  /* LSHIFT  */
    RSHIFT = 270,                  /* RSHIFT  */
    BITAND = 271,                  /* BITAND  */
    BITOR = 272,                   /* BITOR  */
    BITXOR = 273,                  /* BITXOR  */
    BITNOT = 274,                  /* BITNOT  */
    LPAREN = 275,                  /* LPAREN  */
    RPAREN = 276,                  /* RPAREN  */
    LBRACE = 277,                  /* LBRACE  */
    RBRACE = 278,                  /* RBRACE  */
    SEMICOLON = 279,               /* SEMICOLON  */
    ASSIGN = 280,                  /* ASSIGN  */
    PLUS_ASSIGN = 281,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 282,            /* MINUS_ASSIGN  */
    STAR_ASSIGN = 283,             /* STAR_ASSIGN  */
    SLASH_ASSIGN = 284,            /* SLASH_ASSIGN  */
    MOD_ASSIGN = 285,              /* MOD_ASSIGN  */
    POWER_ASSIGN = 286,            /* POWER_ASSIGN  */
    LSHIFT_ASSIGN = 287,           /* LSHIFT_ASSIGN  */
    RSHIFT_ASSIGN = 288,           /* RSHIFT_ASSIGN  */
    AND = 289,                     /* AND  */
    OR = 290,                      /* OR  */
    NOT = 291,                     /* NOT  */
    EQ = 292,                      /* EQ  */
    NEQ = 293,                     /* NEQ  */
    LT = 294,                      /* LT  */
    LE = 295,                      /* LE  */
    GT = 296,                      /* GT  */
    GE = 297,                      /* GE  */
    IF = 298,                      /* IF  */
    ELSE = 299,                    /* ELSE  */
    DATATYPES = 300,               /* DATATYPES  */
    UPLUS = 301,                   /* UPLUS  */
    UMINUS = 302,                  /* UMINUS  */
    POSTFIX = 303,                 /* POSTFIX  */
    LOWER_THAN_ELSE = 304          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "src/parser/parser.y"

    ASTNode_t *node;
    DataTypes_t datatype;

#line 128 "src/parser/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_PARSER_H_INCLUDED  */
