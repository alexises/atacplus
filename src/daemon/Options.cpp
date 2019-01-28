#include <iostream>
#include "Options.h"
#include "network/precondition.h"

namespace bo = boost::program_options;

Options::Options(int argc, char** argv) : 
    configFile("/etc/atacplus.conf"),
    options("Advenced Tacacs+ server")
{
    this->argc = argc;
    this->argv = argv;
    this->dryrun = false;
    this->foreground = false;
    this->dropPriv = false;
    this->help = false;
    this->valid = false;
    this->options.add_options()
      ("help,h", bo::bool_switch(&(this->help)),"print this usage message")
      ("config-file,f", bo::value(&(this->configFile)), "read configuration from file")
      ("foreground,d", bo::bool_switch(&(this->foreground)), "run service in foreground")
      ("test,t", bo::bool_switch(&(this->dryrun)), "test config file and exit")
      ("uid,u", bo::value(&(this->uid)), "launch with uid")
      ("gid,g", bo::value(&(this->gid)), "launch with gid");

}

void Options::parse()
{

    bo::variables_map vm;
    bo::store(parse_command_line(this->argc, this->argv, options), vm);
    if (vm.count("uid") != vm.count("gid"))
    {
        throw std::logic_error(std::string("Option uid and gid need to be set together"));
    }

    bo::notify(vm);
    this->valid = true;
}

bool Options::isValid()
{
    return this->valid;
}

bool Options::isHelp()
{
    precondition(this->isValid());
    return this->help;
}

void Options::usage()
{
    this->options.print(std::cout);
}
