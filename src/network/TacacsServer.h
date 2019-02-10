#ifndef TACACSSERVER_H
#define TACACSSERVER_H
#include "TcpServer.h"

class TacacsServer
{
    public:
        TacacsServer(const char* host, int port);
        ~TacacsServer();
        /**
         * listen : start event loop and accept connection
         */
        void listen();
    private:
        TcpServer* server;
};
#endif
