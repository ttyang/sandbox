// formatter_time.hpp

// Boost Logging library
//
// Author: John Torjo, www.torjo.com
//
// Copyright (C) 2007 John Torjo (see www.torjo.com for email)
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.
// See http://www.torjo.com/log2/ for more details


#ifndef JT28092007_formatter_time_HPP_DEFINED
#define JT28092007_formatter_time_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/logging/detail/fwd.hpp>
#include <boost/logging/format/formatter/convert_format.hpp>
#include <boost/logging/detail/manipulator.hpp> // is_generic
#include <stdio.h>
#include <time.h>

namespace boost { namespace logging { namespace formatter {

/**
@brief Prefixes the message with the time. You pass the format string at construction.

It's friendlier than write_time_strf (which uses strftime).

The format can contain escape sequences:
$dd - day, 2 digits
$MM - month, 2 digits
$yy - year, 2 digits
$yyyy - year, 4 digits
$hh - hour, 2 digits
$mm - minute, 2 digits
$ss - second, 2 digits

Example: time("Today is $dd/$MM/$yyyy");

@param convert [optional] In case there needs to be a conversion between std::(w)string and the string that holds your logged message. See convert_format.
For instance, you might use @ref boost::logging::optimize::cache_string_one_str "a cached_string class" (see @ref boost::logging::optimize "optimize namespace").
*/
template<class convert = do_convert_format::prepend> struct time_t : is_generic {
private:

    struct index_info {
        typedef hold_string_type::size_type uint;
        
        index_info(uint src_idx, int *format_idx, int size = 2) : src_idx(src_idx), format_idx(format_idx), size(size) {}
        uint src_idx;
        int * format_idx;
        int size;

        static bool by_index(const index_info & first, const index_info & second) {
            return first.src_idx < second.src_idx;
        }
    };

public:

    /** 
        constructs a time object
    */
    time_t(const hold_string_type & format) : m_day(-1), m_month(-1), m_yy(-1), m_yyyy(-1), m_hour(-1), m_min(-1), m_sec(-1) {
        // format too big
        assert( format.size() < 64);

        typedef hold_string_type::size_type uint;
        uint day_idx    = format.find(BOOST_LOGGING_STR("$dd"));
        uint month_idx  = format.find(BOOST_LOGGING_STR("$MM"));
        uint yy_idx     = format.find(BOOST_LOGGING_STR("$yy"));
        uint yyyy_idx   = format.find(BOOST_LOGGING_STR("$yyyy"));
        uint hour_idx   = format.find(BOOST_LOGGING_STR("$hh"));
        uint min_idx    = format.find(BOOST_LOGGING_STR("$mm"));
        uint sec_idx    = format.find(BOOST_LOGGING_STR("$ss"));

        typedef std::vector<index_info> array;
        array indexes;
        if ( day_idx != hold_string_type::npos)
            indexes.push_back( index_info(day_idx, &m_day) );
        if ( month_idx != hold_string_type::npos)
            indexes.push_back( index_info(month_idx, &m_month) );

        if ( yy_idx != hold_string_type::npos || yyyy_idx != hold_string_type::npos) {
            if ( yyyy_idx  != hold_string_type::npos)
                indexes.push_back( index_info(yyyy_idx, &m_yyyy, 4) );
            else
                indexes.push_back( index_info(yy_idx, &m_yy) );
        }

        if ( hour_idx != hold_string_type::npos)
            indexes.push_back( index_info(hour_idx, &m_hour ) );
        if ( min_idx != hold_string_type::npos)
            indexes.push_back( index_info(min_idx, &m_min) );
        if ( sec_idx != hold_string_type::npos)
            indexes.push_back( index_info(sec_idx, &m_sec) );
        std::sort( indexes.begin(), indexes.end(), index_info::by_index);
        
        // create the format string, that we can actually pass to sprintf 
        uint prev_idx = 0;
        int idx = 0;
        for ( typename array::iterator begin = indexes.begin(), end = indexes.end(); begin != end; ++begin) {
            m_format += format.substr( prev_idx, begin->src_idx - prev_idx);
            *begin->format_idx = idx;
            m_format += (begin->size == 4) ? BOOST_LOGGING_STR("%04d") : BOOST_LOGGING_STR("%02d");
            prev_idx = begin->src_idx + begin->size + 1;
            ++idx;
        }

        m_format += format.substr(prev_idx);
    }




    template<class msg_type> void operator()(msg_type & msg) const {
        char_type buffer[64];

        ::time_t t = ::time(0); 
        tm details = *localtime( &t);

        int vals[8];
        vals[m_day + 1]      = details.tm_mday;
        vals[m_month + 1]    = details.tm_mon + 1; // many thanks to Matthew P. Cashdollar
        vals[m_yy + 1]       = details.tm_year % 100; // many thanks to Andy Schweitzer
        vals[m_yyyy + 1]     = details.tm_year + 1900;
        vals[m_hour + 1]     = details.tm_hour;
        vals[m_min + 1]      = details.tm_min;
        vals[m_sec + 1]      = details.tm_sec;
      
        // ignore value at index 0 - it's there so that I don't have to test for an index being -1
    #ifdef UNICODE
        swprintf( buffer, m_format.c_str(), vals[1], vals[2], vals[3], vals[4], vals[5], vals[6], vals[7] );
    #else
        sprintf( buffer, m_format.c_str(), vals[1], vals[2], vals[3], vals[4], vals[5], vals[6], vals[7] );
    #endif

        convert::write(buffer, msg);
    }

    bool operator==(const time_t & other) const {
        return m_format == other.m_format;
    }

private:
    // the indexes of each escape sequence within the format string
    int m_day, m_month, m_yy, m_yyyy, m_hour, m_min, m_sec;
    hold_string_type m_format;
};


/**
@brief Prefixes the message with the time, by using strftime function. You pass the format string at construction.

@param msg_type The type that holds your logged message.

@param convert [optional] In case there needs to be a conversion between std::(w)string and the string that holds your logged message. See convert_format.
For instance, you might use @ref boost::logging::optimize::cache_string_one_str "a cached_string class" (see @ref boost::logging::optimize "optimize namespace").
*/
template<class convert = do_convert_format::prepend> struct time_strf_t : is_generic {

    /** 
        constructs a time_strf object

        @param format the time format , strftime-like
        @param localtime if true, use localtime, otherwise global time
    */
    time_strf_t(const hold_string_type & format, bool localtime)
        : m_format (format), m_localtime (localtime)
    {}

    template<class msg_type> void operator()(msg_type & msg) const {
        char_type buffer[64];
        ::time_t t = ::time (0); 
        ::tm t_details = m_localtime ? *localtime( &t) : *gmtime( &t);
    #ifdef UNICODE
        if (0 != wcsftime (buffer, sizeof (buffer), m_format.c_str (), &t_details))
    #else
        if (0 != strftime (buffer, sizeof (buffer), m_format.c_str (), &t_details))
    #endif
            convert::write(buffer, msg);
    }

    bool operator==(const time_strf_t & other) const {
        return m_format == other.m_format;
    }

private:
    hold_string_type m_format;
    bool m_localtime;

};


typedef time_t<> time;
typedef time_strf_t<> time_strf;

}}}

#endif

