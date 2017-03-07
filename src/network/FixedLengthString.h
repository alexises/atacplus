#ifndef FIXEDLENGTHSTRING_H
#define FIXEDLENGTHSTRING_H
#include <string>
#include <stdint.h>

/**
 * FixedLengthString : Store a string of a fixed size without null termination
 */
class FixedLengthString
{
    public:
	/**
	 * set a string by his length and value
	 * @param[in] size size of the string
	 * @param[in] value string of the size size
	 */ 
        FixedLengthString(const char* value, size_t size);
        /**
         * create an empty string
         * @param[în] size size of the string
         */
        FixedLengthString(size_t size);
	/**
	 * copy constructor
	 * @param[in] other instance to copy
	 */
	FixedLengthString(FixedLengthString & other);
	/**
	 * getString get the raw string
	 * @return raw string (non null terminated, of size getSize())
	 */
	const char* getString();
	/**
	 * getSize get the size of the string returned by getString()
	 * @return size of string
	 */
	size_t getSize();
	/**
	 * copy and convert this object to a standard string
	 */
	std::string toString();
	/**
	 * access and modify an item of the string 
	 * @param[in] index index of the string
	 * @return reference to the selected index
	 * @pre index > 0 && index < this->getLength()
	 */
	char& operator[](size_t index);
        /**
         * Compare two fixed length string for equality
         *
         * @param[in] other other element to compare
         * @return true if string are equal false otherwise
         */
        bool operator==(FixedLengthString& other);
	/**
	 * destructor
	 */
	virtual ~FixedLengthString();
    private:
	size_t size;
	char* value;
};
#endif
