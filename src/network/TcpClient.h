#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include "TcpSocket.h"
#include "stdint.h"

class TcpClient : public TcpSocket
{
    public:
        TcpClient();
        /**
         * connect the socket to remote host
         *
         * @param[in] addr address to join, can be an host or an
         *   FQDN
         * @param[in] port port to connect
         * @return noting, but set usability by setting the setUsable to
         *   true
         */
        void connect(char* addr, uint16_t port);
};


#endif
