#include "TacacsPacketContext.h"
#include "crypto.cpp"
#include "DecodingException.h"

TacacsPacketContext::TacacsPacketContext(int type, size_t rbuff_size, size_t wbuff_size) :
    rbuff(rbuff_size), wbuff(wbuff_size)
{
    this->connType = type;
    this->header = NULL;
    this->key = NULL;
    this->step = TacacsConnectionStep::NoStart;
}

void TacacsPacketContext::setKey(FixedLengthString* key)
{
    this->key = key;
}

TacacsPacketInterface* TacacsPacketContext::decode()
{
    if (this->header == NULL)
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
    }
}
