#include "precondition.h"
#include <cstring>

const char * PreconditionFailException::what () const throw ()
{
    return this->str;
}

PreconditionFailException::PreconditionFailException(const PreconditionFailException & other)
{
    this->str = new char[strlen(other.str) + 1];
    strcpy(this->str, other.str);
}

PreconditionFailException::PreconditionFailException(const char* str)
{
    this->str = new char[strlen(str) + 1];
    strcpy(this->str, str);
}

PreconditionFailException::~PreconditionFailException() throw()
{
    delete[] this->str;
}
