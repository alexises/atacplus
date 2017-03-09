#include "TacacsPacketAuthenticationContinue.h"
#include "precondition.h"
#include "EncodingException.h"
#include "DecodingException.h"

TacacsPacketAuthenticationContinue::TacacsPacketAuthenticationContinue(
     FixedLengthString* userMsg, FixedLengthString* data, uint8_t flags)
{
    this->setFlags(flags);
    this->userMsg = userMsg;
    this->data = data;
}

TacacsPacketAuthenticationContinue::TacacsPacketAuthenticationContinue(Buffer& rbuff, bool decodeHeader)
{
    this->processDecode(rbuff, decodeHeader);
}

TacacsPacketAuthenticationContinue::~TacacsPacketAuthenticationContinue()
{
    delete this->userMsg;
    delete this->data;
}

uint8_t TacacsPacketAuthenticationContinue::getFlags()
{
    return this->flags;
}

void TacacsPacketAuthenticationContinue::setFlags(uint8_t flags)
{
    precondition(flags == AuthenticationContinueFlags::NoFlags ||
                 flags == AuthenticationContinueFlags::ContinueAbort);
    this->flags = flags;
}

FixedLengthString* TacacsPacketAuthenticationContinue::getData()
{
    return this->data;
}

FixedLengthString* TacacsPacketAuthenticationContinue::getUserMsg()
{
    return this->userMsg;
}

size_t TacacsPacketAuthenticationContinue::getSize()
{
    return 5 + this->data->getSize()
             + this->userMsg->getSize();
}

void TacacsPacketAuthenticationContinue::encode(Buffer& wbuff)
{
    if (wbuff.availableWrite() < this->getSize())
    {
        throw EncodingException("no enough space on the buffer");
    }

    wbuff << (uint16_t) this->userMsg->getSize()
          << (uint16_t) this->data->getSize()
          << this->flags << this->userMsg
          << this->data;
}

 
void TacacsPacketAuthenticationContinue::decode(Buffer& rbuff)
{
    if (rbuff.availableRead() < 5)
    {
        throw DecodingException("no enough space to read header");
    }
    
    uint16_t userMsgSize, dataSize;
    uint8_t flags;
    rbuff >> userMsgSize >> dataSize
          >> flags;
    if (rbuff.availableRead() < (userMsgSize + dataSize))
    {
        rbuff -= 5;
        throw DecodingException("no enough byte to decode variable part");
    }
    this->userMsg = new FixedLengthString(userMsgSize);
    this->data = new FixedLengthString(dataSize);
    rbuff >> *(this->userMsg) >> *(this->data);

    try
    {
        this->setFlags(flags);
    }
    catch (PreconditionFailException& e)
    {
        delete userMsg;
        delete data;
        std::string msg("invalid parameter : ");
        msg += e.what();
        throw DecodingException(msg.c_str());
    }
}
