#ifndef CONFIGSECTION
#define CONFIGSECTION
#include <string>
#include <map>
#include "ConfigElement.h"


class ConfigSection {
    protected:
        ConfigSection(char* sectionName);
        ~ConfigSection();

        /**
         * setAttr : add new attribute on the configuration section
         *
         * @param[in] name name of config element
         * @param[in] defaultValue default value if parameter is not set
         * @param[in] required set if parameter is required
         */
        void setAttr(const char* name, const char* defaultValue, bool required);
        /**
         * get configelement from configuration
         *
         * @param[in] name of the config element
         * @return the config element associated with the key
         *
         * due to the presence of = operator overload on ConfigElement, this is allow
         * the usage of section["mykey"] = "newvalue" syntax;
         */
        ConfigElement& operator[](const char* name);

    private:
        std::string sectionName;
        std::map<std::string, ConfigElement*> configElements;
};

#endif
