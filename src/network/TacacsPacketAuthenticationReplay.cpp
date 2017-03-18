#include "TacacsPacketAuthenticationReplay.h"
#include "EncodingException.h"
#include "DecodingException.h"
#include "precondition.h"

TacacsPacketAuthenticationReplay::TacacsPacketAuthenticationReplay(
    TacacsPacketContext* context,
    uint8_t status,
    uint8_t flags,
    FixedLengthString* promptMsg,
    FixedLengthString* data) : TacacsPacketAuthentication(context)
{
    this->setStatus(status);
    this->setFlags(flags);
    this->promptMsg = promptMsg;
    this->data = data;
}

TacacsPacketAuthenticationReplay::TacacsPacketAuthenticationReplay(
    TacacsPacketContext* context,
    Buffer& rbuff) : TacacsPacketAuthentication(context)
{
    this->processDecode(rbuff);
}

TacacsPacketAuthenticationReplay::~TacacsPacketAuthenticationReplay()
{
    delete this->promptMsg;
    delete this->data;
}

uint8_t TacacsPacketAuthenticationReplay::getStatus()
{
    return this->status;
}

void TacacsPacketAuthenticationReplay::setStatus(uint8_t status)
{
    precondition(status == AuthenticationStatus::Pass ||
                 status == AuthenticationStatus::Fail ||
                 status == AuthenticationStatus::GetData ||
                 status == AuthenticationStatus::GetUser ||
                 status == AuthenticationStatus::GetPassword ||
                 status == AuthenticationStatus::Restart ||
                 status == AuthenticationStatus::Error ||
                 status == AuthenticationStatus::Follow);
    this->status = status;
}

uint8_t TacacsPacketAuthenticationReplay::getFlags()
{
    return this->flags;
}

void TacacsPacketAuthenticationReplay::setFlags(uint8_t flags)
{
    precondition(flags == AuthenticationReplayFlags::NoFlags ||
                 flags == AuthenticationReplayFlags::NoEcho);
    this->flags = flags;
}

FixedLengthString* TacacsPacketAuthenticationReplay::getPromptMsg()
{
    return this->promptMsg;
}

FixedLengthString* TacacsPacketAuthenticationReplay::getData()
{
    return this->data;
}

void TacacsPacketAuthenticationReplay::decode(Buffer& rbuff)
{
    uint8_t status, flags;
    uint16_t promptMsgSize, dataSize;
    if (rbuff.availableRead() < 6)
    {
	 throw DecodingException("no enougth data for decoding");
    }
    rbuff >> status >> flags
    	  >> promptMsgSize >> dataSize;

    if (rbuff.availableRead() < (promptMsgSize + dataSize))
    {
        rbuff -= 6;
        throw DecodingException("no enougth size of variable arguments");
    }
    this->promptMsg = new FixedLengthString(promptMsgSize);
    this->data = new FixedLengthString(dataSize);
    rbuff >> *(this->promptMsg) >> *(this->data);

    try
    {
        this->setStatus(status);
        this->setFlags(flags);
    }
    catch (PreconditionFailException& e)
    {
        delete promptMsg;
        delete data;
        std::string msg("invalid parameter : ");
        msg += e.what();
        throw DecodingException(msg.c_str());
    }
}

void TacacsPacketAuthenticationReplay::processEncode(Buffer& wbuff)
{
    if (wbuff.availableWrite() < this->getSize())
    {
        throw EncodingException("to few bytes in the buffer");
    }
    wbuff << this->status << this->flags
	  << (uint16_t) this->promptMsg->getSize()
	  << (uint16_t) this->data->getSize()
	  << this->promptMsg << this->data;
}

size_t TacacsPacketAuthenticationReplay::getSize()
{
    return 6 + this->promptMsg->getSize()
	     + this->data->getSize();
}

