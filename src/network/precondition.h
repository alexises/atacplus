#ifndef PRECONDITION_H
#define PRECONDITION_H
#include <exception>

/**
 * PreconditionFailException : raised when a precondition is failed
 */
class PreconditionFailException : public std::exception
{
    public:
        const char * what () const throw ();
        PreconditionFailException(const char* str);
        ~PreconditionFailException();
    private:
        char* str;
};

#define precondition(attr) if (!(attr)) { throw PreconditionFailException("attr"); }

#endif
