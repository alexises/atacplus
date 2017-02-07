#ifndef ENCODINGEXCEPTION_H
#define ENCODINGEXCEPTION_H
#include <exception>

/**
 * EncodingException : raised when an encoding error occure
 */
class EncodingException : public std::exception
{
	public:
		const char * what () const throw ();
		EncodingException(const char* str);
		~EncodingException();
	private:
		char* str;
};

#endif
