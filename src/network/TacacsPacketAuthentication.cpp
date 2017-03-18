#include "TacacsPacketAuthentication.h"
#include "TacacsPacketHeader.h"

TacacsPacketAuthentication::TacacsPacketAuthentication(
    TacacsPacketContext* context) : TacacsPacketWithHeader(context)
{
}

void TacacsPacketAuthentication::generateHeader()
{
    this->setHeader(
        new TacacsPacketHeader(TACACS_MAJOR + TACACS_MINOR_ONE,
                               TacacsPacketType::Authentication,
                               this->getContext()->getSeqNo(),
                               TacacsPacketFlags::NoFlags,
                               this->getContext()->getSessionId(),
                               this->getSize())
    );
}
