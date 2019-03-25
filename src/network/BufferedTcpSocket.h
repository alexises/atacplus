#ifndef BUFFEREDTCPSOCKET_H
#define BUFFEREDTCPSOCKET_H
#include "TcpSocket.h"

/**
 * represent a tcp socket with temporary buffer
 */
class BufferedTcpSocket : public TcpSocket
{
    public:
        BufferedTcpSocket(int socket);
        BufferedTcpSocket();
        ~BufferedTcpSocket();

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
         * processBytes : fetch and push bytes to the socket buffer
         *
         * we try to flush writing buffer and fill input buffer.
         * @param[in] rbytes minimum required reading bytes to sucess
         * @param[in] wbytes minimum required sending bytes to sucess
         *
         * to block for undefined amount of bytes, please set value to -1.
         * value of 0 perform a non blocking operation
         
         * @pre rbuff != NULL && wbuff != NULL
         * @pre isUsable == true;
         */
        void processBytes(int rbytes, int wbytes);
        /**
         * read : read some byte from the network and fill the buffer
         *
         * @param[in] rblocking set the blocking state for filling the input buffer
         * @pre rbuff != NULL && wbuff != NULL
         * @pre isUsable == true;
         * @return number of read bytes
         */
        int read(bool rblocking);

        /**
         * write : write some byte from the network and fill the buffer
         *
         * @param[in] wblocking set the blocking state for filling the input buffer
         * @pre rbuff != NULL && wbuff != NULL
         * @pre isUsable == true;
         * @return number of writed bytes
         */
        int write(bool wblocking);

    private:
        Buffer* rbuff; // this buffer contain bytes in waiting for client read
        Buffer* wbuff; // this buffer contain bytes in waiting for send to the network
};

#endif
