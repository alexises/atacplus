#ifndef CRYPTO_H
#define CRYPTO_H
#include "Buffer.h"
#include "FixedLengthString.h"
#include <stdint.h>
/**
 * encodeTacacasPacket : encode/decode the tacacs packet payload 
 *
 * @param[in] buff buffer to decode/encode
 * @param[in] size size of the payload
 * @param[in] key used key to decode/encode, it's a null terminated string
 * @param[in] sessionId sessionId from the header
 * @param[in] version version from the header
 * @param[in] seqNo from the header
 * @param[in] offset offset from the buffer object where begin to decipher
 * @pre buff->availableRead() >= (size + offset)
 */
void encodeTacacsPacket(Buffer& buff, size_t size, FixedLengthString* key, uint32_t sessionId, uint8_t version, uint8_t seqNo, size_t offset = 0);

#endif
