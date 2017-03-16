#include "TacacsPacketWithHeader.h"
#include "precondition.h"
TacacsPacketWithHeader::TacacsPacketWithHeader()
{
    this->header = NULL;
}

void TacacsPacketWithHeader::processDecode(Buffer& rbuff, bool headerDecode)
{
    if (headerDecode)
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

void TacacsPacketWithHeader::setHeader(TacacsPacketHeader* header)
{
    precondition(header != NULL);
    this->header = header;
}
