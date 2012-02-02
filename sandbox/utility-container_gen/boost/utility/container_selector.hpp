//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2010 Thomas Claveirole
// Copyright 2011-2012 Cromwell D. Enage
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Thomas Claveirole,
//          Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_UTILITY_CONTAINER_SELECTOR_HPP_INCLUDED
#define BOOST_UTILITY_CONTAINER_SELECTOR_HPP_INCLUDED

#include <boost/config.hpp>

  //===========================================================================
  // Selectors for the VertexList and EdgeList template parameters of
  // adjacency_list, and the container_gen traits class which is used
  // to map the selectors to the container type used to implement the
  // graph.
  //===========================================================================

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__container_selectors
namespace boost {

    struct vecS { };
    struct dequeS { };
    struct listS { };
#if !defined BOOST_NO_SLIST
    struct slistS { };
#endif
    struct setS { };
    struct mapS { };
    struct multisetS { };
    struct multimapS { };
    struct boost_vecS { };
    struct stable_vecS { };
    struct boost_dequeS { };
    struct boost_listS { };
    struct boost_slistS { };
    struct boost_setS { };
    struct boost_mapS { };
    struct boost_multisetS { };
    struct boost_multimapS { };
    struct hash_setS { };
    struct hash_mapS { };
    struct hash_multisetS { };
    struct hash_multimapS { };
    struct flat_setS { };
    struct flat_mapS { };
    struct flat_multisetS { };
    struct flat_multimapS { };
}  // namespace boost
//]

#else  // defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <vector>
#include <deque>
#include <list>
#include <set>

#if !defined BOOST_NO_SLIST
#  ifdef BOOST_SLIST_HEADER
#    include BOOST_SLIST_HEADER
#  else
#    include <slist>
#  endif
#endif

#include <boost/tr1/unordered_set.hpp>
#include <boost/tr1/functional.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>

#include <boost/mpl/if.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/function/range_equal.hpp>
#include <boost/detail/function/range_less.hpp>

//[reference__ptr_container_selectors
namespace boost {

    struct vecS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef ::std::vector<T> type;
            typedef ::boost::ptr_vector<T> ptr_type;
        };
        //->
    };

    struct dequeS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef ::std::deque<T> type;
            typedef ::boost::ptr_deque<T> ptr_type;
        };
        //->
    };

    struct listS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef ::std::list<T> type;
            typedef ::boost::ptr_list<T> ptr_type;
        };
        //->
    };

    //<-
#if !defined BOOST_NO_SLIST
    struct slistS
    {
        template <typename T>
        struct bind_
        {
            typedef ::BOOST_STD_EXTENSION_NAMESPACE::slist<T> type;
        };
    };
#endif
    //->

    struct setS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::set<T,::boost::detail::range_less>
                      , ::std::set<T>
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_set<T,::boost::detail::range_less>
                      , ::boost::ptr_set<T>
                    >::type
                    ptr_type;
        };
        //->
    };

    struct mapS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::set<T,::boost::detail::range_less>
                      , ::std::set<T>
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_set<T,::boost::detail::range_less>
                      , ::boost::ptr_set<T>
                    >::type
                    ptr_type;
        };
        //->
    };

    struct multisetS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::multiset<T,::boost::detail::range_less>
                      , ::std::multiset<T>
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_multiset<T,::boost::detail::range_less>
                      , ::boost::ptr_multiset<T>
                    >::type
                    ptr_type;
        };
        //->
    };

    struct multimapS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::multiset<T,::boost::detail::range_less>
                      , ::std::multiset<T>
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_multiset<T,::boost::detail::range_less>
                      , ::boost::ptr_multiset<T>
                    >::type
                    ptr_type;
        };
        //->
    };

    struct hash_setS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::tr1::unordered_set<
                            ValueType
                          , ::std::tr1::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::std::tr1::unordered_set<T,::std::tr1::hash<T> >
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_unordered_set<
                            T
                          , ::std::tr1::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::boost::ptr_unordered_set<T,::std::tr1::hash<T> >
                    >::type
                    ptr_type;
        };
        //->
    };

    struct hash_mapS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::tr1::unordered_set<
                            T
                          , ::std::tr1::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::std::tr1::unordered_set<T,::std::tr1::hash<T> >
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_unordered_set<
                            T
                          , ::std::tr1::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::boost::ptr_unordered_set<T,::std::tr1::hash<T> >
                    >::type
                    ptr_type;
        };
        //->
    };

    struct hash_multisetS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::tr1::unordered_multiset<
                            T
                          , ::std::tr1::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::std::tr1::unordered_multiset<T,::std::tr1::hash<T> >
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_unordered_multiset<
                            T
                          , ::std::tr1::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::boost::ptr_unordered_multiset<T,::std::tr1::hash<T> >
                    >::type
                    ptr_type;
        };
        //->
    };

    struct hash_multimapS
    {
        //<-
        template <typename T>
        struct bind_
        {
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::tr1::unordered_multiset<
                            T
                          , ::std::tr1::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::std::tr1::unordered_multiset<T,::std::tr1::hash<T> >
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_unordered_multiset<
                            T
                          , ::std::tr1::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::boost::ptr_unordered_multiset<T,::std::tr1::hash<T> >
                    >::type
                    ptr_type;
        };
        //->
    };

    //<-
    template <typename Selector>
    struct container_selector
    {
        typedef vecS type;
    };

#define BOOST_CONTAINER_SELECTOR(NAME) \
    template <> struct container_selector<NAME> { typedef NAME type; }

    BOOST_CONTAINER_SELECTOR(vecS);
    BOOST_CONTAINER_SELECTOR(dequeS);
    BOOST_CONTAINER_SELECTOR(listS);
#if !defined BOOST_NO_SLIST
    BOOST_CONTAINER_SELECTOR(slistS);
#endif
    BOOST_CONTAINER_SELECTOR(setS);
    BOOST_CONTAINER_SELECTOR(mapS);
    BOOST_CONTAINER_SELECTOR(multisetS);
    BOOST_CONTAINER_SELECTOR(multimapS);
    BOOST_CONTAINER_SELECTOR(hash_setS);
    BOOST_CONTAINER_SELECTOR(hash_mapS);
    BOOST_CONTAINER_SELECTOR(hash_multisetS);
    BOOST_CONTAINER_SELECTOR(hash_multimapS);

#undef BOOST_CONTAINER_SELECTOR

    //->
}  // namespace boost
//]

#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_UTILITY_CONTAINER_SELECTOR_HPP_INCLUDED

