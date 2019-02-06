#include "ParserContext.h"
#include "parser.h"
#include "parser.hpp"
#include "scanner.h"
#include <fstream>
#include <stdexcept>

ParserContext::ParserContext()
{
    this->current_ctx = NULL;
    this->server = new ServerConfigSection();
}

ParserContext::~ParserContext()
{
    delete this->server;
}

ServerConfigSection* ParserContext::getServer()
{
    return this->server;
}

ConfigSection*  ParserContext::getCtx()
{
    return this->current_ctx;
}

void ParserContext::setCtx(ConfigSection* ctx)
{
    this->current_ctx = ctx;
}

void ParserContext::parse(std::string& filename)
{
    std::fstream file;
    file.open(filename.c_str(), std::ios_base::in);
    if (!file.is_open())
    {
       throw std::runtime_error("can't open " + filename + " for reading");
    }
    this->parse(file);
}

void ParserContext::parse(std::iostream& buffer)
{
    yyscan_t ctx;
    yylex_init_extra(&buffer, &ctx);
    yyparse(ctx, this);
    yylex_destroy(ctx);
}
