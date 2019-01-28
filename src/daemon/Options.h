#ifndef OPTIONS_H
#define OPTIONS_H
#include <boost/program_options.hpp>
#include <string>

class Options
{
    public:
        Options(int argc, char** argv);
        /**
         * parse: parse option from command line provided on construction
         *
         * @throw logic_error when args are invalid;
         */
        void parse();
        /**
         * isValid : check if object is ready to be used by app
         *
         * @return true if object is properly initialized
         *         false otherwise
         */
        bool isValid();
        /**
         * isHelp: check if help option is passed
         *
         * @return true if help option was passed to commend line
         *         false otherwise
         * @pre isValid() == true;
         *
         */
        bool isHelp();
        /**
         * usage : print usage message
         */
        void usage();

    private:
        std::string configFile;
        bool dryrun;
        bool foreground;
        bool dropPriv;
        bool help;
        bool valid;
        std::string uid;
        std::string gid;
        int argc;
        char** argv;
        boost::program_options::options_description options;
};

#endif
