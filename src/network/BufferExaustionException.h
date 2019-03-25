#ifndef BUFFEREXAUSTIONEXCEPTION_H
#define BUFFEREXAUSTIONEXCEPTION_H
#include <exception>
#include <string>
#include "enum.h"

struct BufferExaustionCondition 
{
    enum_mbr Underflow = 1;
    enum_mbr Overflow = 2;
};

/**
 * BufferExaustionException : raised when buffer is too full/empty
 */
class BufferExaustionException : public std::exception
{
    public:
        const char * what () const throw ();
        BufferExaustionException(int condition, int nbytes);
        ~BufferExaustionException() throw();

        /**
         * getCondition : get the condition that rised the exception
         *
         * @return one member oof BufferExaustionCondition;
         */
        int getCondition();

        /**
         * get sizee : get the number of byte in excess of in need for the
         * operation
         *
         * @return int size neede
         */
       int getSize(); 
    private:
       std::string* str;
       int condition;
       int size;
};

#endif
