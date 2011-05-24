//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_DETAIL_PUSH_BACK_HPP
#define BOOST_COERCE_DETAIL_PUSH_BACK_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>

namespace boost { namespace coerce { namespace detail {

    template <typename T>
    class has_push_back {
        template <typename U, void (U::*)(typename U::const_reference) = &U::push_back>
        struct const_reference { };

        template <typename U>
        static type_traits::yes_type test(U*, const_reference<U>* = 0);

        template <typename U, void (U::*)(typename U::value_type) = &U::push_back>
        struct value_type { };

        template <typename U>
        static type_traits::yes_type test(U*, value_type<U>* = 0);

        template <typename U>
        static type_traits::no_type test(...);

    public:
        BOOST_STATIC_CONSTANT(bool, value =
            sizeof(test<T>(0)) == sizeof(type_traits::yes_type));
        typedef mpl::bool_<value> type;
    };

    BOOST_MPL_HAS_XXX_TRAIT_DEF(const_reference)

    template <typename T>
    struct is_back_insertion_sequence
        : mpl::and_<
            has_push_back<T>,
            has_const_reference<T>
        > { };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_PUSH_BACK_HPP
