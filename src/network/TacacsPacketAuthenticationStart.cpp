#include "TacacsPacketAuthenticationStart.h"
#include "DecodingException.h"
#include "EncodingException.h"
#include "BufferExaustionException.h"
#include "precondition.h"
#include <string>

TacacsPacketAuthenticationStart::TacacsPacketAuthenticationStart(
            TacacsPacketContext* context,
            const uint8_t action,
            const uint8_t privLvl,
            const uint8_t authenType,
            const uint8_t service,
            FixedLengthString* user,
            FixedLengthString* port,
            FixedLengthString* remoteAddr,
            FixedLengthString* data) : TacacsPacketAuthentication(context)
{
    this->setAction(action);
    this->setPrivLvl(privLvl);
    this->setAuthenType(authenType);
    this->setService(service);
    this->user = user;
    this->port = port;
    this->remoteAddr = remoteAddr;
    this->data = data;
}

TacacsPacketAuthenticationStart::TacacsPacketAuthenticationStart(
    TacacsPacketContext* context,
    Buffer& rbuff) : TacacsPacketAuthentication(context)
{
    this->processDecode(rbuff);
}

TacacsPacketAuthenticationStart::~TacacsPacketAuthenticationStart()
{
    delete this->user;
    delete this->port;
    delete this->remoteAddr;
    delete this->data;
}

void TacacsPacketAuthenticationStart::decode(Buffer& rbuff)
{
    if (rbuff.availableRead() < 8)
    {
        throw BufferExaustionException(BufferExaustionCondition::Underflow, 8 - rbuff.availableRead());
    }
    uint8_t action, privLvl, authenType, service;
    uint8_t userLen, portLen, remoteAddrLen, dataLen;

    rbuff >> action >> privLvl >> authenType >> service
          >> userLen >> portLen >> remoteAddrLen >> dataLen;
    
    if (rbuff.availableRead() < (size_t) (userLen + portLen + remoteAddrLen + dataLen))
    {
        rbuff -= 8;
        throw BufferExaustionException(BufferExaustionCondition::Underflow, (userLen + portLen + remoteAddrLen + dataLen) - rbuff.availableRead());
    }
    this->user = new FixedLengthString(userLen);
    this->port = new FixedLengthString(portLen);
    this->remoteAddr = new FixedLengthString(remoteAddrLen);
    this->data = new FixedLengthString(dataLen);
    rbuff >> this->user >> this->port >> this->remoteAddr >> this->data;
    try {
        this->setAction(action);
        this->setPrivLvl(privLvl);
        this->setAuthenType(authenType);
        this->setService(service);
    }
    catch (PreconditionFailException &e)
    {
        delete this->user;
        delete this->port;
        delete this->remoteAddr;
        delete this->data;
        std::string msg("invalid parameter : ");
        msg += e.what();
        throw DecodingException(msg.c_str());
    }
}

void TacacsPacketAuthenticationStart::processEncode(Buffer& wbuff)
{
    if (wbuff.availableWrite() < this->getSize())
    {
        throw BufferExaustionException(BufferExaustionCondition::Overflow, this->getSize() - wbuff.availableRead());
    }

    wbuff << this->action << this->privLvl << this->authenType << this->service
          << (uint8_t) this->user->getSize() << (uint8_t) this->port->getSize()
          << (uint8_t) this->remoteAddr->getSize() << (uint8_t) this->data->getSize()
          << *(this->user) << *(this->port) << *(this->remoteAddr) << *(this->data);
}

size_t TacacsPacketAuthenticationStart::getSize()
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
    precondition(privLvl >= TACACS_MIN_PRIV_LVL &&
                 privLvl <= TACACS_MAX_PRIV_LVL);
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
