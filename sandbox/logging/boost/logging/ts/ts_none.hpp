// defs.hpp

// Boost Logging library
//
// Author: John Torjo, www.torjo.com
//
// Copyright (C) 2007 John Torjo (see www.torjo.com for email)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
 
// See http://www.boost.org for updates, documentation, and revision history.
// See http://www.torjo.com/log2/ for more details

#ifndef JT_BOOST_LOG_TS_NONE_HPP
#define JT_BOOST_LOG_TS_NONE_HPP


#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


namespace boost { namespace logging {

namespace threading {
    // no threads
    struct no_mutex ;

    struct no_lock {
        no_lock(no_mutex &) {}
    };

    struct no_mutex {
        typedef no_lock scoped_lock;
        void Lock() {}
        void Unlock() {}
    };


}

}}


#endif

