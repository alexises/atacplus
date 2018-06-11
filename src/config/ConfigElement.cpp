#include "ConfigElement.h"

ConfigElement::ConfigElement(std::string name, std::string defaultValue, bool required) : name(name), value(defaultValue)
{
    this->required = required;
}

ConfigElement::ConfigElement(const char* name, const char* defaultValue, bool required) : name(std::string(name)), value(std::string(defaultValue))
{
    this->required = required;
}

bool ConfigElement::isValid()
{
    return !this->required || this->value != "";
}

void ConfigElement::operator=(const char* value)
{
    this->value = std::string(value);
}

void ConfigElement::operator=(const std::string& value)
{
    this->value = value;
}

std::string ConfigElement::get()
{
    return this->value;
}
