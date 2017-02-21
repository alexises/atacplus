#ifndef PRECONDITIONFAILEXCEPTION_H
#define PRECONDITIONFAILEXCEPTION_H
#include <exception>

/**
 * PreconditionFailException : raised when a precondition is failed
 */
class PreconditionFailException : public std::exception
{
    public:
        const char * what () const throw ();
        PreconditionFailException(const char* str);
	PreconditionFailException(const PreconditionFailException & other);
        ~PreconditionFailException();
    private:
        char* str;
};

#endif
