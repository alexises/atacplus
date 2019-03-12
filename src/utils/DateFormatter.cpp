#include "DateFormatter.h"

DateFormatter::DateFormatter(std::string const& formatString)
{
    if (formatString == "")
    {
        format = "%Y-%m-%d %H:%M:%S";
    }
    else
    {
        format = formatString;
    }
}

void DateFormatter::operator() (boost::log::formatting_ostream& strm, boost::log::value_ref<boost::posix_time::ptime> const& value) const
{
    if (value)
    {
        boost::posix_time::ptime const& p = value.get();
        std::tm t = boost::posix_time::to_tm(p);

        char buf[128];
        std::size_t len = std::strftime(buf, sizeof(buf), this->format.c_str(), &t);
        buf[len] = '\0';

        strm << buf;
    }
}

