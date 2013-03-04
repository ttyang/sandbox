
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_AUX_THREAD_VARIABLE_HPP_
#define BOOST_CONTRACT_AUX_THREAD_VARIABLE_HPP_

#include <boost/contract/aux_/config.hpp>

#if BOOST_CONTRACT_AUX_CONFIG_THREAD_SAFE_01
#   include <boost/thread/recursive_mutex.hpp> // Required only if thread safe.
#endif

namespace boost { namespace contract { namespace aux {

template< typename T >
class thread_variable
{
    public: /* implicit */ thread_variable ( T const& value ) : value_(value) {}
    
    // Default T() required only if this is actually used.
    public: thread_variable ( void ) : value_(T()) {}

    // Set //

    // Sync so cannot return object&.
    public: void operator= ( T const& value )
    {
#if BOOST_CONTRACT_AUX_CONFIG_THREAD_SAFE_01
        boost::recursive_mutex::scoped_lock lock(mutex_);
#endif
        value_ = value;
    } // Release eventual lock.
    
    // Sync so cannot return object&.
    public: void operator= ( T const& value ) volatile
    {
#if BOOST_CONTRACT_AUX_CONFIG_THREAD_SAFE_01
        boost::recursive_mutex::scoped_lock lock(mutex_);
#endif
        value_ = value;
    } // Release eventual lock.

    // Get //
    
    // Sync so must return object copy (by value).
    public: operator T ( void ) const
    {
#if BOOST_CONTRACT_AUX_CONFIG_THREAD_SAFE_01
        boost::recursive_mutex::scoped_lock lock(mutex_);
#endif
        return value_;
    } // Release eventual lock.
    
    // Sync so must return object copy (by value).
    public: operator T ( void ) const volatile
    {
#if BOOST_CONTRACT_AUX_CONFIG_THREAD_SAFE_01
        boost::recursive_mutex::scoped_lock lock(mutex_);
#endif
        return value_;
    } // Release eventual lock.

    private: T value_;

#if BOOST_CONTRACT_AUX_CONFIG_THREAD_SAFE_01
    private: mutable boost::recursive_mutex mutex_;
#endif
};

} } } // namespace

#endif // #include guard

