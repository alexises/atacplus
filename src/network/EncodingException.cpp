#include "EncodingException.h"
#include <cstring>

const char * EncodingException::what () const throw ()
{
	return this->str;
}

EncodingException::EncodingException(const char* str)
{
	this->str = new char[strlen(str) + 1];
	strcpy(str, this->str);
}

EncodingException::~EncodingException()
{
	delete this->str;
}
