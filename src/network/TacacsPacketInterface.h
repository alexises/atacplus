#ifndef TACACSPACKETINTERFACE_H
#define TACACSPACKETINTERFACE_H
#include <string>
#include "Buffer.h"

class TacacsPacketInterface
{
    public:
        /**
         * encode : encode a portion of a network packet from
         * the corresponding TacacsPacketInterface instance
         *
         * @param[out] wbuff buffer where the packet will be filled
         */
        virtual void encode(Buffer& wbuff) = 0;
        /**
         * getType : get an unique string that describe the type of packet decoded
         * @return the correspoding unique indentifier string
         */
        virtual std::string getType() = 0;
        /**
         * getSize : get the size of the corresponding part of the packet
         * @return size of the packet
         * 
         * this function should be used to allocate the proper buffer
         * to decode the corresponding package
         */
        virtual size_t getSize() = 0;
	virtual inline ~TacacsPacketInterface() { };
};

#endif
