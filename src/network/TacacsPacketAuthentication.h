#ifndef TACACSPACKETAUTHENTICATION_H
#define TACACSPACKETAUTHENTICATION_H
#include "TacacsPacketWithHeader.h"

class TacacsPacketAuthentication : public TacacsPacketWithHeader
{
    public:
        TacacsPacketAuthentication(TacacsPacketContext* context);
    protected:
        /**
         * generate and set via setHeader method the corresponding
         * header with this packet
         */
        virtual void generateHeader();

};
#endif
