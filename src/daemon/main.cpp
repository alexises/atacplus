#include "Options.h"
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

    return 0;
}