%{
 /* Declarations section */
#include "tokens.hpp"
#include <stdio.h>
%}

%option yylineno
%option noyywrap
digit ([0-9])
letter ([a-zA-Z])
whitespace ([\t\n ])
ascii (\x([2-6][0-9a-fA-F]|7[0-9a-eA-E]|09))
escape (\\(\\|n|\"|r|t|0))

%%
void                      return VOID;
int                      return INT;
byte                      return BYTE;
b                      return B;
bool                      return BOOL;
and                      return AND;
or                      return OR;
not                      return NOT;
true                      return TRUE;
false                      return FALSE;
return                      return RETURN;
if                      return IF;
else                      return ELSE;
while                      return WHILE;
break                      return BREAK;
continue                      return CONTINUE;
";"                                              return SC;
","                                              return COMMA;
"("                                              return LPAREN;
")"                                              return RPAREN;
"{"                                              return LBRACE;
"}"                                              return RBRACE;
"="                                           return ASSIGN;
"=="|"!="|"<"|">"|"<="|">="                        return RELOP;
"+"|"-"|"*"|"/"                                       return BINOP;
"//"[^\r\n]*[\r\n]                                   return COMMENT;
{letter}+({digit}|{letter})*                         return ID;
0|[1-9]{digit}*                                         return NUM;
\"({letter}|{digit}|{ascii}|{escape})*\"                 return STRING;
{whitespace}                                  ;
.         printf("Lex doesn't know what that is!\n");
%%