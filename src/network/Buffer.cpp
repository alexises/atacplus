#include "Buffer.h"
#include "precondition.h"

/*
 * we define usefull macro for endianess
 */
#if ! defined(__BYTE_ORDER__)
#error "please use GCC to compil"
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BIG_ENDIAN
#endif

Buffer::Buffer(size_t size)
{
    this->size = size;
    this->readPos = 0;
    this->writePos = 0;
    this->buff = new uint8_t[this->size];
}

Buffer::~Buffer()
{
    delete[] this->buff;
}

size_t Buffer::availableRead()
{
    return this->writePos - this->readPos;
}

size_t Buffer::availableWrite()
{
    return this->size - this->availableRead();
}

size_t Buffer::getSize()
{
    return this->size;
}

void Buffer::write(uint8_t* buff, size_t size)
{
    precondition(size < this->availableWrite())
    for (size_t i = 0; i < size; ++i)
    {
        this->buff[this->writePos % this->size] = buff[i];
        ++this->writePos;
    }
}

uint8_t Buffer::pop()
{
    precondition(this->availableRead() > 0);
    register uint8_t r = this->buff[this->readPos % this->size];
    this->readPos++;
    return r;
}

void Buffer::operator>>(uint8_t &elem)
{
    precondition(this->availableRead() >= 1);
    elem = this->pop();
}

void Buffer::operator>>(uint16_t &elem)
{
    precondition(this->availableRead() >= 2);
    #ifndef BIG_ENDIAN
    elem = this->pop() +
           (this->pop() << 8);
    #else
    elem = (this->pop() << 8) +
           this->pop();
    #endif
}

void Buffer::operator>>(uint32_t &elem)
{
    precondition(this->availableRead() >= 4);
    #ifndef BIG_ENDIAN
    elem = this->pop() +
           (this->pop() << 8) +
           (this->pop() << 16) +
           (this->pop() << 24);
    #else
    elem = (this->pop() << 24) +
           (this->pop() << 16) +
           (this->pop() << 8) +
           this->pop();
    #endif
}
