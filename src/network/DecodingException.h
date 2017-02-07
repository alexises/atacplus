#ifndef DECODINGEXCEPTION_H
#define DECODINGEXCEPTION_H
#include <exception>

/**
 * DecodingException : raised when an decoding error occure
 */
class DecodingException : public std::exception
{
	public:
		const char * what () const throw ();
		DecodingException(const char* str);
		~DecodingException();
	private:
		char* str;
};

#endif
