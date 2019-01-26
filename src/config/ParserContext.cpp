#include "ParserContext.h"

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
