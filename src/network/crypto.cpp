#include "crypto.h"
#include "precondition.h"
#include "macro.h"
#include <cstring>
#include <openssl/md5.h>

/**
 * create the clear message used for the first row algorithm
 *
 * @param[out] pointer where to store the dynamicaly allocated buffer
 * @param[in] key shared key
 * @param[in] sessionId sessionId present on the packet header
 * @param[in] version version present on the packet header
 * @param[in] seqNo sequence index present on the packet header
 * @return the size of the resulting buffer, the buffer allocated into buff provided the needed extra space
 *   to launch all round of the algorithm and set the md5 key
 */
static int createMD5message(uint8_t** buff, FixedLengthString* key, uint32_t sessionId, uint8_t version, uint8_t seqNo)
{
    int keySize = key->getSize();
    int firstRoundSize = keySize + sizeof(sessionId) + sizeof(version) + sizeof(seqNo); 
    uint8_t* md5ClearBuffer = new uint8_t[firstRoundSize + MD5_DIGEST_LENGTH];
    int currIdx = 0;

    memcpy(&md5ClearBuffer[currIdx], &sessionId, sizeof(sessionId));
    currIdx += sizeof(sessionId);
    memcpy(&md5ClearBuffer[sizeof(sessionId)], key, keySize);
    currIdx += keySize;
    md5ClearBuffer[currIdx++] = version; // avoid a new line, post increment is well understand
    md5ClearBuffer[currIdx] = seqNo;

    *buff = md5ClearBuffer;
    return firstRoundSize;
}

void encodeTacacsPacket(Buffer& buff, size_t size, FixedLengthString* key, uint32_t sessionId, uint8_t version, uint8_t seqNo, size_t offset)
{
    precondition(buff.availableRead() >= (size + offset));
    uint8_t md5EncipheredBuffer[MD5_DIGEST_LENGTH];
    uint8_t* md5ClearBuffer;
    int prevMD5pos = createMD5message(&md5ClearBuffer, key, sessionId, version, seqNo);
    int md5ClearBufferSize = prevMD5pos;

    for (size_t chunk = 0; chunk < size; chunk += MD5_DIGEST_LENGTH)
    {
        MD5(md5ClearBuffer, md5ClearBufferSize, md5EncipheredBuffer);
        for (int i = 0; i < MD5_DIGEST_LENGTH && (chunk + i) < size; ++i)
	{
	    buff[chunk + i + offset] = buff[chunk + i + offset] ^ md5EncipheredBuffer[i];
	    md5ClearBuffer[prevMD5pos + i] = md5EncipheredBuffer[i];
	}
	md5ClearBufferSize = prevMD5pos + MD5_DIGEST_LENGTH;
    }
    delete[] md5ClearBuffer;
}
