%{
  #include <stdio.h>
  #include "parser.h"
  #include "parser.hpp"
  #include "scanner.h"
%}

%define api.pure full
%define api.value.type {union parser_data}
%start configFile
%param { parser_context* ctx }

%token OPEN_BRACKET
%token CLOSE_BRACKET
%token SEMICOLUMN
%token STRING
%token DIGIT
%token SERVER
%token CONFIG_NAME

%%

configFile:
  configSections
;

configSections:
  configSection
| configSection configSections
;

configSection: 
  serverConfigSection
;

serverConfigSection:
  SERVER { ctx->current = ctx->server; } OPEN_BRACKET serverConfigBlock CLOSE_BRACKET
;

serverConfigBlock:
  configInstructions
;

configInstructions:
  configInstruction
| configInstruction configInstructions
;

configInstruction:
  CONFIG_NAME STRING SEMICOLUMN { (*(ctx->current))[$1.char_val] = $2.char_val;}
| CONFIG_NAME DIGIT SEMICOLUMN
;
  
