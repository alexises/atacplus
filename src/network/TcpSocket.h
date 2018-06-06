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
};
#endif
