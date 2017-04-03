#include "TcpClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


TcpClient::TcpClient() : TcpSocket()
{
}

void TcpClient::connect(char* addr, uint16_t port)
{
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_in *h;
    int rv, cStatus;
 
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((rv = getaddrinfo(addr, NULL, &hints, &servinfo)) != 0) 
    {
        return;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        h = (struct sockaddr_in *) p->ai_addr;
        h->sin_port = htons(port);

        this->socket = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (this->socket == -1)
            continue;
        cStatus = ::connect(this->socket, 
                     (struct sockaddr *)&h, sizeof(h));

        if (cStatus == 0)
        {
            this->usable = true;
            break;
        }
    }
    freeaddrinfo(servinfo); // all done with this structure

    if (this->usable)
    {
        this->remotePort = port;
        this->remoteAddr = ntohl(h->sin_addr.s_addr);
        this->remoteFqdn = new FixedLengthString(addr, strlen(addr));
    }
}
