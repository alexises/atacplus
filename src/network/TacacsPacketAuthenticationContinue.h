#ifndef TACACSPACKETAUTHENTICATIONCONTINUE_H
#define TACACSPACKETAUTHENTICATIONCONTINUE_H
#include "TacacsPacketAuthentication.h"
#include "FixedLengthString.h"
#include "enum.h"

struct AuthenticationContinueFlags
{
    enum_mbr NoFlags = 0;
    enum_mbr ContinueAbort = 1;
};

class TacacsPacketAuthenticationContinue : public TacacsPacketAuthentication
{
    public:
        /**
         * create a TacacsPacketAuthenticationContinue packet
         * @param[in] context context associated with this packet
         * @param[in] userMsg response of the server msg
         * @param[in] data specific data depending on the choose
         *            authentication method
         * @param[in] flags flags associated with this packet
         */
        TacacsPacketAuthenticationContinue(
            TacacsPacketContext* context,
            FixedLengthString* userMsg,
            FixedLengthString* data, 
            uint8_t flags);
        TacacsPacketAuthenticationContinue(
            TacacsPacketContext* context,
            Buffer& rbuff);
        virtual ~TacacsPacketAuthenticationContinue();
        /**
         * get flags : get flags of the packe
         * @return flags of the packet
         */
        uint8_t getFlags();
        /**
         * set flags : set the flags of the packet
         * @param[in] flags flags to set
         * @pre flags == AuthenticationContinueFlags::NoFlags
         *      flags == AuthenticationContinueFlags::ContinueAbort
         */
        void setFlags(uint8_t flags);
        /**
         * getData : get the authentication method specific data
         *
         * @return the data
         */
        FixedLengthString* getData();
        /**
         * getUserMsg : get the response user msg
         *
         * @return userMsg
         */
        FixedLengthString* getUserMsg();
        /**
         * get size : return the size of the packet
         *
         * @return size of the packet
         */
        virtual size_t getSize();
        /**
         * getType : get an unique string that describe the type of pack
et decoded
         * @return the correspoding unique indentifier string
         */
        virtual inline std::string getType()
        {
            return std::string("auth-continue");
        }
    protected:
        /**       
         * decode : decode a portion of network packet and generate
         * the corresponding TacacsPacketAuthenticationContinue instance
         *
         * @param[in] buff buffer where data are located
         */
        virtual void decode(Buffer& rbuff);
        /**
         * processEncode : encode a portion of a network packet from
         * the corresponding TacacsPacketAuthenticationContinue instance
         *
         * @param[out] wbuff buffer where the packet will be filled
         */
        virtual void processEncode(Buffer& wbuff);
    private:
        FixedLengthString* userMsg;
        FixedLengthString* data;
        uint8_t flags;
};
#endif
