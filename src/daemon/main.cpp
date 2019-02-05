#include "Options.h"
#include "daemonize.h"
#include "ParserContext.h"
#include <iostream>

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
    }
    ParserContext ctx;
    std::string filename = opt.getConfigFilename();
    if (opt.isDryrun())
    {
        ctx.parse(filename);
        return 0;
    }
    else if (!opt.isForeground())
    {
        daemonize(opt.getUid(), opt.getGid());
    }
    return 0;
}
