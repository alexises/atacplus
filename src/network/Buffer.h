#ifndef BUFFER_H
#define BUFFER_H
#include <cstring>
#include <cstdint>

/**
 * Buffer : define a network buffer
 */
class Buffer
{
    public:
        /**
         * Construct a buffer of given size
         *
         * @param[in] size size of the buffer
         */
        Buffer(size_t size=4096);
        virtual ~Buffer();
        /**
         * avalableRead : get the available byte for reading in the buffer
         *
         * @return available byte for reading
         */
        size_t availableRead();
        /**
         * avalableWrite : get the available byte for writing in the buffer
         *
         * @return available byte for writing
         */
        size_t availableWrite();
        /**
         * getSize : get the size of the buffe
         * 
         * @return size of the buffer();
         */
        size_t getSize();
        /**
         * write : write inside the buffer
         *
         * @param[in] buffer when the data are located
         * @param[in] size size of the buffer
         * @pre size < this->availableWrite()
         */
        void write(uint8_t* buff, size_t size);
        /**
         * read byte from network to host
         */
        void operator>>(uint8_t &elem);
        void operator>>(uint16_t &elem);
        void operator>>(uint32_t &elem);
    private:
        /**
         * pop the next char from the buffer and upldate char position
         *
         * @pre this->availableRead() > 0
         * @return next readed byte
         */
        uint8_t pop();
        uint8_t* buff;
        size_t size;
        int readPos;
        int writePos;
};
#endif
