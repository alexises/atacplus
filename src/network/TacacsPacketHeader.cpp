#include "TacacsPacketHeader.h"
#include "EncodingException.h"

TacacsPacketHeader::TacacsPacketHeader(const uint8_t version,
	const uint8_t type,
	const uint8_t seqNo,
        const uint8_t flags,
        const uint32_t sessionId,
        const uint32_t length)
{
	this->version = version;
	this->type = type;
	this->seqNo = seqNo;
	this->flags = flags;
	this->sessionId = sessionId;
	this->length = length;
}

virtual int encode(char* payload, int size)
{
	if (size < this->getSize())
	{
		throw EncodingException("buffer too small")
	}
	payload[0] = this->version;
	payload[1] = this->type;
	payload[2] = this->seqNo;
	payload[3] = this->flags;
	memcpy(&payload[4], htonl(this->sessionId), 4);
	memcpy(&payload[8], htonl(this->size), 4);
}

static virtual TacacsPacketHeader* decode(const char* paylod, int size)
{
	if (size < TACAS_PACKET_HEADER_SIZE)
	{
		throw DecodingException("buffer too small");
	}
	uint8_t version = payload[0];
	uint8_t type = payload[1];
	uint8_t seqNo = payload[2];
	uint8_t flags = payload[3];
	uint32_t sessionId;
	uint32_t size;
	memcpy(&sessionId, &payload[4], 4);
	memcpy(&size, &payload[8], 4);
        return new TacacsPacketHeader(version, type, seqNo, flags,
		       	sessionId, size);
}
