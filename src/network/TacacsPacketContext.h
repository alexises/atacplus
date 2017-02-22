#ifndef TACACSPACKETCONTEXT_H
#define TACACSPACKETCONTEXT_H
#include "TacacsPacketInterface.h"
#include "TacacsPacketHeader.h"
#include "enum.h"
#include "Buffer.h"
#include "FixedLengthString.h"

struct TacacsConnectionType
{
    enum_mbr Client = 1;
    enum_mbr Server = 2;
};

struct TacacsConnectionStep
{
    enum_mbr NoStart = 0;
    enum_mbr StartAuthentication = 1;
    enum_mbr StartAuthorization = 2;
    enum_mbr StartAccounting = 3;
    enum_mbr ReplayAuthentication = 4;
};

/**
 * store the context needed to encode and decode TacacsPacket
 */
class TacacsPacketContext
{
    public:
	/**
	 * construct the context
         *
         * @param[in] type : type of connection should be a member of TacacsConnectionType
         * @param[in] rbuff_size size of the reading buffer
         * @param[in] wbuff_size size of the writing buffer
	 */
        TacacsPacketContext(int type, size_t rbuff_size = 4096, size_t wbuff_size = 4096);
        /**
         * decode a packet
         */
        TacacsPacketInterface* decode();
        /**
         * the the shared key used to decipher/encipher the packet payload
         *
         * @param[in] key key to set
         */
        void setKey(FixedLengthString* key);
    private:
        int step;
	int connType;
        TacacsPacketHeader* header;
        FixedLengthString* key;
        Buffer rbuff;
        Buffer wbuff;
};
#endif
