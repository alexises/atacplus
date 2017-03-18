#include "TacacsPacketWithHeader.h"
#include "precondition.h"
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
    }
    this->decode(rbuff);
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

