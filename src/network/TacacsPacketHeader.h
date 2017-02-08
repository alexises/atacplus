#ifndef TACACSPACKETHEADER_H
#define TACACSPACKETHEADER_H
#include <cstdint>
#include "TacacsPacketInterface.h"

#define TACACS_PACKET_HEADER_SIZE 12
enum TacacsPacketType {
	Authentication = 1,
	Authorization = 2,
	Accounting = 3
};
enum TacacsPacketFlags {
	NoFlags = 0,
	Unencrypted = 1
};
class TacacsPacketHeader : public TacacsPacketInterface
{
	public:
		TacacsPacketHeader(const uint8_t version,
                	const uint8_t type,
                	const uint8_t seqNo,
                	const uint8_t flags,
                	const uint32_t sessionId,
                	const uint32_t length);

		/**
                 * encode : encode a portion of a network packet from
                 * the corresponding TacacsPacketHeader instance
                 *
                 * @param[out] payload buffer where the packet will be filled
                 * @param[in] size size of the buffer
                 * @return size of encoded packet
                 */
		virtual int encode(char* payload, const int size);
		/**
                 * decode : decode a portion of network packet and generate
                 * the corresponding TacacsPacketHeader instance
                 *
                 * @param[in] payload packet part to decode
                 * @param[in] size size of the payload
                 * @return the corresponding TacacsPacketInterface instance
                 */
                static TacacsPacketHeader* decode(const char* payload, int size);
		/**
                 * getType : get an unique string that describe the type of pack
et decoded
                 * @return the correspoding unique indentifier string
                 */
                virtual inline std::string getType()
		{
			return std::string("header");
		}
		 /**
                 * getSize : get the size of the corresponding part of the packe
t
                 * @return size of the packet
                 *
                 * this function should be used to allocate the proper buffer
                 * to decode the corresponding package
                 */
                virtual inline int getSize()
		{
			return TACACS_PACKET_HEADER_SIZE;
		}
		/**
		 * getMajorVersion : get the major tacacs version of the packet
		 *
		 * @return major version
		 */
		virtual int getMajorVersion();
		/**
		 * getMinorVersion : get the minor tacacs version of the packet
		 *
		 * @return minor version
		 */
		virtual int getMinorVersion();
		/**
		 * getPacketType : get the type of packet (Authentication, Authorization, Accouinting
		 *
		 * @return TacacsPacketType::Authentication,
		 *         TacacsPacketType::Authorization,
		 *         TacacsPacketType::Accounting
		 */
		virtual uint8_t getPacketType(); 
		/**
		 * getSeqNo : get the sequence id of the packet
		 *
		 * @return sequence No
		 */
		virtual uint8_t getSeqNo();
		/**
		 * getFlags : return the related flags of the packets
		 *
		 * the flags is a bitwise field of TacacsPacketFlags
		 * @return flags of the packet
		 */
		virtual uint8_t getFlags();
		/**
		 * getSessionId : get the session id 
		 *
		 * @return session id
		 */
		virtual uint32_t getSessionId();
		/**
		 * getLength : get the length of the packet
		 *
		 * @return length of the packet
		 */
		virtual uint32_t getLength();
	private:
		// packet attribute
		uint8_t version;
		uint8_t type;
		uint8_t seqNo;
		uint8_t flags;
		uint32_t sessionId;
		uint32_t length;
		// decoding attributes
		std::string key;
};

#endif
