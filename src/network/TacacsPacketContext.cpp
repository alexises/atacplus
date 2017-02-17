#include "TacacsPacketContext.h"

TacacsPacketContext::TacacsPacketContext(int type)
{
    this->connType = type;
    this->header = NULL;
    this->key = NULL;
    this->step = TacacsConnectionStep::NoStep;
}

TacacsPacketInterface* TacacsPacketContext::decode()
{
    if (this->header == NULL)
    {
        this->header = TacacsPacketHeader::decode(this->key);
    }
    if (this->header->getPacketType() == TacacsPacketType::Authentication)
    {
        switch(this->step)
        {
            case TacacsConnectionStep::NoStep:
                return TacacsPacketAuthStart::decode();
                break;
        }
    }
}
