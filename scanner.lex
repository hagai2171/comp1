%{
 /* Declarations section */
#include "tokens.hpp"
#include <stdio.h>
int line;
%}

%option yylineno
%option noyywrap
digit ([0-9])
letter ([a-zA-Z])
whitespace ([\t\n ])
ascii (\x([2-6][0-9a-fA-F]|7[0-9a-eA-E]|09))
escape (\\(\\|n|\"|r|t|0))
signs ([\x20-\x21\x23-\x5B\x5D-\x7E])

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
"//"                                              {BEGIN(COMM); return COMMENT;}
<COMM>[^\r\n]*                                  ;
<COMM>(\r\n|\n|\r)                               BEGIN(INITIAL);
{letter}+({digit}|{letter})*                         return ID;
0|[1-9]{digit}*                                     return NUM;
\"                                              {line = yylineno; BEGIN(QUOTE);}
<QUOTE>([^\"\\]|(\\.))*(\")                    {if (line == yylineno) { BEGIN(INITIAL); return STRING;} else {printf ("Error unclosed string\n"); exit(0);}}
<QUOTE>.                    {printf ("Error unclosed string\n"); exit(0);}
{whitespace}                               ;
[\n\r]+       ;
.         {printf("Error %s\n", yytext); exit(0);}
%%