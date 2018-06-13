#ifndef CONFIGELEMENTNOTFOUNDEXCEPTION_H
#define CONFIGELEMENTNOTFOUNDEXCEPTION_H
#include <exception>

/**
 * ConfigElementNotFoundException : raised when the parameter get is not found
 */
class ConfigElementNotFoundException : public std::exception
{
    public:
        const char * what () const throw ();
        ConfigElementNotFoundException(const char* str);
        ~ConfigElementNotFoundException() throw();
    private:
        char* str;
};

#endif
