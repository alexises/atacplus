#ifndef TACACSPACKETCONTEXT_H
#define TACACSPACKETCONTEXT_H
#include "enum.h"
#include "Buffer.h"
#include "FixedLengthString.h"

struct TacacsConnectionType
{
    enum_mbr Client = 1;
    enum_mbr Server = 2;
};

struct TacacsPacketContextState
{
    enum_mbr StartClient = 0;
    enum_mbr StartServer = 1;
    enum_mbr EncodeAuthReplay = 2;
    enum_mbr DecodeAuthReplay = 3;
    enum_mbr EncodeAuthContinue = 4;
    enum_mbr DecodeAuthContinue = 5;
};
#define STATE_COUNT 6

//forwoard declaration
class TacacsPacketContext;
class TacacsPacketWithHeader; //needed to solve cycling inclusion


/**
 * private function used internally, theses function are declered here 
 * for freind keyword usage.
 * theses functions are used for encoding and decoding purpose
 */
TacacsPacketWithHeader* startDecode(TacacsPacketContext* obj);
void encodeAuthenticationReplay(TacacsPacketContext* obj, TacacsPacketWithHeader* packet);
TacacsPacketWithHeader* decodeAuthenticationContinue(TacacsPacketContext* obj);
void startEncode(TacacsPacketContext* obj, TacacsPacketWithHeader* packet);
TacacsPacketWithHeader* decodeAuthenticationReplay(TacacsPacketContext* obj);
void encodeAuthenticationContinue(TacacsPacketContext* obj, TacacsPacketWithHeader* packet);


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
         * 
         * @return decoded packety
         */
        TacacsPacketWithHeader* decode();
        /**
         * encode a packet
         *
         * @param[in] packet packet to encode
         */
        void encode(TacacsPacketWithHeader* packet);
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
        /**
         * getRbuff get internal read buffer
         *
         * this function is needed to warm up the BufferedTcpSocket
         * @return read buffer
         */
        Buffer* getRbuff();
        /**
         * getWbuff get internal read buffer
         *
         * this function is needed to warm up the BufferedTcpSocket
         * @return write buffer
         */
        Buffer* getWbuff();
    private:
        int stateId;
        int connType;
        int context;
        uint32_t sessionId;
        uint8_t seqNo;
        FixedLengthString* key;
        Buffer rbuff;
        Buffer wbuff;
        bool decodeHeader;
        void (*encodeCallback[STATE_COUNT])(TacacsPacketContext*, TacacsPacketWithHeader*);
        TacacsPacketWithHeader* (*decodeCallback[STATE_COUNT])(TacacsPacketContext*);

    friend TacacsPacketWithHeader* startDecode(TacacsPacketContext* obj);
    friend void encodeAuthenticationReplay(TacacsPacketContext* obj, TacacsPacketWithHeader* packet);
    friend TacacsPacketWithHeader* decodeAuthenticationContinue(TacacsPacketContext* obj);
    friend void startEncode(TacacsPacketContext* obj, TacacsPacketWithHeader* packet);
    friend TacacsPacketWithHeader* decodeAuthenticationReplay(TacacsPacketContext* obj);
    friend void encodeAuthenticationContinue(TacacsPacketContext* obj, TacacsPacketWithHeader* packet);
};
#endif
