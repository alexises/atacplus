#ifndef TACACSPACKETINTERFACE_H
#define TACACSPACKETINTERFACE_H
#include <string>

class TacacsPacketInterface
{
	public:
		/**
		 * encode : encode a portion of a network packet from
		 * the corresponding TacacsPacketInterface instance
		 *
		 * @param[out] payload buffer where the packet will be filled
		 * @param[in] size size of the buffer
		 * @return size of encoded packet
		 */
		virtual int encode(char* payload, const int size) = 0;
		/**
		 * decode : decode a portion of network packet and generate
		 * the corresponding TacacsPacketInterface instance
		 *
		 * @param[in] payload packet part to decode
		 * @param[in] size size of the payload
		 * @return the corresponding TacacsPacketInterface instance
		 */
		static virtual TacacsPacketInterface* decode(const char* paylod, int size) = 0;
		/**
		 * getType : get an unique string that describe the type of packet decoded
		 * @return the correspoding unique indentifier string
		 */
		static virtual std::string getType() = 0;
		/**
		 * getSize : get the size of the corresponding part of the packet
		 * @return size of the packet
		 * 
		 * this function should be used to allocate the proper buffer
		 * to decode the corresponding package
		 */
		virtual inline int getSize()
		{
			return 12;
		}
}

#endif
