#ifndef TACACSPACKETWITHHEADER_H
#define TACACSPACKETWITHHEADER_H
#include "TacacsPacketInterface.h"
#include "TacacsPacketHeader.h"
#include "TacacsPacketContext.h"

/**
 * allow the end packet to store the corresponding header
 * associated with the second step of packet decoding
 */
class TacacsPacketWithHeader : public TacacsPacketInterface
{
    public:
        /**
         * Build a TacackPacketWithHeader
         *
         * the context object is needed for encoding and decoding
         * @param[in] context context to set
         */
        TacacsPacketWithHeader(TacacsPacketContext* context);
        virtual ~TacacsPacketWithHeader();
        /**
         * get the associated header
         *
         * @return header of null if no header already set
         */
        TacacsPacketHeader* getHeader();
        /**
         * encode : encode a portion of a network packet from
         * the corresponding TacacsPacketInterface instance
         *
         * @param[out] wbuff buffer where the packet will be filled
         */
        virtual void encode(Buffer& wbuff);
        /**
         * getContext : get the associated context with this object
         *
         * @return context associated with this object
         */
        TacacsPacketContext* getContext();
    protected:
        /**
         * set the associated header
         *
         * @param[in] associated header
         * @pre header != NULL
         */
        void setHeader(TacacsPacketHeader* header);
        /**
         * really process the decode operation
         * should be colled on the constructor with a buffer argument
         * of each child class
         *
         * @param[in] rbuff buffer to decode
         */
        void processDecode(Buffer& rbuff);
        /**
         * really process the encoding operation
         * this method is called on decode methode and should 
         * not be called outside of this class
         *
         * @param[out] wbuff buffer to encode
         */
        virtual void processEncode(Buffer& wbuff) = 0;
    private:
        TacacsPacketHeader* header;
        TacacsPacketContext* context;
};

#endif
