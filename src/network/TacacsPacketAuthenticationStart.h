#ifndef TACACSPACKETAUTHENTICATIONSTART_H
#define TACACSPACKETAUTHENTICATIONSTART_H
#include "TacacsPacketInterface.h"
#include "enum.h"
#include "FixedLengthString.h"
#include "Buffer.h"
#include <stdint.h>

struct TacacsAuthenticationAction {
    enum_mbr Login = 1;
    enum_mbr ChangePassword = 2;
    enum_mbr SendPassword = 3;
    enum_mbr SendAuth = 4;
};

#define TACACS_MIN_PRIV_LVL 0
#define TACACS_MAX_PRIX_LVL 15

struct TacacsAuthenticationType {
    enum_mbr Ascii = 1;
    enum_mbr Pap = 2;
    enum_mbr Chap = 3;
    enum_mbr Arap = 4;
    enum_mbr mschap = 5;
};

struct TacacsAuthenticationService {
    enum_mbr None = 0;
    enum_mbr Login = 1;
    enum_mbr Enable = 2;
    enum_mbr Ppp = 3;
    enum_mbr Arap = 4;
    enum_mbr Pt = 5;
    enum_mbr Rcmd = 6;
    enum_mbr X25 = 7;
    enum_mbr Nasi = 8;
    enum_mbr FwProxy = 9;
};

class TacacsPacketAuthenticationStart : public TacacsPacketInterface
{
    public:
        /**
         * construct a TacacsPacketAuthenticationStart object
         *
         * @param[in] action action to be run to authenticate the user
         * @param[in] privLvl request privilege level for the action
         * @param[in] authenType authentication type used to perform the authentication
         * @param[in] service service for wich the authentication is requested
         * @param[in] user username for this authentication methode
         * @param[in] port pseudo therminal used for this authentication request
         * @param[in] remoteAddr remote addresse used by the user for this authentication request
         * @param[in] data data needed to perform the authentication
         */
        TacacsPacketAuthenticationStart(
            const uint8_t action,
            const uint8_t privLvl,
            const uint8_t authenType,
            const uint8_t service,
            FixedLengthString* user,
            FixedLengthString* port,
            FixedLengthString* remoteAddr,
            FixedLengthString* data);
        virtual ~TacacsPacketAuthenticationStart();
        /**
         * encode : encode a portion of a network packet from
         * the corresponding TacacsPacketAuthenticationStart instance
         *
         * @param[out] payload buffer where the packet will be filled
         * @param[in] size size of the buffer
         * @return size of encoded packet
         */
        virtual int encode(unsigned char* payload, const int size);
        /**       
         * decode : decode a portion of network packet and generate
         * the corresponding TacacsPacketHeader instance
         *
         * @param[in] buff buffer where data are located
         */
        static TacacsPacketAuthenticationStart* decode(Buffer& rbuff);
        /**
         * getType : get an unique string that describe the type of pack
et decoded
         * @return the correspoding unique indentifier string
         */
        virtual inline std::string getType()
        {
            return std::string("auth-start");
        }
        /**
         * get size : return the size of the packet
         *
         * @return size of the packet
         */
        virtual int getSize();
    private:
        uint8_t action;
        uint8_t privLvl;
        uint8_t authenType;
        uint8_t service;
        FixedLengthString* user;
        FixedLengthString* port;
        FixedLengthString* remoteAddr;
        FixedLengthString* data;

};

#endif
