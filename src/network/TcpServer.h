#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <stdint.h>
#include "TcpSocket.h"
#include "BufferedTcpSocket.h"

class TcpServer : public TcpSocket
{
    public:
        TcpServer();
        /**
         * start listening
         *
         * @param[in] addr address to listen
         * @param[in] port port to listen
         * @return noting, but set usability by setting the setUsable to
         *   true
         */
        void listen(char* addr, uint16_t port);
        /**
         * accept new connection
         * 
         * @pre isUsable()
         * @return new socket if succes, NULL otherwise
         */
        BufferedTcpSocket* accept();
};


#endif
