// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// (C) Copyright 2007 Anthony Williams
// (C) Copyright 2010 Vicente J. Botet Escriba

#ifndef BOOST_SYNC_HAS_MEMBERS_HPP
#define BOOST_SYNC_HAS_MEMBERS_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost
{
    namespace sync {

#ifndef BOOST_SYNC_NO_AUTO_DETECT_TYPES
#if defined(BOOST_NO_SFINAE) ||                           \
    BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600)) || \
    BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
#define BOOST_SYNC_NO_AUTO_DETECT_TYPES
#endif
#endif

#ifndef BOOST_SYNC_NO_AUTO_DETECT_TYPES
    namespace detail
    {
#define BOOST_DEFINE_HAS_MEMBER_CALLED(member_name)                     \
        template<typename T, bool=boost::is_class<T>::value>            \
        struct has_member_called_##member_name                          \
        {                                                               \
            BOOST_STATIC_CONSTANT(bool, value=false);                   \
        };                                                              \
                                                                        \
        template<typename T>                                            \
        struct has_member_called_##member_name<T,true>                  \
        {                                                               \
            typedef char true_type;                                     \
            struct false_type                                           \
            {                                                           \
                true_type dummy[2];                                     \
            };                                                          \
                                                                        \
            struct fallback { int member_name; };                       \
            struct derived:                                             \
                T, fallback                                             \
            {                                                           \
                derived();                                              \
            };                                                          \
                                                                        \
            template<int fallback::*> struct tester;                    \
                                                                        \
            template<typename U>                                        \
                static false_type has_member(tester<&U::member_name>*); \
            template<typename U>                                        \
                static true_type has_member(...);                       \
                                                                        \
            BOOST_STATIC_CONSTANT(                                      \
                bool, value=sizeof(has_member<derived>(0))==sizeof(true_type)); \
        }

        typedef char true_type;
        struct false_type
        {
            true_type dummy[2];
        };

        BOOST_DEFINE_HAS_MEMBER_CALLED(lock);
        BOOST_DEFINE_HAS_MEMBER_CALLED(unlock);
        BOOST_DEFINE_HAS_MEMBER_CALLED(try_lock);
        BOOST_DEFINE_HAS_MEMBER_CALLED(try_lock_until);
        BOOST_DEFINE_HAS_MEMBER_CALLED(try_lock_for);

        template<typename T,bool=has_member_called_lock<T>::value >
        struct has_member_lock
        {
            BOOST_STATIC_CONSTANT(bool, value=false);
        };
        
        template<typename T>
        struct has_member_lock<T,true>
        {
            
            template<typename U,typename V>
            static true_type has_member(V (U::*)());
            template<typename U>
            static false_type has_member(U);
            
            BOOST_STATIC_CONSTANT(
                bool,value=sizeof(has_member_lock<T>::has_member(&T::lock))==sizeof(true_type));
        };
        
        template<typename T,bool=has_member_called_unlock<T>::value >
        struct has_member_unlock
        {
            BOOST_STATIC_CONSTANT(bool, value=false);
        };
        
        template<typename T>
        struct has_member_unlock<T,true>
        {
            
            template<typename U,typename V>
            static true_type has_member(V (U::*)());
            template<typename U>
            static false_type has_member(U);
            
            BOOST_STATIC_CONSTANT(
                bool,value=sizeof(has_member_unlock<T>::has_member(&T::unlock))==sizeof(true_type));
        };
        
        template<typename T,bool=has_member_called_try_lock<T>::value >
        struct has_member_try_lock
        {
            BOOST_STATIC_CONSTANT(bool, value=false);
        };
        
        template<typename T>
        struct has_member_try_lock<T,true>
        {
            
            template<typename U>
            static true_type has_member(bool (U::*)());
            template<typename U>
            static false_type has_member(U);
            
            BOOST_STATIC_CONSTANT(
                bool,value=sizeof(has_member_try_lock<T>::has_member(&T::try_lock))==sizeof(true_type));
        };


        
        template<typename T>
        struct has_member_try_lock_until : boost::false_type {};

        template<typename T>
        struct has_member_try_lock_for : boost::false_type {};
        
    }
    
#endif    

}    
}


#endif
