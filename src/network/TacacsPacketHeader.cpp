#include "TacacsPacketHeader.h"
#include "EncodingException.h"
#include "DecodingException.h"
#include "precondition.h"
#include <netinet/in.h>
#include <cstring>

TacacsPacketHeader::TacacsPacketHeader(const uint8_t version,
    const uint8_t type,
    const uint8_t seqNo,
    const uint8_t flags,
    const uint32_t sessionId,
    const uint32_t length)
{
    this->setVersion(version);
    this->setPacketType(type);
    this->seqNo = seqNo;
    this->setFlags(flags);
    this->sessionId = sessionId;
    this->length = length;
}

TacacsPacketHeader::TacacsPacketHeader(Buffer& rbuff)
{
    TacacsPacketHeader::decode(rbuff);
}

TacacsPacketHeader::TacacsPacketHeader(const TacacsPacketHeader & other)
{
    this->version = other.version;
    this->type = other.type;
    this->seqNo = other.seqNo;
    this->flags = other.flags;
    this->sessionId = other.sessionId;
    this->length = other.length;
}

TacacsPacketHeader::~TacacsPacketHeader()
{
}

void TacacsPacketHeader::encode(Buffer& wbuff)
{
    if (wbuff.availableWrite() < this->getSize())
    {
        throw EncodingException("buffer too small");
    }
    wbuff << this->version
          << this->type
          << this->seqNo
          << this->flags
          << this->sessionId
          << this->length;
}

void TacacsPacketHeader::decode(Buffer& rbuff)
{
    if (rbuff.availableRead() < TACACS_PACKET_HEADER_SIZE)
    {
        throw DecodingException("buffer too small");
    }
    uint8_t version, type, flags;
    rbuff >> version >> type >> this->seqNo >> flags
          >> this->sessionId >> this->length;

    try {
        this->setVersion(version);
        this->setPacketType(type);
        this->setFlags(flags);
    }
    catch (PreconditionFailException & e)
    {
	std::string msg("invalid parameter : ");
        msg += e.what();
        throw DecodingException(msg.c_str());
    }
}

int TacacsPacketHeader::getMajorVersion()
{
    return this->version >> 4;
}

int TacacsPacketHeader::getMinorVersion()
{
    return this->version & 0x0f; 
}

void TacacsPacketHeader::setVersion(int major, int minor)
{
    precondition(major == TACACS_MAJOR);
    precondition(minor == TACACS_MINOR_DEFAULT ||
                 minor == TACACS_MINOR_ONE);
    this->version = (major << 4) + minor;
}

void TacacsPacketHeader::setVersion(uint8_t version)
{
    this->setVersion(version >> 4, version & 0x0f);
}

uint8_t TacacsPacketHeader::getVersion()
{
    return this->version;
}

uint8_t TacacsPacketHeader::getPacketType()
{
    return this->type;
}

void TacacsPacketHeader::setPacketType(uint8_t type)
{
    precondition(type == TacacsPacketType::Authentication ||
		 type == TacacsPacketType::Authorization ||
		 type == TacacsPacketType::Accounting);
    this->type = type;
}

uint8_t TacacsPacketHeader::getSeqNo()
{
    return this->seqNo;
}

uint8_t TacacsPacketHeader::getFlags()
{
    return this->flags;
}

void TacacsPacketHeader::setFlags(uint8_t flags)
{
    precondition(flags <= TacacsPacketFlags::Unencrypted) 
    this->flags = flags;
}
uint32_t TacacsPacketHeader::getSessionId()
{
    return this->sessionId;
}

uint32_t TacacsPacketHeader::getLength()
{
    return this->length;
}
