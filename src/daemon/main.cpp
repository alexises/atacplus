#include "Options.h"
#include "daemonize.h"
#include "ParserContext.h"
#include "TacacsServer.h"
#include "log.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

BOOST_LOG_ATTRIBUTE_KEYWORD(Line, "Line", int)
BOOST_LOG_ATTRIBUTE_KEYWORD(File, "File", std::string)

void setupLogging(ParserContext& opt)
{
    boost::log::core::get()->add_global_attribute("Line", boost::log::attributes::mutable_constant<int>(5));
    boost::log::core::get()->add_global_attribute("File", boost::log::attributes::mutable_constant<std::string>(""));
    boost::log::add_common_attributes();

    std::string filename = opt.getServer()["logfile"].get(); 
    if (filename != "")
    {
        boost::log::add_file_log(
            boost::log::keywords::file_name = filename,
            boost::log::keywords::format = "[%TimeStamp%][%File%:%Line%] %Severity%: %Message%"
        );
    }
    else
    {
        boost::log::add_console_log(
            std::clog,
            boost::log::keywords::format = "[%TimeStamp%][%File:Line%] %Severity%: %Message%"
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
        LOG_MSG(info) << "dryrun, exiting";
        return 0;
    }
    if (!opt.isForeground())
    {
        daemonize(opt.getUid(), opt.getGid());
    }
    LOG_MSG(info) << "initialization done, starting event loop";
    TacacsServer srv(ctx.getServer()["listen"].get().c_str(),
                     atoi(ctx.getServer()["port"].get().c_str()));
    srv.listen();
    return 0;
}
