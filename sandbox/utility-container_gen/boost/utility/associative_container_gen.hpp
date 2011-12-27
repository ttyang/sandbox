//=======================================================================
// Copyright (C) 2011 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_UTILITY_ASSOCIATIVE_CONTAINER_GEN_HPP_INCLUDED
#define BOOST_UTILITY_ASSOCIATIVE_CONTAINER_GEN_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/utility/container_selector.hpp>

#include <boost/container/set.hpp>
#include <boost/container/map.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/container/flat_map.hpp>

#include <boost/tr1/unordered_set.hpp>
#include <boost/tr1/unordered_map.hpp>
#include <boost/functional/hash.hpp>

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/function/range_equal.hpp>
#include <boost/detail/function/range_less.hpp>

//[reference__associative_container_gen
namespace boost {

    template <typename Selector>
    struct associative_container_gen
    {
//<-
#if 0
//->
        template <typename Key, typename Mapped = void>
        struct apply
        {
            // typedef ... type;
        };
//<-
#endif
//->
    };

    //<-
    template <>
    struct associative_container_gen<setS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::set<
                                Key
                              , ::boost::detail::range_less
                            >
                          , ::boost::container::map<
                                Key
                              , Mapped
                              , ::boost::detail::range_less
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::set<Key>
                          , ::boost::container::map<Key,Mapped>
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<mapS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::set<
                                Key
                              , ::boost::detail::range_less
                            >
                          , ::boost::container::map<
                                Key
                              , Mapped
                              , ::boost::detail::range_less
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::set<Key>
                          , ::boost::container::map<Key,Mapped>
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<multisetS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::multiset<
                                Key
                              , ::boost::detail::range_less
                            >
                          , ::boost::container::multimap<
                                Key
                              , Mapped
                              , ::boost::detail::range_less
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::multiset<Key>
                          , ::boost::container::multimap<Key,Mapped>
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<multimapS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::multiset<
                                Key
                              , ::boost::detail::range_less
                            >
                          , ::boost::container::multimap<
                                Key
                              , Mapped
                              , ::boost::detail::range_less
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::multiset<Key>
                          , ::boost::container::multimap<Key,Mapped>
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<hash_setS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::std::tr1::unordered_set<
                                Key
                              , ::boost::hash<Key>
                              , ::boost::detail::range_equal
                            >
                          , ::std::tr1::unordered_map<
                                Key
                              , Mapped
                              , ::boost::hash<Key>
                              , ::boost::detail::range_equal
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::std::tr1::unordered_set<Key,::boost::hash<Key> >
                          , ::std::tr1::unordered_map<
                                Key
                              , Mapped
                              , ::boost::hash<Key>
                            >
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<hash_mapS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::std::tr1::unordered_set<
                                Key
                              , ::boost::hash<Key>
                              , ::boost::detail::range_equal
                            >
                          , ::std::tr1::unordered_map<
                                Key
                              , Mapped
                              , ::boost::hash<Key>
                              , ::boost::detail::range_equal
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::std::tr1::unordered_set<Key,::boost::hash<Key> >
                          , ::std::tr1::unordered_map<
                                Key
                              , Mapped
                              , ::boost::hash<Key>
                            >
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<hash_multisetS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::std::tr1::unordered_multiset<
                                Key
                              , ::boost::hash<Key>
                              , ::boost::detail::range_equal
                            >
                          , ::std::tr1::unordered_multimap<
                                Key
                              , Mapped
                              , ::boost::hash<Key>
                              , ::boost::detail::range_equal
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::std::tr1::unordered_multiset<
                                Key
                              , ::boost::hash<Key>
                            >
                          , ::std::tr1::unordered_multimap<
                                Key
                              , Mapped
                              , ::boost::hash<Key>
                            >
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<hash_multimapS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::std::tr1::unordered_multiset<
                                Key
                              , ::boost::hash<Key>
                              , ::boost::detail::range_equal
                            >
                          , ::std::tr1::unordered_multimap<
                                Key
                              , Mapped
                              , ::boost::hash<Key>
                              , ::boost::detail::range_equal
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::std::tr1::unordered_multiset<
                                Key
                              , ::boost::hash<Key>
                            >
                          , ::std::tr1::unordered_multimap<
                                Key
                              , Mapped
                              , ::boost::hash<Key>
                            >
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<flat_setS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::flat_set<
                                Key
                              , ::boost::detail::range_less
                            >
                          , ::boost::container::flat_map<
                                Key
                              , Mapped
                              , ::boost::detail::range_less
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::flat_set<Key>
                          , ::boost::container::flat_map<Key,Mapped>
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<flat_mapS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::flat_set<
                                Key
                              , ::boost::detail::range_less
                            >
                          , ::boost::container::flat_map<
                                Key
                              , Mapped
                              , ::boost::detail::range_less
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::flat_set<Key>
                          , ::boost::container::flat_map<Key,Mapped>
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<flat_multisetS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::flat_multiset<
                                Key
                              , ::boost::detail::range_less
                            >
                          , ::boost::container::flat_multimap<
                                Key
                              , Mapped
                              , ::boost::detail::range_less
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::flat_multiset<Key>
                          , ::boost::container::flat_multimap<Key,Mapped>
                        >
                    >::type
                    type;
        };
    };

    template <>
    struct associative_container_gen<flat_multimapS>
    {
        template <typename Key, typename Mapped = void>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                        ::boost::detail::is_container<Key>
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::flat_multiset<
                                Key
                              , ::boost::detail::range_less
                            >
                          , ::boost::container::flat_multimap<
                                Key
                              , Mapped
                              , ::boost::detail::range_less
                            >
                        >
                      , ::boost::mpl::if_<
                            ::std::tr1::is_same<Mapped,void>
                          , ::boost::container::flat_multiset<Key>
                          , ::boost::container::flat_multimap<Key,Mapped>
                        >
                    >::type
                    type;
        };
    };
    //->
}  // namespace boost
//]

#endif  // BOOST_UTILITY_ASSOCIATIVE_CONTAINER_GEN_HPP_INCLUDED

