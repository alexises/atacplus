#include "TacacsPacketContext.h"

TacacsPacketContext::TacacsPacketContext(int type)
{
    this->connType = type;
    this->header = NULL;
    this->key = NULL;
    this->step = TacacsConnectionStep::NoStart;
}

TacacsPacketInterface* TacacsPacketContext::decode()
{
    /* FIXME : tmp for compiling */
    unsigned char buff[1];
    if (this->header == NULL)
    {
        this->header = TacacsPacketHeader::decode(buff, (unsigned int) 0, this->key);
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
