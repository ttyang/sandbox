///////////////////////////////////////////////////////////////////////////////
//
// is_std_hash_set.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
# pragma once
#endif // _MSC_VER > 1000

#ifndef IS_STD_HASH_SET_EN_16_12_2004
#define IS_STD_HASH_SET_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include "./std_hash_set_fwd.hpp"

namespace boost
{
    template<class T>
    struct is_std_hash_set
        : ::boost::mpl::false_
    {};

    template<
        class Kty
      , class Tr
      , class Alloc
    >
    struct is_std_hash_set< ::stdext::hash_set<Kty,Tr,Alloc> >
        : ::boost::mpl::true_
    {};

    template<class T>
    struct is_std_hash_multiset
        : ::boost::mpl::false_
    {};

    template<
        class Kty
      , class Tr
      , class Alloc
    >
    struct is_std_hash_multiset< ::stdext::hash_multiset<Kty,Tr,Alloc> >
        : ::boost::mpl::true_
    {};
}

#endif
