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
    AMP = 271,                     /* AMP  */
    PIPE = 272,                    /* PIPE  */
    BITXOR = 273,                  /* BITXOR  */
    BITNOT = 274,                  /* BITNOT  */
    LPAREN = 275,                  /* LPAREN  */
    RPAREN = 276,                  /* RPAREN  */
    LBRACE = 277,                  /* LBRACE  */
    RBRACE = 278,                  /* RBRACE  */
    SEMICOLON = 279,               /* SEMICOLON  */
    LSQUARE = 280,                 /* LSQUARE  */
    RSQUARE = 281,                 /* RSQUARE  */
    ASSIGN = 282,                  /* ASSIGN  */
    PLUS_ASSIGN = 283,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 284,            /* MINUS_ASSIGN  */
    STAR_ASSIGN = 285,             /* STAR_ASSIGN  */
    SLASH_ASSIGN = 286,            /* SLASH_ASSIGN  */
    MOD_ASSIGN = 287,              /* MOD_ASSIGN  */
    POWER_ASSIGN = 288,            /* POWER_ASSIGN  */
    LSHIFT_ASSIGN = 289,           /* LSHIFT_ASSIGN  */
    RSHIFT_ASSIGN = 290,           /* RSHIFT_ASSIGN  */
    COLON = 291,                   /* COLON  */
    AND = 292,                     /* AND  */
    OR = 293,                      /* OR  */
    NOT = 294,                     /* NOT  */
    EQ = 295,                      /* EQ  */
    NEQ = 296,                     /* NEQ  */
    LT = 297,                      /* LT  */
    LE = 298,                      /* LE  */
    GT = 299,                      /* GT  */
    GE = 300,                      /* GE  */
    IF = 301,                      /* IF  */
    ELSE = 302,                    /* ELSE  */
    FOR = 303,                     /* FOR  */
    LOOP = 304,                    /* LOOP  */
    DATATYPES = 305,               /* DATATYPES  */
    UPLUS = 306,                   /* UPLUS  */
    UMINUS = 307,                  /* UMINUS  */
    POSTFIX = 308,                 /* POSTFIX  */
    LOWER_THAN_ELSE = 309          /* LOWER_THAN_ELSE  */
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

#line 133 "src/parser/parser.h"

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
