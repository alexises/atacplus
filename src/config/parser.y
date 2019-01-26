%{
  #include <cstdio>
  #include <exception>
  #include "parser.h"
  #include "parser.hpp"
  #include "scanner.h"
  #include "ParserContext.h"
  #include "ConfigElementNotFoundException.h"
%}

%define parse.trace
%define api.pure full
%define api.value.type {union parser_data}
%start configFile
%lex-param { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { ParserContext* ctx }

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
  SERVER { ctx->setCtx(ctx->getServer()); } OPEN_BRACKET serverConfigBlock CLOSE_BRACKET
;

serverConfigBlock:
  configInstructions
;

configInstructions:
  configInstruction
| configInstruction configInstructions
;

configInstruction:
  CONFIG_NAME STRING SEMICOLUMN { 
    try
    {
        (*(ctx->getCtx()))[$1.char_val] = $2.char_val; 
        delete[] $1.char_val;
        delete[] $2.char_val;
    }
    catch (ConfigElementNotFoundException& e)
    {
        delete[] $1.char_val;
        delete[] $2.char_val;
        throw;
    }
  }
| CONFIG_NAME DIGIT SEMICOLUMN
;
  
