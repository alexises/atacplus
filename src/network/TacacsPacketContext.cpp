#include "TacacsPacketContext.h"
#include "crypto.h"
#include "DecodingException.h"

TacacsPacketContext::TacacsPacketContext(int type, size_t rbuff_size, size_t wbuff_size) :
    rbuff(rbuff_size), wbuff(wbuff_size)
{
    this->connType = type;
    this->header = NULL;
    this->key = NULL;
    this->step = TacacsConnectionStep::NoStart;
    this->sessionId = 0;
    this->seqNo = 0;
    this->decodeHeader = false;
}

void TacacsPacketContext::setKey(FixedLengthString* key)
{
    this->key = key;
}

FixedLengthString* TacacsPacketContext::getKey()
{
    return this->key;
}

TacacsPacketInterface* TacacsPacketContext::decode()
{
/*  FIXME  
 *  if (this->header == NULL)
    {
        this->header = TacacsPacketHeader::decode(this->rbuff);
    }
    if (this->rbuff.availableRead() < this->header->getLength())
    {
        throw DecodingException("not enough size to decode packet payload");
    }
    if ((this->header->getFlags() & TacacsPacketFlags::Unencrypted) == 0)
    {
        encodeTacacsPacket(this->rbuff, this->header->getSize(), 
                           this->key, this->header->getSessionId(),
                           this->header->getVersion(),
                           this->header->getSeqNo());
    }
    if (this->header->getPacketType() == TacacsPacketType::Authentication)
    {
        switch(this->step)
        {
            case TacacsConnectionStep::NoStart:
                //return TacacsPacketAuthStart::decode(buff, (unsigned int) 0);
                break;
        }
    }*/
}

uint8_t TacacsPacketContext::getSeqNo()
{
    return this->seqNo;
}

bool TacacsPacketContext::isDecodeHeader()
{
    return this->decodeHeader;
}

void TacacsPacketContext::setDecodeHeader(bool decodeHeader)
{
    this->decodeHeader = decodeHeader;
}

uint32_t TacacsPacketContext::getSessionId()
{
    return this->sessionId;
}
