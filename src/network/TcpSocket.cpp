#include "TcpSocket.h"
#include "precondition.h"
#include "macro.h"
#include <sys/socket.h>
#include <unistd.h>

TcpSocket::TcpSocket()
{
    this->socket = 0;
    this->usable = false;
}

TcpSocket::TcpSocket(int socket)
{
    this->socket = socket;
    this->usable = false;
}

TcpSocket::~TcpSocket()
{
    if (this->usable)
    {
        shutdown(this->socket, SHUT_RDWR);
    }
    close(this->socket);
}

bool TcpSocket::isUsable()
{
    return this->usable;
}
