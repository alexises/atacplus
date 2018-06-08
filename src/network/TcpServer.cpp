#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include "TcpServer.h"
#include "precondition.h"

TcpServer::TcpServer() : TcpSocket()
{
}

void TcpServer::listen(const char* addr, uint16_t port)
{
    struct sockaddr_in addr_struct;
    int ret;
    this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket == -1)
    {
        return;
    }

    memset(&addr_struct, '\0', sizeof(struct sockaddr_in));
    addr_struct.sin_family = AF_INET;
    addr_struct.sin_port = htons(port);
    inet_aton(addr, &addr_struct.sin_addr);
    ret = ::bind(this->socket, (struct sockaddr*) &addr_struct, sizeof(addr_struct)); 
    if (ret == -1)
    {
        return;
    }

    this->remotePort = port;
    this->remoteAddr = ntohl(addr_struct.sin_addr.s_addr);
    this->remoteFqdn = new FixedLengthString(addr, strlen(addr));

    ret = ::listen(this->socket, 5); //FIXME
    if (ret == -1)
    {
        return;
    }
    this->usable = true;
}

BufferedTcpSocket* TcpServer::accept()
{
    precondition(this->isUsable());

    struct sockaddr_in addr_struct;
    socklen_t addr_struct_size = sizeof(addr_struct); 
    int ret;
    BufferedTcpSocket* sock = NULL;

    ret = ::accept(this->socket, (sockaddr*) &addr_struct, &addr_struct_size);
    if (ret == -1)
    {
        return NULL;
    }
    
    sock = new BufferedTcpSocket(ret);
    return sock;
}
