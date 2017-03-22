#include "TcpSocket.h"
#include "precondition.h"

TcpSocket::TcpSocket()
{
    this->socket = 0;
    this->rbuff = NULL;
    this->wbuff = NULL;
    this->usable = false;
}

TcpSocket::TcpSocket(int socket)
{
    this->socket = socket;
    this->rbuff = NULL;
    this->wbuff = NULL;
    this->usable = false;
}

void TcpSocket::setBuffer(Buffer* rbuff, Buffer* wbuff)
{
    precondition(rbuff != NULL && wbuff != NULL);
    this->rbuff = rbuff;
    this->wbuff = wbuff;
}

bool TcpSocket::isUsable()
{
    return this->usable;
}

void TcpSocket::processBytes(bool rblocking, bool wblocking)
{
    precondition(rbuff != NULL && wbuff != NULL);
    precondition(usable == true);

    // first do non blocking operation
    size_t waitingWriteByte = this->wbuff->availableRead();
    size_t spaceForReading = this->rbuff->availableWrite();
    if (waitingWriteByte > 0)
    {
        this->write(false); 
    }
    if (spaceForReading > 0)
    {
        this->read(false);
    }
    //now we do blocking operation only if no bytes
    //have been proccesses
    //we begin by writing first
    if (wblocking &&
        waitingWriteByte == this->wbuff->availableRead())
    {
        this->write(true);
    }
    if (rblocking &&
        spaceForReading == this->rbuff->availableRead())
    {
        this->read(true);
    }
}

void TcpSocket::read(bool rblocking)
{
    precondition(rbuff != NULL && wbuff != NULL);
    precondition(usable == true);
}

void TcpSocket::write(bool wblocking)
{
    precondition(rbuff != NULL && wbuff != NULL);
    precondition(usable == true);
}
