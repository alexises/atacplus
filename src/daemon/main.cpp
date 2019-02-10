#include "Options.h"
#include "daemonize.h"
#include "ParserContext.h"
#include "TacacsServer.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main(int argc, char** argv)
{
    Options opt(argc, argv);
    try
    {
        opt.parse();
    }
    catch (std::logic_error &e)
    {
        std::cerr << e.what() << std::endl;
        opt.usage();
        return 1;
    }
    if (opt.isHelp())
    {
        opt.usage();
        return 0;
    }
    ParserContext ctx;
    std::string filename = opt.getConfigFilename();
    try 
    {
        ctx.parse(filename);
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        opt.usage();
        return 1;
    }
    if (opt.isDryrun())
    {
        return 0;
    }
    if (!opt.isForeground())
    {
        daemonize(opt.getUid(), opt.getGid());
    }
    TacacsServer srv((*(ctx.getServer()))["bind"].get().c_str(),
                     atoi((*(ctx.getServer()))["port"].get().c_str()));
    return 0;
}
