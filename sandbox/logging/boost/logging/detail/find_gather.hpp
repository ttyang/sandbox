// find_gather.hpp

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


#ifndef JT28092007_find_gather_HPP_DEFINED
#define JT28092007_find_gather_HPP_DEFINED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/logging/detail/fwd.hpp>

namespace boost { namespace logging {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // specialize logger for format_write class
    //
    template<
            class string_ ,
            class param1 ,
            class param2 ,
            class param3 ,
            class param4 ,
            class param5 ,
            class param6 ,
            class param7 ,
            class param8 ,
            class param9 ,
            class param10> struct tag_holder ;

    namespace gather { namespace ostream_like {
        template<class, class> struct return_str ;
        template<class holder_type, class stream_type> struct return_tag_holder ;
    }}

    namespace optimize {
        template<class> struct cache_string_one_str ;
        template<class, class> struct cache_string_several_str ;
    }

    namespace detail {
        template<class param> struct find_gather {};
        template<> struct find_gather< std::basic_string<char_type> > { typedef gather::ostream_like::return_str< std::basic_string<char_type>, std::basic_ostringstream<char_type> > type ; };

        template< class string_type> 
        struct find_gather< boost::logging::optimize::cache_string_one_str<string_type> > { 
            typedef gather::ostream_like::return_str< boost::logging::optimize::cache_string_one_str<string_type>, std::basic_ostringstream<char_type> > type;
        };

        template< class string_type> 
        struct find_gather< boost::logging::optimize::cache_string_several_str<string_type,void*> > { 
            typedef gather::ostream_like::return_str< boost::logging::optimize::cache_string_several_str<string_type,void*>, std::basic_ostringstream<char_type> > type;
        };


        template<class string, class p1, class p2, class p3, class p4, class p5, class p6, class p7, class p8, class p9, class p10>
        struct find_gather< tag_holder<string,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10> > {
            typedef gather::ostream_like::return_tag_holder< tag_holder<string,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10> , std::basic_ostringstream<char_type> > type;
        };
    }

}}

#endif

