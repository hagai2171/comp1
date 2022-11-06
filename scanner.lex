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

%x QUOTE
%x COMM

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
"//"                                              BEGIN(COMM);
<COMM>[^\r\n]*                                  return COMMENT;
<COMM>[\r\n]                                        BEGIN(INITIAL);
{letter}+({digit}|{letter})*                         return ID;
0|[1-9]{digit}*                                                        return NUM;
\"                                                                        BEGIN(QUOTE);
<QUOTE>({letter}|{digit}|{ascii}|{escape}|{whitespace})*                 return STRING;
<QUOTE>\"                                                             BEGIN(INITIAL);
{whitespace}                                  ;
.         printf("Lex doesn't know what that is!\n");
%%