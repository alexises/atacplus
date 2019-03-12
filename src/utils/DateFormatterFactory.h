#ifndef DATEFORMATTERFACTORY_H
#define DATEFORMATTERFACTORY_H
#include "DateFormatter.h"
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/attributes/attribute_name.hpp>

class DateFormatterFactory : public boost::log::basic_formatter_factory<char, boost::posix_time::ptime>
{
    public:
        boost::log::formatter_factory<char>::formatter_type create_formatter(boost::log::attribute_name const& name, boost::log::formatter_factory<char>::args_map const& args);
};
#endif 
