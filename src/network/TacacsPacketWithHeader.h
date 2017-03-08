#ifndef TACACSPACKETWITHHEADER_H
#define TACACSPACKETWITHHEADER_H
#include "TacacsPacketInterface.h"
#include "TacacsPacketHeader.h"

/**
 * allow the end packet to store the corresponding header
 * associated with the second step of packet decoding
 */
class TacacsPacketWithHeader : public TacacsPacketInterface
{
    public:
        TacacsPacketWithHeader();
        virtual ~TacacsPacketWithHeader();
        /**
         * get the associated header
         *
         * @return header of null if no header already set
         */
        TacacsPacketHeader* getHeader();
    protected:
        /**
         * set the associated header
         *
         * @param[in] associated header
         * @pre header != NULL
         */
        void setHeader(TacacsPacketHeader* header); 
    private:
        TacacsPacketHeader* header;
};

#endif
