%{
  #include <stdio.h>
  #include "parser.h"
%}

%define api.value.type {union parser_data}
%token OPEN_BRACKET
%token CLOSE_BRACKET
%token SEMICOLUMN
%token STRING
%token SERVER
%token CONFIG_NAME

%%

prog:
  %empty
