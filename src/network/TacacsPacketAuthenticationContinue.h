#ifndef TACACSPACKETAUTHENTICATIONCONTINUE_H
#define TACACSPACKETAUTHENTICATIONCONTINUE_H
#include "TacacsPacketWithHeader.h"
#include "FixedLengthString.h"
#include "enum.h"

struct AuthenticationContinueFlags
{
    enum_mbr NoFlags = 0;
    enum_mbr ContinueAbort = 1;
};

class TacacsPacketAuthenticationContinue : public TacacsPacketWithHeader
{
    public:
        /**
         * create a TacacsPacketAuthenticationContinue packet
         * @param[in] userMsg response of the server msg
         * @param[in] data specific data depending on the choose
         *            authentication method
         */
        TacacsPacketAuthenticationContinue(FixedLengthString* userMsg,
            FixedLengthString* data, uint8_t flags);
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
         * encode : encode a portion of a network packet from
         * the corresponding TacacsPacketAuthenticationContinue instance
         *
         * @param[out] wbuff buffer where the packet will be filled
         */
        virtual void encode(Buffer& wbuff);
        /**       
         * decode : decode a portion of network packet and generate
         * the corresponding TacacsPacketAuthenticationContinue instance
         *
         * @param[in] buff buffer where data are located
         */
        static TacacsPacketAuthenticationContinue* decode(Buffer& rbuff);
        /**
         * getType : get an unique string that describe the type of pack
et decoded
         * @return the correspoding unique indentifier string
         */
        virtual inline std::string getType()
        {
            return std::string("auth-continue");
        }

    private:
        FixedLengthString* userMsg;
        FixedLengthString* data;
        uint8_t flags;
};
#endif
