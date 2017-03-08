#ifndef TACACSPACKETAUTHENTICATIONSTART_H
#define TACACSPACKETAUTHENTICATIONSTART_H
#include "TacacsPacketWithHeader.h"
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
#define TACACS_MAX_PRIV_LVL 15

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

class TacacsPacketAuthenticationStart : public TacacsPacketWithHeader
{
    public:
        /**
         * construct a TacacsPacketAuthenticationStart object
         *
         * Warning : FixedLengthString object are destructed with this object,
         * you should provides instance of theses object that was allocated
         * dynamicaly !
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
         * @param[out] wbuff buffer where the packet will be filled
         */
        virtual void encode(Buffer& wbuff);
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
        virtual size_t getSize();
        /**
         * getAction : get action requested for 
         * this authentication
         *
         * @return action value
         */
        uint8_t getAction();
        /**
         * setAction : set the corresponding action of the packet
         *
         * @param[in] action action to set
         * @pre action == TacacsAuthenticationAction::Login ||
         *      action == TacacsAuthenticationAction::ChangePassword ||
         *      action == TacacsAuthenticationAction::SendPassword ||
         *      action == TacacsAuthenticationAction::SendAuth
         */
        void setAction(uint8_t action);
        /**
         * get the privilege level associated to the authentication request
         *
         * @return privilege level
         */
        uint8_t getPrivLvl();
        /**
         * set the privilege level associated to this request
         *
         * @param[in] privLvl privLvl to set
         * @pre privLvl >= TACACS_MIN_PRIV_LVL &&
         *      privLvl <= TACACS_MAX_PRIX_LVL
         */
        void setPrivLvl(uint8_t privLvl);
        /**
         * getAuthenType : get the authentication type of the 
         * packet
         *
         * @return authentication type
         */
        uint8_t getAuthenType();
        /**
         * setAuthenType : set the authentication type requested
         * for this authentication session
         *
         * @param[in] authenType authentication type of the query
         * @pre authenType == TacacsAuthenticationType::Ascii ||
         *      authenType == TacacsAuthenticationType::Pap ||
         *      authenType == TacacsAuthenticationType::Chap ||
         *      authenType == TacacsAuthenticationType::Arap ||
         *      authenType == TacacsAuthenticationType::mschap
         */
        void setAuthenType(uint8_t authenType);
        /**
         * getService get the service requested for this auth
         *
         * @return service for this authentication
         */
        uint8_t getService();
        /**
         * set service that require the authentication
         *
         * @param[in] service service to use
         * @pre service == TacacsAuthenticationService::None ||
         *      service == TacacsAuthenticationService::Login ||
         *      service == TacacsAuthenticationService::Enable ||
         *      service == TacacsAuthenticationService::Ppp ||
         *      service == TacacsAuthenticationService::Arap ||
         *      service == TacacsAuthenticationService::Pt ||
         *      service == TacacsAuthenticationService::Rcmd ||
         *      service == TacacsAuthenticationService::X25 ||
         *      service == TacacsAuthenticationService::Nasi ||
         *      service == TacacsAuthenticationService::FwProxy
         */
        void setService(uint8_t service);
        /**
         * getUser get the user string
         *
         * @return user strin
         */
        FixedLengthString* getUser();
        /**
         * getPort get the port string
         *
         * @return port string
         */
        FixedLengthString* getPort();
        /**
         * getRemoteAddr get the remote addr string
         *
         * @return remoteAddr string
         */
        FixedLengthString* getRemoteAddr();
        /**
         * getData get the data requested to perform authentication
         *
         * @return data string
         */
        FixedLengthString* getData();
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
