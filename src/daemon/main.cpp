#include "Options.h"
#include "daemonize.h"
#include "ParserContext.h"
#include "TacacsServer.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>


void setupLogging(ParserContext& opt)
{
    std::string filename = opt.getServer()["logfile"].get(); 
    if (filename != "")
    {
        boost::log::add_file_log(
            boost::log::keywords::file_name = filename,
            boost::log::keywords::format = "[%TimeStamp%][%ThreadID%] %Severity%: %Message%"
        );
    }
    else
    {
        boost::log::add_console_log(
            std::clog,
            boost::log::keywords::format = "[%TimeStamp%][%ThreadID%] %Severity%: %Message%"
        );
    }
}

int main(int argc, char** argv)
{
    BOOST_LOG_TRIVIAL(info) << "start application";
    Options opt(argc, argv);
    try
    {
        opt.parse();
    }
    catch (std::logic_error &e)
    {
        std::cerr << e.what() << std::endl;
        BOOST_LOG_TRIVIAL(fatal) << e.what();
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
        BOOST_LOG_TRIVIAL(debug) << "parse config " << filename;
        ctx.parse(filename);
    }
    catch (std::runtime_error &e)
    {
        BOOST_LOG_TRIVIAL(fatal) << "can't parse config : " << e.what();
        std::cerr << e.what() << std::endl;
        opt.usage();
        return 1;
    }
    setupLogging(ctx);
    if (opt.isDryrun())
    {
        BOOST_LOG_TRIVIAL(info) << "dryrun, exiting";
        return 0;
    }
    if (!opt.isForeground())
    {
        daemonize(opt.getUid(), opt.getGid());
    }
    BOOST_LOG_TRIVIAL(info) << "initialization done, starting event loop";
    TacacsServer srv(ctx.getServer()["listen"].get().c_str(),
                     atoi(ctx.getServer()["port"].get().c_str()));
    return 0;
}
