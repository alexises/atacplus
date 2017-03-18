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
        ~TacacsPacketContext();
        /**
         * decode a packet
         */
        TacacsPacketInterface* decode();
        /**
         * set the shared key used to decipher/encipher the packet payload
         *
         * @param[in] key key to set
         */
        void setKey(FixedLengthString* key);
        /**
         * get the shared key used tu decipher/encipher the packet payload
         *
         * @return shared key
         */
        FixedLengthString* getKey();
        /**
         * getSeqNo get the next sequence number expecteed for
         * encoding or decoding
         *
         * @return expected seqNo
         */
        uint8_t getSeqNo();
        /**
         * get the decode header boolean.
         *
         * This boolean specify if the header should be encoded
         * when the packet is created
         *
         * @return decode header value
         */
        bool isDecodeHeader();
        /**
         * set the decode header boolean
         *
         * This boolean specify if the header should be encoded
         * when the packet is created
         *
         * @param[in] decodeHeader header to set
         */
        void setDecodeHeader(bool decodeHeader);
        /**
         * getSession id get the session id associated with 
         * this tacacsPacketContext object
         *
         * @return session id
         */
        uint32_t getSessionId();
    private:
        int step;
	int connType;
        uint32_t sessionId;
        uint8_t seqNo;
        TacacsPacketHeader* header;
        FixedLengthString* key;
        Buffer rbuff;
        Buffer wbuff;
        bool decodeHeader;
};
#endif
