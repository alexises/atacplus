#include "TacacsPacketContext.h"
#include "TacacsPacketWithHeader.h"
#include "TacacsPacketAuthenticationStart.h"
#include "TacacsPacketAuthenticationReplay.h"
#include "TacacsPacketAuthenticationContinue.h"
#include "crypto.h"
#include "DecodingException.h"
#include "EncodingException.h"
#include "precondition.h"

/**
 * get type of packet requested and build the corresponding object
 */
TacacsPacketWithHeader* startDecode(TacacsPacketContext* obj)
{
    uint8_t type;
    TacacsPacketWithHeader* res = NULL; //required for non managed method
    if (obj->rbuff.availableRead() < 12)
    {
        throw DecodingException("no enougth bytes for decoding");
    }
    type = obj->rbuff[2];
    switch (type)
    {
        case TacacsPacketType::Authentication:
            res = new TacacsPacketAuthenticationStart(obj, obj->rbuff);
            obj->decodeCallback = NULL;
            obj->encodeCallback = encodeAuthenticationReplay;
            break;
        case TacacsPacketType::Authorization:
            break;
        case TacacsPacketType::Accounting:
            break;
        default:
            throw DecodingException("bad packet type");
    }
    return res;
}

void startEncode(TacacsPacketContext* obj, TacacsPacketWithHeader* packet)
{
    std::string type = packet->getType();
    if (type == "auth-start")
    {
        obj->decodeCallback = decodeAuthenticationReplay;
        obj->encodeCallback = NULL;
    }
    else 
    {
        throw DecodingException("unexpected packed, expect auth-start");
    }
    packet->encode(obj->wbuff);
}

void encodeAuthenticationReplay(TacacsPacketContext* obj, TacacsPacketWithHeader* packet)
{
    if (packet->getType() != "auth-replay")
    {
        throw DecodingException("expecting AuthenticationStartInstance");
    }
    TacacsPacketAuthenticationReplay* 
        castPacket = dynamic_cast<TacacsPacketAuthenticationReplay*>(packet);
    castPacket->encode(obj->wbuff);
    uint8_t status = castPacket->getStatus();
    switch(status)
    {
        case AuthenticationStatus::GetData:
        case AuthenticationStatus::GetUser:
        case AuthenticationStatus::GetPassword:
            obj->decodeCallback = decodeAuthenticationContinue;
            break;
        default:
            obj->decodeCallback = startDecode;
            break;
    }
    obj->encodeCallback = NULL;
}

TacacsPacketWithHeader* decodeAuthenticationReplay(TacacsPacketContext* obj)
{
    TacacsPacketAuthenticationReplay* packet =
        new TacacsPacketAuthenticationReplay(obj, obj->rbuff);
    uint8_t status = packet->getStatus();
    switch (status)
    {
        case AuthenticationStatus::GetData:
        case AuthenticationStatus::GetUser:
        case AuthenticationStatus::GetPassword:
            obj->encodeCallback = encodeAuthenticationContinue;
            obj->decodeCallback = NULL;
            break;
        default:
            obj->encodeCallback = startEncode;
            obj->decodeCallback = NULL;
    }
    return packet;
}

TacacsPacketWithHeader* decodeAuthenticationContinue(TacacsPacketContext* obj)
{
    TacacsPacketAuthenticationContinue* packet = 
        new TacacsPacketAuthenticationContinue(obj, obj->rbuff);
    if ((packet->getFlags() & AuthenticationContinueFlags::ContinueAbort) != 0)
    {
        obj->encodeCallback = NULL;
        obj->decodeCallback = startDecode;
    }
    else
    {
        obj->encodeCallback = encodeAuthenticationReplay;
        obj->decodeCallback = NULL;
    }
    return packet;
}

void encodeAuthenticationContinue(TacacsPacketContext* obj, TacacsPacketWithHeader* packet)
{
    if (packet->getType() != "auth-continue")
    {
        throw EncodingException("Expect authentication continue packet");
    }
    TacacsPacketAuthenticationContinue* castPacket =
        dynamic_cast<TacacsPacketAuthenticationContinue*>(packet);
    if ((castPacket->getFlags() & AuthenticationContinueFlags::ContinueAbort) != 0)
    {
        obj->encodeCallback = startEncode;
        obj->decodeCallback = NULL;
    }
    else
    {
        obj->encodeCallback = NULL;
        obj->decodeCallback = decodeAuthenticationReplay;
    }
    packet->encode(obj->wbuff);
}


TacacsPacketContext::TacacsPacketContext(int type, size_t rbuff_size, size_t wbuff_size) :
    rbuff(rbuff_size), wbuff(wbuff_size)
{
    this->connType = type;
    this->key = NULL;
    this->sessionId = 0;
    this->seqNo = 0;
    this->decodeHeader = true;
    switch(this->connType)
    {
        case TacacsConnectionType::Server:
            this->encodeCallback = NULL;
            this->decodeCallback = startDecode;
            break;
        case TacacsConnectionType::Client:
            this->encodeCallback = startEncode;
            this->decodeCallback = NULL;
            break;
        default:
            throw PreconditionFailException("bad connection type should be TacacsConnectionType::Server or TacacsConnectionType::Client");
            break;
    }
}

TacacsPacketContext::~TacacsPacketContext()
{
    if (this->key != NULL)
    {
        delete this->key;
    }
}

void TacacsPacketContext::setKey(FixedLengthString* key)
{
    this->key = key;
}

FixedLengthString* TacacsPacketContext::getKey()
{
    return this->key;
}

TacacsPacketWithHeader* TacacsPacketContext::decode()
{
    if (this->decodeCallback == NULL)
    {
        throw DecodingException("not expectiong decoding operation");
    }
    return this->decodeCallback(this);
}

void TacacsPacketContext::encode(TacacsPacketWithHeader* packet)
{
    if (this->decodeCallback == NULL)
    {
        throw EncodingException("not expection encoding operation");
    }
    this->encodeCallback(this, packet);
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
