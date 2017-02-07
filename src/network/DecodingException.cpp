#include "DecodingException.h"
#include <cstring>

const char * DecodingException::what () const throw ()
{
	return this->str;
}

DecodingException::DecodingException(const char* str)
{
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
}

DecodingException::~DecodingException()
{
	delete this->str;
}
