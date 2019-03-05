#ifndef LOG_H
#define LOG_H

#include <string>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/mutable_constant.hpp>

std::string path_to_filename(std::string path);

template<typename ValueType> ValueType set_get_attrib(const char* name, ValueType value) 
{
    boost::log::attributes::mutable_constant<ValueType> attr =
        boost::log::attribute_cast<boost::log::attributes::mutable_constant<ValueType> >(
            boost::log::core::get()->get_global_attributes()[name]
        );
    attr.set(value);
    return attr.get();
}

#define LOG_MSG(sev) \
    BOOST_LOG_STREAM_WITH_PARAMS( \
        (::boost::log::trivial::logger::get()), \
         (set_get_attrib("File", path_to_filename(__FILE__))) \
         (set_get_attrib("Line", __LINE__)) \
         (::boost::log::keywords::severity = (boost::log::trivial::sev)) \
    )

#endif
