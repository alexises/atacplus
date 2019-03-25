#include "TacacsPacketAuthenticationContinue.h"
#include "precondition.h"
#include "EncodingException.h"
#include "DecodingException.h"
#include "BufferExaustionException.h"

TacacsPacketAuthenticationContinue::TacacsPacketAuthenticationContinue(
     TacacsPacketContext* context,
     FixedLengthString* userMsg,
     FixedLengthString* data,
     uint8_t flags) : TacacsPacketAuthentication(context)
{
    this->setFlags(flags);
    this->userMsg = userMsg;
    this->data = data;
}

TacacsPacketAuthenticationContinue::TacacsPacketAuthenticationContinue(
    TacacsPacketContext* context,
    Buffer& rbuff) : TacacsPacketAuthentication(context)
{
    this->processDecode(rbuff);
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

void TacacsPacketAuthenticationContinue::processEncode(Buffer& wbuff)
{
    if (wbuff.availableWrite() < this->getSize())
    {
        throw BufferExaustionException(BufferExaustionCondition::Overflow, this->getSize() - wbuff.availableWrite());
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
        throw BufferExaustionException(BufferExaustionCondition::Underflow, 5 - rbuff.availableRead());
    }
    
    uint16_t userMsgSize, dataSize;
    uint8_t flags;
    rbuff >> userMsgSize >> dataSize
          >> flags;
    if (rbuff.availableRead() < (userMsgSize + dataSize))
    {
        rbuff -= 5;
        throw BufferExaustionException(BufferExaustionCondition::Underflow, (userMsgSize + dataSize) - rbuff.availableRead());
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
