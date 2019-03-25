#include "BufferExaustionException.h"
#include <sstream>
#include "precondition.h"

BufferExaustionException::BufferExaustionException(int condition, int nbytes)
{
    precondition(condition == BufferExaustionCondition::Underflow ||
                 condition == BufferExaustionCondition::Overflow);
    this->condition = condition;
    this->size = nbytes;
    std::stringstream s;
    if (condition == BufferExaustionCondition::Underflow)
    {
        s << "too fiew bytes on buffer (" << nbytes << " more bytes needed)";
    }
    else
    {
        s << "too many bytes on buffer (" << nbytes << " bytes are in excess)";
    }
    this->str = new std::string(s.str());
}

const char * BufferExaustionException::what () const throw ()
{
    return this->str->c_str();
}

BufferExaustionException::~BufferExaustionException() throw()
{
    delete this->str;
}

int BufferExaustionException::getCondition()
{
    return this->condition;
}

int BufferExaustionException::getSize()
{
    return this->size;
}
