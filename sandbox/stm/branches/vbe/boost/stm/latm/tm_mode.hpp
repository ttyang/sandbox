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

#ifndef BOOST_STM_LATM_TM_MIXIN__HPP
#define BOOST_STM_LATM_TM_MIXIN__HPP

#include <boost/stm/detail/config.hpp>
#include <boost/stm/latm/datatypes.hpp>
#include <boost/stm/latm/base_mode.hpp>

//-----------------------------------------------------------------------------
namespace boost { namespace stm { namespace latm {

//-----------------------------------------------------------------------------
template <typename Base=static_mode>
class tm_mode : public base_mode<Base>  {
public:
    ~tm_mode() {}
    
    latm_type const protection() { return eTmConflictingLockLatmProtection; }
    std::string const protection_str() {
        return "tm_protect";
    }

    bool doing_full_lock_protection() {
        return false;
    }
    bool doing_tm_lock_protection() {
        return true;
    }
    bool doing_tx_lock_protection() {
        return false;
    }

//-----------------------------------------------------------------------------
    bool can_go_inflight()
    {
        // allow transactions
        // to start only if
        for (latm::mutex_set::iterator i = this->tmConflictingLocks_.begin(); i != this->tmConflictingLocks_.end(); ++i)
        {
            // if one of your conflicting locks is currently locked ...
            if (this->latmLockedLocks_.end() != this->latmLockedLocks_.find(*i))
            {
                // if it is locked by our thread, it is ok ... otherwise it is not
                latm::mutex_thread_id_map::iterator j = this->latmLockedLocksOfThreadMap_.find(*i);

                if (j != this->latmLockedLocksOfThreadMap_.end() &&
                   this_thread::get_id() != j->second)
                {
                   return false;
                }
            }
        }

        return true;
    }

//-----------------------------------------------------------------------------
    void tm_lock_conflict(latm::mutex_type &lock)
    {
        tm_lock_conflict(&lock);
    }
    void tm_lock_conflict(latm::mutex_type* inLock)
    {
        synchro::lock_guard<Mutex> lock_l(this->latmMutex_);

       //-------------------------------------------------------------------------
       // insert can throw an exception
       //-------------------------------------------------------------------------
        this->tmConflictingLocks_.insert(inLock);
    }

};

}}}

#endif // BOOST_STM_LATM_TM_MIXIN__HPP


