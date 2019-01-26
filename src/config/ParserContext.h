#ifndef PARSERCONTEXT_H
#define PARSERCONTEXT_H

#include "ServerConfigSection.h"

class ParserContext {
  public:
    ParserContext();
    ~ParserContext();
    /**
     * getServer : get server subconfig
     *
     * return server subconfig object
     */
    ServerConfigSection* getServer();
    /**
     * getCtx : get current parser context
     *
     * return one of the subconfig object depending on the last 
     *        call of setCtx
     */
    ConfigSection*  getCtx();
    /**
     * setCtx : set current parser ctx
     */
    void setCtx(ConfigSection* ctx);

  private:
    ServerConfigSection* server;
    ConfigSection* current_ctx;
};

#endif
