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
         * affect new value to the configuration element
         * @param[in] value value to set
         */
        void operator=(const char* value);
        void operator=(const std::string& value);

        /**
         * is valid : check if config element is valid
         */
        bool isValid();

        /**
         * get value of the config
         * 
         * @return value, the string has "" value is no parameter is set
         */
         std::string get();

    private:
        std::string name;
        std::string value;
        bool required;
};

#endif
