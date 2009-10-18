//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Justin E. Gottchlich 2009.
// (C) Copyright Vicente J. Botet Escriba 2009.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/stm for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_SYNCHO_TIME_HPP
#define BOOST_SYNCHO_TIME_HPP

//-----------------------------------------------------------------------------
#include <boost/thread/thread_time.hpp>
#include <boost/thread/pthread/timespec.hpp>
//-----------------------------------------------------------------------------

namespace boost { namespace synchro {

    using boost::system_time;
    
    inline system_time get_system_time() {
        return boost::get_system_time();
    }
    
    namespace detail {
        inline struct timespec const get_timespec(system_time& t) {
            return boost::detail::get_timespec(t);
        }
    }

}}
#endif // BOOST_SYNCHO_TRY_LOCK_HPP


