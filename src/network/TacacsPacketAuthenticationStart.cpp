#include "TacacsPacketAuthenticationStart.h"
#include "EncodingException.h"
#include "precondition.h"

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

uint8_t TacacsPacketAuthenticationStart::getAction()
{
    return this->action;
}

void TacacsPacketAuthenticationStart::setAction(uint8_t action)
{
    precondition(action == TacacsAuthenticationAction::Login ||
                 action == TacacsAuthenticationAction::ChangePassword ||
                 action == TacacsAuthenticationAction::SendPassword ||
                 action == TacacsAuthenticationAction::SendAuth);
    this->action = action;
}

uint8_t TacacsPacketAuthenticationStart::getPrivLvl()
{
    return this->privLvl;
}

void TacacsPacketAuthenticationStart::setPrivLvl(uint8_t privLvl)
{
    precondition(privLvl <= TACACS_MIN_PRIV_LVL &&
                 privLvl >= TACACS_MAX_PRIV_LVL);
    this->privLvl = privLvl;
}

uint8_t TacacsPacketAuthenticationStart::getAuthenType()
{
    return this->authenType;
}

void TacacsPacketAuthenticationStart::setAuthenType(uint8_t authenType)
{
    precondition(authenType == TacacsAuthenticationType::Ascii ||
                 authenType == TacacsAuthenticationType::Pap ||
                 authenType == TacacsAuthenticationType::Chap ||
                 authenType == TacacsAuthenticationType::Arap ||
                 authenType == TacacsAuthenticationType::mschap);
    this->authenType = authenType;
}

uint8_t TacacsPacketAuthenticationStart::getService()
{
    return this->service;
}

void TacacsPacketAuthenticationStart::setService(uint8_t service)
{
    precondition(service == TacacsAuthenticationService::None ||
                 service == TacacsAuthenticationService::Login ||
                 service == TacacsAuthenticationService::Enable ||
                 service == TacacsAuthenticationService::Ppp ||
                 service == TacacsAuthenticationService::Arap ||
                 service == TacacsAuthenticationService::Pt ||
                 service == TacacsAuthenticationService::Rcmd ||
                 service == TacacsAuthenticationService::X25 ||
                 service == TacacsAuthenticationService::Nasi ||
                 service == TacacsAuthenticationService::FwProxy);
    this->service = service;
}

FixedLengthString* TacacsPacketAuthenticationStart::getUser()
{
    return this->user;
}

FixedLengthString* TacacsPacketAuthenticationStart::getPort()
{
    return this->port;
}

FixedLengthString* TacacsPacketAuthenticationStart::getRemoteAddr()
{
    return this->remoteAddr;
}

FixedLengthString* TacacsPacketAuthenticationStart::getData()
{
    return this->data;
}
