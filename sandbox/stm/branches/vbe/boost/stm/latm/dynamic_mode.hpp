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

#ifndef BOOST_STM_LATM_DYNAMIC__HPP
#define BOOST_STM_LATM_DYNAMIC__HPP

#include <boost/stm/detail/config.hpp>
#include <boost/stm/latm/datatypes.hpp>
#include <boost/stm/latm/base_mode.hpp>
#include <boost/stm/latm/abstract_mode.hpp>
#include <boost/stm/latm/full_mode.hpp>
#include <boost/stm/latm/tm_mode.hpp>
#include <boost/stm/latm/tx_mode.hpp>

namespace boost { namespace stm { namespace latm {
    typedef base_mode<abstract_mode> latm_mode;
    struct mode {
        static full_mode<abstract_mode> full_;
        static tm_mode<abstract_mode> tm_;
        static tx_mode<abstract_mode> tx_;
        static latm_mode* instance_;      
    };
    inline void do_full_lock_protection() {
        mode::instance_ = &mode::full_;
    }
    inline void do_tm_lock_protection() {
        mode::instance_ = &mode::tm_;
    }
    inline void do_tx_lock_protection() {
        mode::instance_ = &mode::tx_;
    }
    inline latm_mode& instance() {
        return *mode::instance_;
    }
    
    
}}}

#endif // BOOST_STM_LATM_DYNAMIC__HPP


