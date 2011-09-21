//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2010 Thomas Claveirole
// Copyright 2011 Cromwell D. Enage
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Thomas Claveirole,
//          Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_UTILITY_CONTAINER_GEN_HPP_INCLUDED
#define BOOST_UTILITY_CONTAINER_GEN_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/utility/container_selector.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if !defined BOOST_NO_SLIST
#  ifdef BOOST_SLIST_HEADER
#    include BOOST_SLIST_HEADER
#  else
#    include <slist>
#  endif
#endif

#include <vector>
#include <deque>
#include <list>
#include <set>

#include <boost/tr1/unordered_set.hpp>
#include <boost/functional/hash.hpp>

#if !defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS && BOOST_VERSION >= 104800
#define BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
#endif

#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
#include <boost/mpl/if.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/function/range_equal.hpp>
#include <boost/detail/function/range_less.hpp>
#endif

//[reference__container_gen__list_specialization
namespace boost {

    //<-
    template <typename Selector, typename ValueType>
    struct container_gen
    {
    };
    //->

    template <typename ValueType>
    struct container_gen<listS,ValueType>
    {
        typedef ::std::list<ValueType> type;
    };

    //<-
#if !defined BOOST_NO_SLIST
    template <typename ValueType>
    struct container_gen<slistS,ValueType>
    {
        typedef ::BOOST_STD_EXTENSION_NAMESPACE::slist<ValueType> type;
    };
#endif

    template <typename ValueType>
    struct container_gen<vecS,ValueType>
    {
        typedef ::std::vector<ValueType> type;
    };

    template <typename ValueType>
    struct container_gen<dequeS,ValueType>
    {
        typedef ::std::deque<ValueType> type;
    };

    template <typename ValueType>
    struct container_gen<setS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::std::set<ValueType,::boost::detail::range_less>
                  , ::std::set<ValueType>
                >::type
                type;
#else
        typedef ::std::set<ValueType> type;
#endif
    };

    template <typename ValueType>
    struct container_gen<mapS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::std::set<ValueType,::boost::detail::range_less>
                  , ::std::set<ValueType>
                >::type
                type;
#else
        typedef ::std::set<ValueType> type;
#endif
    };

    template <typename ValueType>
    struct container_gen<multisetS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::std::multiset<ValueType,::boost::detail::range_less>
                  , ::std::multiset<ValueType>
                >::type
                type;
#else
        typedef ::std::multiset<ValueType> type;
#endif
    };

    template <typename ValueType>
    struct container_gen<multimapS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::std::multiset<ValueType,::boost::detail::range_less>
                  , ::std::multiset<ValueType>
                >::type
                type;
#else
        typedef ::std::multiset<ValueType> type;
#endif
    };

    template <typename ValueType>
    struct container_gen<hash_setS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::std::tr1::unordered_set<
                        ValueType
                      , ::boost::hash<ValueType>
                      , ::boost::detail::range_equal
                    >
                  , ::std::tr1::unordered_set<
                        ValueType
                      , ::boost::hash<ValueType>
                    >
                >::type
                type;
#else
        typedef ::std::tr1::unordered_set<
                    ValueType
                  , ::boost::hash<ValueType>
                >
                type;
#endif
    };

    template <typename ValueType>
    struct container_gen<hash_mapS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::std::tr1::unordered_set<
                        ValueType
                      , ::boost::hash<ValueType>
                      , ::boost::detail::range_equal
                    >
                  , ::std::tr1::unordered_set<
                        ValueType
                      , ::boost::hash<ValueType>
                    >
                >::type
                type;
#else
        typedef ::std::tr1::unordered_set<
                    ValueType
                  , ::boost::hash<ValueType>
                >
                type;
#endif
    };

    template <typename ValueType>
    struct container_gen<hash_multisetS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::std::tr1::unordered_multiset<
                        ValueType
                      , ::boost::hash<ValueType>
                      , ::boost::detail::range_equal
                    >
                  , ::std::tr1::unordered_multiset<
                        ValueType
                      , ::boost::hash<ValueType>
                    >
                >::type
                type;
#else
        typedef ::std::tr1::unordered_multiset<
                    ValueType
                  , ::boost::hash<ValueType>
                >
                type;
#endif
    };

    template <typename ValueType>
    struct container_gen<hash_multimapS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::std::tr1::unordered_multiset<
                        ValueType
                      , ::boost::hash<ValueType>
                      , ::boost::detail::range_equal
                    >
                  , ::std::tr1::unordered_multiset<
                        ValueType
                      , ::boost::hash<ValueType>
                    >
                >::type
                type;
#else
        typedef ::std::tr1::unordered_multiset<
                    ValueType
                  , ::boost::hash<ValueType>
                >
                type;
#endif
    };
    //->
}  // namespace boost
//]

#else // defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

  //===========================================================================
  // The main container_gen traits class uses partial specialization,
  // so we also include a workaround.
  //===========================================================================

//[reference__container_gen
namespace boost {

    template <typename Selector, typename ValueType>
    struct container_gen
    {
        //<-
        typedef typename container_selector<Selector>::type
                Select;
        typedef typename Select::BOOST_NESTED_TEMPLATE bind_<ValueType>::type
                type;
        //->
        // typedef .... type;
    };
}  // namespace boost
//]

#endif // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_UTILITY_CONTAINER_GEN_HPP_INCLUDED

