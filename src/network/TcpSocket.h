#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "Buffer.h"
#include "FixedLengthString.h"

/**
 * represent a tcp socket
 */
class TcpSocket
{
    public:
        TcpSocket();
        ~TcpSocket();
        /**
         * set the associated buffer with 
         *
         * the user of this class is responsible of maintening the
         * integrity of the buffer durring the life of Socket
         *
         * the client is also responsible of deleting the buffer after
         * the proper use
         *
         * @param[in] rbuff reading buffer
         * @param[in] wbuff writting buffer
         * @pre rbuff != NULL && wbuff != NULL
         */
        void setBuffer(Buffer* rbuff, Buffer* wbuff);
        /**
         * check is socket is ready for reading or writting
         *
         * this include :
         *      socket is not EOF
         *      socket is properly bind
         *      socket is properly callected fromm recv/sendto
         *
         * @return true is socket is ready to read/write
         *         false otherwise
         */
        bool isUsable();
        /**
         * processBytes : fetch and push bytes to the socket buffer
         *
         * we try to flush writing buffer and fill input buffer.
         * @param[in] rblocking set the blocking state for filling the input buffer
         * @param[in] wblocking set the blocking state for filling the output buffer
         * @pre rbuff != NULL && wbuff != NULL
         * @pre isUsable == true;
         */
        void processBytes(bool rblocking, bool wblocking);
        /**
         * read : read some byte from the network and fill the buffer
         *
         * @param[in] rblocking set the blocking state for filling the input buffer
         * @pre rbuff != NULL && wbuff != NULL
         * @pre isUsable == true;
         */
        void read(bool rblocking);
        /**
         * write : write some byte from the network and fill the buffer
         *
         * @param[in] wblocking set the blocking state for filling the input buffer
         * @pre rbuff != NULL && wbuff != NULL
         * @pre isUsable == true;
         */
        void write(bool wblocking);
    protected:
        /**
         * this function is used on child class for creating the corresponding
         * object after accepting a client
         */
        TcpSocket(int socket);
        bool usable;
        int socket;
        uint32_t remoteAddr;
        FixedLengthString* remoteFqdn;
        uint16_t remotePort;
    private:
        Buffer* rbuff; // this buffer contain bytes in waiting for client read
        Buffer* wbuff; // this buffer contain bytes in waiting for send to the network
};
#endif
