#include "ConfigSection.h"
#include "ConfigElementNotFoundException.h"

ConfigSection::ConfigSection(char* sectionName) : sectionName(std::string(sectionName))
{
}

ConfigSection::~ConfigSection()
{
    for(std::map<std::string, ConfigElement*>::iterator it = this->configElements.begin(); it != this->configElements.end(); it++)
    {
        delete it->second;
    }
}

void ConfigSection::setAttr(const char* name, const char* defaultValue, bool required)
{
    ConfigElement* elem = new ConfigElement(name, defaultValue, required);
    this->configElements[std::string(name)] = elem;
}

ConfigElement& ConfigSection::operator[](const char* name)
{
    ConfigElement* elem = this->configElements[std::string(name)];
    if (elem == NULL)
    {
        throw ConfigElementNotFoundException(name);
    }
    return *elem;
}
