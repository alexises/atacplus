#include "TacacsPacketWithHeader.h"
#include "precondition.h"
#include "crypto.h"
#include "DecodingException.h"
#include "EncodingException.h"

TacacsPacketWithHeader::TacacsPacketWithHeader(TacacsPacketContext* context)
{
    precondition(context != NULL);
    this->header = NULL;
    this->context = context;
}

void TacacsPacketWithHeader::processDecode(Buffer& rbuff)
{
    if (this->context->isDecodeHeader())
    {
        this->header = new TacacsPacketHeader(rbuff);
        if (rbuff.availableRead() < this->header->getLength())
        {
            //we don't have enouth size for full decoding
            //delete header and redo buffer
            rbuff -= this->header->getSize();
            delete this->header;
            throw DecodingException("no enough byte for full decoding");
        }
        //check if payload should be deciphered
        if ((this->header->getFlags() & TacacsPacketFlags::Unencrypted) == 0)
        {
            encodeTacacsPacket(rbuff, this->header->getLength(),
                               this->context->getKey(), 
                               this->header->getSessionId(),
                               this->header->getVersion(),
                               this->header->getSeqNo());
        }
    }
    // decoding packet, check for corresponding size, if packet
    // return decoding error or si size missmatch, we considere
    // the packet mallformed and don't refill the buffer
    try 
    {
        this->decode(rbuff); 
    }
    catch (DecodingException& e)
    {
        delete this->header;
        throw;
    }
    if (this->context->isDecodeHeader() &&
        this->getSize() != this->header->getLength())
    {
        delete this->header;
        throw DecodingException("header and payload size missmatch");
    }
}

TacacsPacketWithHeader::~TacacsPacketWithHeader()
{
    if (this->header != NULL)
    {
        delete this->header;
    }
}

TacacsPacketHeader* TacacsPacketWithHeader::getHeader()
{
    return this->header;
}

void TacacsPacketWithHeader::encode(Buffer& wbuff)
{
    //FIXME : naive implementation, should process decode
    //all child class should generate the proper header
    //for the object
    if (this->header != NULL and this->context->isDecodeHeader())
    {
        this->header->encode(wbuff);
    }
    this->processEncode(wbuff);
}

void TacacsPacketWithHeader::setHeader(TacacsPacketHeader* header)
{
    precondition(header != NULL);
    this->header = header;
}

TacacsPacketContext* TacacsPacketWithHeader::getContext()
{
    return this->context;
}

