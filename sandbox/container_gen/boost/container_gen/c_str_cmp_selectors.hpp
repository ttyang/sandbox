//=======================================================================
// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_C_STR_CMP_SELECTORS_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_C_STR_CMP_SELECTORS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>

#if !defined BOOST_NO_CWCHAR
#include <cwchar>
#endif

//[reference__c_str_compare_selectors
namespace boost {

    struct c_str_equivalence_selector
    {
        template <typename T>
        struct apply
        {
            class type
            {
                inline static bool
                    _evaluate(
                        T const& lhs
                      , T const& rhs
                      , ::std::tr1::true_type
                    )
                {
                    return !strcmp(lhs, rhs);
                }

//<-
#if !defined BOOST_NO_CWCHAR
//->
                inline static bool
                    _evaluate(
                        T const& lhs
                      , T const& rhs
                      , ::std::tr1::false_type
                    )
                {
                    return !wcscmp(lhs, rhs);
                }
//<-
#endif
//->

             public:
                inline bool operator()(T const& lhs, T const& rhs) const
                {
                    return _evaluate(
                        lhs
                      , rhs
                      , ::std::tr1::is_same<
                            typename ::std::tr1::remove_cv<
                                typename ::std::tr1::remove_pointer<
                                    typename ::std::tr1::remove_extent<T>::type
                                >::type
                            >::type
                          , char
                        >()
                    );
                }
            };
        };
    };

    struct c_str_ordering_selector
    {
        template <typename T>
        struct apply
        {
            class type
            {
                inline static bool
                    _evaluate(
                        T const& lhs
                      , T const& rhs
                      , ::std::tr1::true_type
                    )
                {
                    return strcmp(lhs, rhs) < 0;
                }

//<-
#if !defined BOOST_NO_CWCHAR
//->
                inline static bool
                    _evaluate(
                        T const& lhs
                      , T const& rhs
                      , ::std::tr1::false_type
                    )
                {
                    return wcscmp(lhs, rhs) < 0;
                }
//<-
#endif
//->

             public:
                inline bool operator()(T const& lhs, T const& rhs) const
                {
                    return _evaluate(
                        lhs
                      , rhs
                      , ::std::tr1::is_same<
                            typename ::std::tr1::remove_cv<
                                typename ::std::tr1::remove_pointer<
                                    typename ::std::tr1::remove_extent<T>::type
                                >::type
                            >::type
                          , char
                        >()
                    );
                }
            };
        };
    };
}  // namespace boost
//]

#endif  // BOOST_CONTAINER_GEN_C_STR_CMP_SELECTORS_HPP_INCLUDED

