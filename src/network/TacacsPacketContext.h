#ifndef TACACSPACKETCONTEXT_H
#define TACACSPACKETCONTEXT_H

enum TacacsConnectionType
{
    Client = 1,
    Server = 2
};

enum TacacsConnectionStep
{
    NoStart = 0,
    StartAuthentication = 1,
    StartAuthorization = 2,
    StartAccounting = 3,
    ReplayAuthentication = 4
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
    private:
        int step;
	int connType;
};
#endif
