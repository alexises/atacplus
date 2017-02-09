#ifndef CRYPTO_H
#define CRYPTO_H

#include <cstdint>
/**
 * encodeTacacasPacket : encode/decode the tacacs packet payload 
 *
 * @param[in] buff buffer to decode/encode
 * @param[in] size size of the buffer
 * @param[in] key used key to decode/encode, it's a null terminated string
 * @param[in] sessionId sessionId from the header
 * @param[in] version version from the header
 * @param[in] seqNo from the header
 *
 * @return encoded payload, the client is responsable to free the
 * resulting packet
 */
unsigned char* encodeTacacsPacket(const unsigned char * buff, int size, char* key, uint32_t sessionId, uint8_t version, uint8_t seqNo);

#endif
