%{
#include <cstdlib>
#include "parser.h"
#include "parser.hpp"
#include <iostream>
int yycharpos = 1;

#define stepPos() yycharpos += yyleng
char* processStr(struct yyguts_t* yyg);

#define YY_INPUT(buf, result, max_size)  \
  result = 0; \
  while (1) { \
    int c = yyextra->get(); \
    if (yyextra->eof()) { \
      break; \
    } \
    buf[result++] = c; \
    if (result == max_size || c == '\n') { \
      break; \
    } \
  }

%}
%option noyywrap
%option reentrant
%option extra-type="std::iostream *"
%option bison-bridge

%%

\{                   { stepPos(); return OPEN_BRACKET; }
\}                   { stepPos(); return CLOSE_BRACKET; }
;                   { stepPos(); return SEMICOLUMN; }
server              { stepPos(); return SERVER; }
[a-z][a-z_-]+       { stepPos();
                      yylval->char_val = new char[yyleng + 1];
                      memcpy(yylval->char_val, yytext, yyleng);
                      yylval->char_val[yyleng] = '\0';
                      return CONFIG_NAME; }
[0-9]+              { stepPos(); 
                      yylval->int_val = strtol(yytext, NULL, 10);
                      return DIGIT;}
\"(\\.|[^"\\])*\"   { yylval->char_val = processStr(yyg);
                      return STRING; }
'(\\.|[^'\\])*'     { yylval->char_val = processStr(yyg);
                      return STRING; }
"[ \t]"             { stepPos(); }
\n                  { yylineno++; yycharpos=0;}

%%

char* processStr(struct yyguts_t* yyg)
{
     char* out = new char[yyleng - 1];
     int iOut = 0;
     int iIn = 1;
     while (iIn < (yyleng - 1) && iOut < (yyleng - 2))
     {
         if (yytext[iIn] != '\\')
         {
             out[iOut] = yytext[iIn];
             iIn++;
         }
         else if ((iIn + 1) < yyleng)
         {
             out[iOut] = yytext[iIn + 1];
             iIn += 2;
         }
         iOut++;
     }
     for (; iOut < (yyleng - 1); ++iOut)
     {
         out[iOut] = '\0';
     }
     stepPos();
     return out;
}
