//           Copyright Jeroen Habraken 2010 - 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_DETAIL_QI_HPP
#define BOOST_COERCE_DETAIL_QI_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/coerce/reserve.hpp>
#include <boost/coerce/string.hpp>

#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>

namespace boost { namespace coerce { namespace detail {

    struct qi {
        template <typename Target, typename Source>
        static inline bool
        call(Target & target, Source const & source) {
            typedef traits::string<Source> string_traits;

            typename string_traits::size_type
                length = string_traits::length(source);
            detail::call_reserve(target, length);

            typename string_traits::const_iterator
                begin = string_traits::begin(source), iterator = begin;

            bool result = spirit::qi::parse(
                iterator, string_traits::end(source), target);

            if (static_cast<typename string_traits::size_type>(iterator - begin) != length) {
                return false;
            }

            return result;
        }
    };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_QI_HPP
