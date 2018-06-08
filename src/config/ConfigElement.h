#ifndef CONFIGELEMENT_H
#define CONFIGELEMENT_H
#include <string>

/**
 * ConfigElment : store configuration entry with default value
 */
class ConfigElement
{
    public:
        /**
         * @param[in] name name of the config element
         * @param[in] defaultValue default value for the config, empty string should be provided if no default value is provided
         * @param[in] required set if the config element is required
         */
        ConfigElement(std::string name, std::string defaultValue, bool required);
        ConfigElement(const char* name, const char* defaultValue, bool required);

        /**
         * is valid : check if config element is valid
         */
        bool isValid();

    private:
        std::string name;
        std::string value;
        bool required;
};

#endif
