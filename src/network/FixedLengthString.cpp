#include "FixedLengthString.h"
#include <cstring>
#include "precondition.h"

FixedLengthString::FixedLengthString(const char* value, uint8_t size)
{
    this->size = size;
    this->value = new char[size];
    memcpy(this->value, value, size);
}


FixedLengthString::FixedLengthString(uint8_t size)
{
    this->size = size;
    this->value = new char[size];
}

FixedLengthString::FixedLengthString(FixedLengthString & other)
{
    this->size = other.size;
    this->value = new char[other.size];
    memcpy(this->value, other.value, this->size);
}

FixedLengthString::~FixedLengthString()
{
    delete[] this->value;
}

const char* FixedLengthString::getString()
{
    return this->value;
}

uint8_t FixedLengthString::getSize()
{
    return this->size;
}

std::string FixedLengthString::toString()
{
    return std::string(this->value, this->size);
}

char& FixedLengthString::operator[](uint8_t pos)
{
    precondition(pos < this->size);
    return this->value[pos];
}

bool FixedLengthString::operator==(FixedLengthString& other)
{
    if (this->size != other.size)
    {
        return false;
    }
    for (uint8_t i = 0; i < this->size; ++i)
    {
        if (this->value[i] != other.value[i])
        {
            return false;
        }
    }
    return true;
}
