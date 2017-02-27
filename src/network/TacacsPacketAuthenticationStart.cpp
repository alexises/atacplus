#include "TacacsPacketAuthenticationStart.h"
#include "EncodingException.h"

TacacsPacketAuthenticationStart::TacacsPacketAuthenticationStart(
            const uint8_t action,
            const uint8_t privLvl,
            const uint8_t authenType,
            const uint8_t service,
            FixedLengthString* user,
            FixedLengthString* port,
            FixedLengthString* remoteAddr,
            FixedLengthString* data)
{
    this->action = action;
    this->privLvl = privLvl;
    this->authenType = authenType;
    this->service = service;
    this->user = user;
    this->port = port;
    this->remoteAddr = remoteAddr;
    this->data = data;
}

TacacsPacketAuthenticationStart::~TacacsPacketAuthenticationStart()
{
    delete this->user;
    delete this->port;
    delete this->remoteAddr;
    delete this->data;
}

TacacsPacketAuthenticationStart* TacacsPacketAuthenticationStart::decode(Buffer& rbuff)
{
    if (rbuff.availableRead() < 8)
    {
        throw EncodingException("no enough size");
    }
    uint8_t action, privLvl, authenType, service;
    uint8_t userLen, portLen, remoteAddrLen, dataLen;
    FixedLengthString *user, *port, *remoteAddr, *data;

    rbuff >> action >> privLvl >> authenType >> service;
    rbuff >> userLen >> portLen >> remoteAddrLen >> dataLen;
    
    user = new FixedLengthString(userLen);
    port = new FixedLengthString(portLen);
    remoteAddr = new FixedLengthString(remoteAddrLen);
    data = new FixedLengthString(dataLen);

    if (rbuff.availableRead() < (userLen + portLen + remoteAddrLen + dataLen))
    {
        throw EncodingException("no enougth size of variable arguments");
    }
    rbuff >> user >> port >> remoteAddr >> data;
    return new TacacsPacketAuthenticationStart(
        action, privLvl, authenType, service,
        user, port, remoteAddr, data);
}

int TacacsPacketAuthenticationStart::encode(unsigned char* payload, const int size)
{
    return 0;
}

int TacacsPacketAuthenticationStart::getSize()
{
    return 8 + this->user->getSize()
             + this->port->getSize()
             + this->remoteAddr->getSize()
             + this->data->getSize();
}
