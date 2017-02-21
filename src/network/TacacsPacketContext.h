#ifndef TACACSPACKETCONTEXT_H
#define TACACSPACKETCONTEXT_H
#include "TacacsPacketInterface.h"
#include "TacacsPacketHeader.h"
#include "enum.h"

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
	 */
        TacacsPacketContext(int type);
        /**
         * decode a packet
         */
        TacacsPacketInterface* decode();
    private:
        int step;
	int connType;
        TacacsPacketHeader* header;
        char* key;
};
#endif
