#ifndef BUFFER_H
#define BUFFER_H
#include <cstring>
#include <stdint.h>
#include "FixedLengthString.h"

class TcpSocket;

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
        /**
         * Construct a buffer of given size and populate it with data
         *
         * This class is usefull for unit testing
         *
         * @param[in] buffer buffer used to fill the Buffer instance
         * @param[in] buffsize size of the buffer
         * @param[in] size size of the resulting Buffer instance
         */
        Buffer(const uint8_t* buffer, size_t buffsize, size_t size=4096);
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
        void write(const uint8_t* buff, size_t size);
        /**
         * read byte from network to host
         */
        Buffer& operator>>(uint8_t &elem);
        Buffer& operator>>(uint16_t &elem);
        Buffer& operator>>(uint32_t &elem);
        Buffer& operator>>(FixedLengthString &elem);
        Buffer& operator>>(FixedLengthString *elem);
        /**
         * write byte from host to network
         */
        Buffer& operator<<(uint8_t elem);
        Buffer& operator<<(uint16_t elem);
        Buffer& operator<<(uint32_t elem);
        Buffer& operator<<(FixedLengthString &elem);
        Buffer& operator<<(FixedLengthString *elem);
        /**
         * undo the previously consummed offset byte
         *
         * this is usefull on error management, the biavior of this
         * method is only guarrented if no new data have been added
         * between the read and the offset shift
         *
         * @param[in] offset offset to move
         */
        void operator-=(size_t offset);
        /**
         * access a position and edit it, the position is relative to
         * the current read curso
         *
         * this function is mainly used for decoding/encoding in place.
         * @param[in] pos position to read
         * @return reference to the corresponding item
         * @pre pos < availableReadi()
         */
        uint8_t& operator[](size_t pos);
    private:
        /**
         * pop the next char from the buffer and upldate char position
         *
         * @pre this->availableRead() > 0
         * @return next readed byte
         */
        uint8_t pop();
        /**
         * push a char to the buffer and update char position
         *
         * @param[in] val value to insert
         * @pre this->availableWrite() > 0
         */
        void push(uint8_t val);
        uint8_t* buff;
        size_t size;
        size_t readPos;
        size_t writePos;
    friend class BufferedTcpSocket;
};
#endif
