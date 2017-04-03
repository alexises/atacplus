#include "TcpSocket.h"
#include "precondition.h"
#include "macro.h"
#include <sys/socket.h>
#include <unistd.h>

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

TcpSocket::~TcpSocket()
{
    if (this->usable)
    {
        shutdown(this->socket, SHUT_RDWR);
    }
    close(this->socket);
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
    size_t availableWrite, currPos, size, firstBuffSize, secondBuffSize;
    int flags = 0;
    availableWrite = this->rbuff->availableWrite();
    currPos = this->rbuff->writePos;
    size = this->rbuff->size;
    firstBuffSize = min(size - currPos, availableWrite);
    secondBuffSize = availableWrite - firstBuffSize;

    if (!rblocking)
    {
        flags = MSG_DONTWAIT;
    }

    ssize_t readBytes = recv(this->socket, 
                            &(this->rbuff->buff[currPos % size]),
                            firstBuffSize, flags);
    if (readBytes > -1)
    {
        this->rbuff->writePos += readBytes;
        if (readBytes == firstBuffSize)
        {
            readBytes = recv(this->socket,
                             &(this->rbuff->buff),
                              secondBuffSize, 0);
        }
        if (readBytes > -1)
        {
            this->rbuff->writePos += readBytes;
        }
    }
}

void TcpSocket::write(bool wblocking)
{
    precondition(rbuff != NULL && wbuff != NULL);
    precondition(usable == true);
    size_t availableRead, currPos, size, firstBuffSize, secondBuffSize;
    int flags = 0;
    availableRead = this->wbuff->availableRead();
    currPos = this->wbuff->readPos;
    size = this->wbuff->size;
    firstBuffSize = min(size - currPos, availableRead);
    secondBuffSize = availableRead - firstBuffSize;

    if (!wblocking)
    {
        flags = MSG_DONTWAIT;
    }

    ssize_t writeBytes = send(this->socket,
                            &(this->wbuff->buff[currPos % size]),
                            firstBuffSize, flags);
    if (writeBytes > -1)
    {
        this->rbuff->readPos += writeBytes;
        if (writeBytes == firstBuffSize)
        {
            writeBytes = recv(this->socket,
                             &(this->wbuff->buff),
                              secondBuffSize, 0);
        }
        if (writeBytes > -1)
        {
            this->wbuff->readPos += writeBytes;
        }
    }

}
