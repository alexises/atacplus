#ifndef DATEFORMATTER_H
#define DATEFORMATTER_H
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/utility/value_ref.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class DateFormatter
{
    public:
        typedef void result_type;
        DateFormatter(std::string const& formatString);
        void operator() (boost::log::formatting_ostream& strm, boost::log::value_ref<boost::posix_time::ptime> const& value) const; 

    private:
        std::string format;
};
#endif
