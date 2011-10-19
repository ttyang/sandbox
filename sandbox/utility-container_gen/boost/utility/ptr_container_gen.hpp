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

#ifndef BOOST_UTILITY_PTR_CONTAINER_GEN_HPP_INCLUDED
#define BOOST_UTILITY_PTR_CONTAINER_GEN_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/utility/container_selector.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <boost/functional/hash.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>

#if !defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS && BOOST_VERSION >= 104800
#define BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
#endif

#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
#include <boost/mpl/if.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/function/range_equal.hpp>
#include <boost/detail/function/range_less.hpp>
#endif

//[reference__ptr_container_gen__list_specialization
namespace boost {

    //<-
    template <typename Selector, typename ValueType>
    struct ptr_container_gen
    {
    };

    template <typename ValueType>
    struct ptr_container_gen<vecS,ValueType>
    {
        typedef ::boost::ptr_vector<ValueType> type;
    };

    template <typename ValueType>
    struct ptr_container_gen<dequeS,ValueType>
    {
        typedef ::boost::ptr_deque<ValueType> type;
    };
    //->

    template <typename ValueType>
    struct ptr_container_gen<listS,ValueType>
    {
        typedef ::boost::ptr_list<ValueType> type;
    };

    //<-
    template <typename ValueType>
    struct ptr_container_gen<setS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::boost::ptr_set<ValueType,::boost::detail::range_less>
                  , ::boost::ptr_set<ValueType>
                >::type
                type;
#else
        typedef ::boost::ptr_set<ValueType> type;
#endif
    };

    template <typename ValueType>
    struct ptr_container_gen<mapS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::boost::ptr_set<ValueType,::boost::detail::range_less>
                  , ::boost::ptr_set<ValueType>
                >::type
                type;
#else
        typedef ::boost::ptr_set<ValueType> type;
#endif
    };

    template <typename ValueType>
    struct ptr_container_gen<multisetS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::boost::ptr_multiset<
                        ValueType
                      , ::boost::detail::range_less
                    >
                  , ::boost::ptr_multiset<ValueType>
                >::type
                type;
#else
        typedef ::boost::ptr_multiset<ValueType> type;
#endif
    };

    template <typename ValueType>
    struct ptr_container_gen<multimapS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::boost::ptr_multiset<
                        ValueType
                      , ::boost::detail::range_less
                    >
                  , ::boost::ptr_multiset<ValueType>
                >::type
                type;
#else
        typedef ::boost::ptr_multiset<ValueType> type;
#endif
    };

    template <typename ValueType>
    struct ptr_container_gen<hash_setS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::boost::ptr_unordered_set<
                        ValueType
                      , ::boost::hash<ValueType>
                      , ::boost::detail::range_equal
                    >
                  , ::boost::ptr_unordered_set<
                        ValueType
                      , ::boost::hash<ValueType>
                    >
                >::type
                type;
#else
        typedef ::boost::ptr_unordered_set<
                    ValueType
                  , ::boost::hash<ValueType>
                >
                type;
#endif
    };

    template <typename ValueType>
    struct ptr_container_gen<hash_mapS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::boost::ptr_unordered_set<
                        ValueType
                      , ::boost::hash<ValueType>
                      , ::boost::detail::range_equal
                    >
                  , ::boost::ptr_unordered_set<
                        ValueType
                      , ::boost::hash<ValueType>
                    >
                >::type
                type;
#else
        typedef ::boost::ptr_unordered_set<
                    ValueType
                  , ::boost::hash<ValueType>
                >
                type;
#endif
    };

    template <typename ValueType>
    struct ptr_container_gen<hash_multisetS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::boost::ptr_unordered_multiset<
                        ValueType
                      , ::boost::hash<ValueType>
                      , ::boost::detail::range_equal
                    >
                  , ::boost::ptr_unordered_multiset<
                        ValueType
                      , ::boost::hash<ValueType>
                    >
                >::type
                type;
#else
        typedef ::boost::ptr_unordered_multiset<
                    ValueType
                  , ::boost::hash<ValueType>
                >
                type;
#endif
    };

    template <typename ValueType>
    struct ptr_container_gen<hash_multimapS,ValueType>
    {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::is_container<ValueType>
                  , ::boost::ptr_unordered_multiset<
                        ValueType
                      , ::boost::hash<ValueType>
                      , ::boost::detail::range_equal
                    >
                  , ::boost::ptr_unordered_multiset<
                        ValueType
                      , ::boost::hash<ValueType>
                    >
                >::type
                type;
#else
        typedef ::boost::ptr_unordered_multiset<
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
  // The main ptr_container_gen traits class uses partial specialization,
  // so we also include a workaround.
  //===========================================================================

//[reference__ptr_container_gen
namespace boost {

    template <typename Selector, typename ValueType>
    struct ptr_container_gen
    {
        //<-
        typedef typename container_selector<Selector>::type
                Select;
        typedef typename Select::BOOST_NESTED_TEMPLATE bind_<
                    ValueType
                >::ptr_type
                type;
        //->
        // typedef .... type;
    };
}  // namespace boost
//]

#endif // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_UTILITY_PTR_CONTAINER_GEN_HPP_INCLUDED

