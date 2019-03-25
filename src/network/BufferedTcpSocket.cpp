#include <unistd.h>
#include <sys/socket.h>
#include "BufferedTcpSocket.h"
#include "precondition.h"
#include "macro.h"

BufferedTcpSocket::BufferedTcpSocket() : TcpSocket()
{
    this->rbuff = NULL;
    this->wbuff = NULL;
}

BufferedTcpSocket::BufferedTcpSocket(int socket) : TcpSocket(socket)
{
    this->rbuff = NULL;
    this->wbuff = NULL;
    this->usable = true;
}

BufferedTcpSocket::~BufferedTcpSocket()
{
}

void BufferedTcpSocket::setBuffer(Buffer* rbuff, Buffer* wbuff)
{
    precondition(rbuff != NULL && wbuff != NULL);
    this->rbuff = rbuff;
    this->wbuff = wbuff;
}

void BufferedTcpSocket::processBytes(int rbytes, int wbytes)
{
    precondition(rbuff != NULL && wbuff != NULL);
    precondition(usable == true);

    // first do non blocking operation
    size_t waitingWriteByte = this->wbuff->availableRead();
    size_t spaceForReading = this->rbuff->availableWrite();
    if (waitingWriteByte > 0)
    {
        wbytes -= this->write(false);
    }
    if (spaceForReading > 0)
    {
        rbytes -= this->read(false);
    }
    //now we do blocking operation only if no bytes
    //have been proccesses
    //we begin by writing first
    while (rbytes > 0 || wbytes > 0)
    {
        if (wbytes > 0 &&
            waitingWriteByte == this->wbuff->availableRead())
        {
            wbytes -= this->write(true);
        }
        if (rbytes > 0 &&
            spaceForReading == this->rbuff->availableRead())
        {
            rbytes -= this->read(true);
        }
    }
}

int BufferedTcpSocket::read(bool rblocking)
{
    precondition(rbuff != NULL && wbuff != NULL);
    precondition(usable == true);
    size_t availableWrite, currPos, size, firstBuffSize;
    int flags = 0;
    availableWrite = this->rbuff->availableWrite();
    currPos = this->rbuff->writePos;
    size = this->rbuff->size;
    firstBuffSize = min(size - currPos, availableWrite);

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
        return readBytes;
    }
    else
    {
        return 0;
    }
}

int BufferedTcpSocket::write(bool wblocking)
{
    precondition(rbuff != NULL && wbuff != NULL);
    precondition(usable == true);
    size_t availableRead, currPos, size, firstBuffSize;
    int flags = 0;
    availableRead = this->wbuff->availableRead();
    currPos = this->wbuff->readPos;
    size = this->wbuff->size;
    firstBuffSize = min(size - currPos, availableRead);

    if (!wblocking)
    {
        flags = MSG_DONTWAIT;
    }

    ssize_t writeBytes = send(this->socket,
                            &(this->wbuff->buff[currPos % size]),
                            firstBuffSize, flags);
    if (writeBytes > -1)
    {
        this->wbuff->readPos += writeBytes;
        return writeBytes;
    }
    else
    {
        return 0;
    }
}
