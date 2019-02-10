#include "TacacsServer.h"
#include "TacacsServerThread.h"
#include <boost/thread/thread.hpp>

TacacsServer::TacacsServer(const char* host, int port)
{
    this->server = new TcpServer();
    this->server->listen(host, port);
}

void TacacsServer::listen()
{
    while (1)
    {
        BufferedTcpSocket* sock = this->server->accept();
        TacacsServerThread* serverThread = new TacacsServerThread(sock);
        boost::thread threadObj(*serverThread);
        threadObj.detach();
    }
}

TacacsServer::~TacacsServer()
{
    delete this->server;
}
