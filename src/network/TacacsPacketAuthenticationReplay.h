#ifndef TACACSPACKETAUTHENTICATIONREPLAY_H
#define TACACSPACKETAUTHENTICATIONREPLAY_H
#include "enum.h"
#include "TacacsPacketWithHeader.h"
#include "FixedLengthString.h"
#include "Buffer.h"

struct AuthenticationStatus
{
    enum_mbr Pass = 1;
    enum_mbr Fail = 2;
    enum_mbr GetData = 3;
    enum_mbr GetUser = 4;
    enum_mbr GetPassword = 5;
    enum_mbr Restart = 6;
    enum_mbr Error = 7;
    enum_mbr Follow = 21;
};

struct AuthenticationReplayFlags
{
    enum_mbr NoFlags = 0;
    enum_mbr NoEcho = 1;
};

class TacacsPacketAuthenticationReplay : public TacacsPacketWithHeader
{
    public:
        /**
         * Create a TacacsPacketAuthenticationReplay packet
         *
         * @param[in] status status of the authentication from AuthenticationStatus
         * @param[in] flags flags associated with the replay
         * @param[in] promptMsg message printed to the user for the requested field
         * @param[in] data data requered to perform the specific authentication task
         */
        TacacsPacketAuthenticationReplay(uint8_t status, uint8_t flags,
                                        FixedLengthString* promptMsg,
                                        FixedLengthString* data);
        TacacsPacketAuthenticationReplay(Buffer& rbuff, bool headerDecode = true);
        virtual ~TacacsPacketAuthenticationReplay();
        /**
         * getStatus get the status of the authentication
         *
         * @return status of the authentication
         */
        uint8_t getStatus();
        /**
         * setStatus set the status of the authentication
         *
         * @param[in] status status to set
         * @pre status == AuthenticationStatus::Pass ||
         *      status == AuthenticationStatus::Fail ||
         *      status == AuthenticationStatus::GetData ||
         *      status == AuthenticationStatus::GetUser ||
         *      status == AuthenticationStatus::GetPassword ||
         *      status == AuthenticationStatus::Restart ||
         *      status == AuthenticationStatus::Error ||
         *      status == AuthenticationStatus::Follow
         */
        void setStatus(uint8_t status);
        /**
         * getFlags : get the flags associated with the
         * Authentication replay package
         *
         * @return flags of the packet
         */
        uint8_t getFlags();
        /**
         * setFlags : set flags associated with the
         * Authentication replay package
         *
         * @param[in] flags flags to set
         * @pre flags == AuthenticationReplayFlags::NoFlags ||
         *      flags == AuthenticationReplayFlags::NoEchos
         */
        void setFlags(uint8_t flags);
        /**
         * getPromptMsg get the associated prompt message with this
         * packet
         *
         * @return promptMsg
         */
        FixedLengthString* getPromptMsg();
        /**
         * getData get the data required by the Tacacs+ Client to 
         * perform the selected authentication
         *
         * @return data
         */
        FixedLengthString* getData();
        /**
         * getType : get an unique string that describe the type of packet decoded
         * @return the correspoding unique indentifier string
         */
        virtual std::string getType()
        {
            return std::string("auth-replay");
        }
        /**
         * getSize : get the size of the corresponding part of the packet
         * @return size of the packet
         *
         * this function should be used to allocate the proper buffer
         * to decode the corresponding package
         */
        virtual size_t getSize();
    protected:
        /**
         * decode data from a buffer and create the corresponding
         * instance of TacacsPacketAuthenticationReplay
         *
         * @param[in] buffer buffer where fetch bytexs
         * @return created instance of TacacsPacketAuthenticationReplay
         */
         virtual void decode(Buffer& rbuff);
         /**
         * processEncode this object to the corresponding Buffer
         *
         * @param[out] buffer buffer where bytes are wrote
         */
        virtual void processEncode(Buffer& wbuff);
    private:
        uint8_t status;
        uint8_t flags;
        FixedLengthString* promptMsg;
        FixedLengthString* data;

};


#endif
