#ifndef PARSERCONTEXT_H
#define PARSERCONTEXT_H
#include "ServerConfigSection.h"
#include <string>
#include <iostream>

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
    /**
     * parse the configuration file/buffer provided on argument and 
     * populate this context object
     *
     * this method could throw exception in case of bad configuration
     */
    void parse(std::string& filename);
    void parse(std::iostream& buffer);

  private:
    ServerConfigSection* server;
    ConfigSection* current_ctx;
};

#endif
