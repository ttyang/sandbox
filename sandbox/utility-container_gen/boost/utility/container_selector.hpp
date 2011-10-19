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

#if !defined BOOST_NO_SLIST
    struct slistS { };
#endif

    struct vecS { };
    struct dequeS { };
    struct listS { };
    struct setS { };
    struct mapS { };
    struct multisetS { };
    struct multimapS { };
    struct hash_setS { };
    struct hash_mapS { };
    struct hash_multisetS { };
    struct hash_multimapS { };
}  // namespace boost
//]

#else // defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

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

namespace boost {

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

    struct vecS
    {
        template <typename T>
        struct bind_
        {
            typedef ::std::vector<T> type;
            typedef ::boost::ptr_vector<T> ptr_type;
        };
    };

    struct dequeS
    {
        template <typename T>
        struct bind_
        {
            typedef ::std::deque<T> type;
            typedef ::boost::ptr_deque<T> ptr_type;
        };
    };

    struct listS
    {
        template <typename T>
        struct bind_
        {
            typedef ::std::list<T> type;
            typedef ::boost::ptr_list<T> ptr_type;
        };
    };

    struct setS
    {
        template <typename T>
        struct bind_
        {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
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
#else
            typedef ::std::set<T> type;
            typedef ::boost::ptr_set<T> ptr_type;
#endif
        };
    };

    struct mapS
    {
        template <typename T>
        struct bind_
        {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
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
#else
            typedef ::std::set<T> type;
            typedef ::boost::ptr_set<T> ptr_type;
#endif
        };
    };

    struct multisetS
    {
        template <typename T>
        struct bind_
        {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
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
#else
            typedef ::std::multiset<T> type;
            typedef ::boost::ptr_multiset<T> ptr_type;
#endif
        };
    };

    struct multimapS
    {
        template <typename T>
        struct bind_
        {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
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
#else
            typedef ::std::multiset<T> type;
            typedef ::boost::ptr_multiset<T> ptr_type;
#endif
        };
    };

    struct hash_setS
    {
        template <typename T>
        struct bind_
        {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::tr1::unordered_set<
                            ValueType
                          , ::boost::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::std::tr1::unordered_set<T,::boost::hash<T> >
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_unordered_set<
                            T
                          , ::boost::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::boost::ptr_unordered_set<T,::boost::hash<T> >
                    >::type
                    ptr_type;
#else
            typedef ::std::tr1::unordered_set<T,::boost::hash<T> > type;
            typedef ::boost::ptr_unordered_set<T,::boost::hash<T> > ptr_type;
#endif
        };
    };

    struct hash_mapS
    {
        template <typename T>
        struct bind_
        {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::tr1::unordered_set<
                            T
                          , ::boost::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::std::tr1::unordered_set<T,::boost::hash<T> >
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_unordered_set<
                            T
                          , ::boost::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::boost::ptr_unordered_set<T,::boost::hash<T> >
                    >::type
                    ptr_type;
#else
            typedef ::std::tr1::unordered_set<T,::boost::hash<T> > type;
            typedef ::boost::ptr_unordered_set<T,::boost::hash<T> > ptr_type;
#endif
        };
    };

    struct hash_multisetS
    {
        template <typename T>
        struct bind_
        {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::tr1::unordered_multiset<
                            T
                          , ::boost::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::std::tr1::unordered_multiset<T,::boost::hash<T> >
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_unordered_multiset<
                            T
                          , ::boost::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::boost::ptr_unordered_multiset<T,::boost::hash<T> >
                    >::type
                    ptr_type;
#else
            typedef ::std::tr1::unordered_multiset<T,::boost::hash<T> >
                    type;
            typedef ::boost::ptr_unordered_multiset<T,::boost::hash<T> >
                    ptr_type;
#endif
        };
    };

    struct hash_multimapS
    {
        template <typename T>
        struct bind_
        {
#if defined BOOST_CONTAINER_GEN_USES_OP_TYPE_TRAITS
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::std::tr1::unordered_multiset<
                            T
                          , ::boost::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::std::tr1::unordered_multiset<T,::boost::hash<T> >
                    >::type
                    type;
            typedef typename ::boost::mpl::if_<
                        ::boost::detail::is_container<T>
                      , ::boost::ptr_unordered_multiset<
                            T
                          , ::boost::hash<T>
                          , ::boost::detail::range_equal
                        >
                      , ::boost::ptr_unordered_multiset<T,::boost::hash<T> >
                    >::type
                    ptr_type;
#else
            typedef ::std::tr1::unordered_multiset<T,::boost::hash<T> >
                    type;
            typedef ::boost::ptr_unordered_multiset<T,::boost::hash<T> >
                    ptr_type;
#endif
        };
    };

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
    BOOST_CONTAINER_SELECTOR(setS);
    BOOST_CONTAINER_SELECTOR(mapS);
    BOOST_CONTAINER_SELECTOR(multisetS);
    BOOST_CONTAINER_SELECTOR(multimapS);
    BOOST_CONTAINER_SELECTOR(hash_setS);
    BOOST_CONTAINER_SELECTOR(hash_mapS);
#if !defined BOOST_NO_SLIST
    BOOST_CONTAINER_SELECTOR(slistS);
#endif

#undef BOOST_CONTAINER_SELECTOR

}  // namespace boost

#endif // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_UTILITY_CONTAINER_SELECTOR_HPP_INCLUDED

