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

#ifndef BOOST_SYNCHO_LOCKABLE_UNLOCK_HPP
#define BOOST_SYNCHO_LOCKABLE_UNLOCK_HPP

#include <assert.h>
#include <boost/synchro/call_context.hpp>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

namespace boost { namespace synchro {

    template< typename Lockable >
    inline void unlock(Lockable& lockable BOOST_STM_CALL_CONTEXT_2_PARAMS()) {
        try {
        lockable.unlock();
        } catch (...) {
            assert(false && "synchro::unlock exception");
        }
    }

}}
#endif // BOOST_SYNCHO_LOCKABLE_UNLOCK_HPP


