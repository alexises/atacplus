#include "TcpSocket.h"
#include "precondition.h"
#include "macro.h"
#include <sys/socket.h>
#include <unistd.h>

TcpSocket::TcpSocket()
{
    this->socket = 0;
    this->usable = false;
    this->remoteFqdn = NULL;
}

TcpSocket::TcpSocket(int socket)
{
    this->socket = socket;
    this->usable = false;
    this->remoteFqdn = NULL;
}

TcpSocket::~TcpSocket()
{
    if (this->usable)
    {
        shutdown(this->socket, SHUT_RDWR);
    }
    close(this->socket);
    if (this->remoteFqdn != NULL)
    {
        delete this->remoteFqdn;
    }
}

bool TcpSocket::isUsable()
{
    return this->usable;
}
