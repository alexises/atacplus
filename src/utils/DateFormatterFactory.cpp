#include "DateFormatterFactory.h"
#include <boost/phoenix.hpp>

#include "boost/log/trivial.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/utility/setup.hpp"
#include "boost/log/support/date_time.hpp"

boost::log::formatter_factory<char>::formatter_type DateFormatterFactory::create_formatter(boost::log::attribute_name const& name, boost::log::formatter_factory<char>::args_map const& args)
{
    boost::log::formatter_factory<char>::args_map::const_iterator it = args.find("format");
    if (it != args.end())
    {
        return boost::phoenix::bind(
            DateFormatter(it->second), 
            boost::log::expressions::stream, 
            boost::log::expressions::attr<boost::posix_time::ptime>(name));
    }
    else
    {
        return boost::phoenix::bind(
            DateFormatter(std::string("")),
            boost::log::expressions::stream, 
            boost::log::expressions::attr<boost::posix_time::ptime>(name));
    }
}

