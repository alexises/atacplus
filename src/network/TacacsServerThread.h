#ifndef TACACSSERVERTHREAD_H
#define TACACSSERVERTHREAD_H
#include "BufferedTcpSocket.h"

class TacacsServerThread
{
    public:
        /**
         * initialize tread with the accepted socket
         *
         * @param[in] sock, accepted socket with listen
         */
        TacacsServerThread(BufferedTcpSocket* sock);
        ~TacacsServerThread();
        /**
         * main function that manage tacacs protocol state
         *
         * this function will be called with 
         */
        void operator()();
    private:
        BufferedTcpSocket* sock;

};

#endif 
