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
    this->type = type;
    this->seqNo = seqNo;
    this->flags = flags;
    this->sessionId = sessionId;
    this->length = length;
}

TacacsPacketHeader::~TacacsPacketHeader()
{
}

int TacacsPacketHeader::encode(char* payload, int size)
{
    if (size < this->getSize())
    {
        throw EncodingException("buffer too small");
    }
    payload[0] = this->version;
    payload[1] = this->type;
    payload[2] = this->seqNo;
    payload[3] = this->flags;
    uint32_t tmp = htonl(this->sessionId);
    memcpy(&payload[4], &tmp, 4);
    tmp = htonl(this->length);
    memcpy(&payload[8], &tmp, 4);
    return TACACS_PACKET_HEADER_SIZE;
}

TacacsPacketHeader* TacacsPacketHeader::decode(const char* payload, int size)
{
    if (size < TACACS_PACKET_HEADER_SIZE)
    {
        throw DecodingException("buffer too small");
    }
    uint8_t version = payload[0];
    uint8_t type = payload[1];
    uint8_t seqNo = payload[2];
    uint8_t flags = payload[3];
    uint32_t sessionId = (uint32_t) payload[4];
    uint32_t length;
    memcpy(&sessionId,  &payload[4], 4);
    memcpy(&length, &payload[8], 4);
    try {
        return new TacacsPacketHeader(version, type, seqNo, flags,
                       ntohl(sessionId), ntohl(length));
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

uint8_t TacacsPacketHeader::getPacketType()
{
    return this->type;
}

uint8_t TacacsPacketHeader::getSeqNo()
{
    return this->seqNo;
}

uint8_t TacacsPacketHeader::getFlags()
{
    return this->flags;
}

uint32_t TacacsPacketHeader::getSessionId()
{
    return this->sessionId;
}

uint32_t TacacsPacketHeader::getLength()
{
    return this->length;
}
