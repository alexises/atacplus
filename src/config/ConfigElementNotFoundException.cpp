#include "ConfigElementNotFoundException.h"
#include <cstring>

const char * ConfigElementNotFoundException::what () const throw ()
{
    return this->str;
}

ConfigElementNotFoundException::ConfigElementNotFoundException(const char* str)
{
    this->str = new char[strlen(str) + 1];
    strcpy(this->str, str);
}

ConfigElementNotFoundException::~ConfigElementNotFoundException() throw()
{
    delete[] this->str;
}
