// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_FUNCTION_ADD_CONST_TO_2ND_POINTEE_HPP_INCLUDED
#define BOOST_DETAIL_FUNCTION_ADD_CONST_TO_2ND_POINTEE_HPP_INCLUDED

#include <utility>

namespace boost { namespace detail {

    template <typename K, typename V>
    struct add_const_to_2nd_pointee
    {
        typedef ::std::pair<K const,V const*> result_type;
        typedef ::std::pair<K const,V*> argument_type;

        result_type operator()(argument_type const& arg) const;
    };

    template <typename K, typename V>
    inline typename add_const_to_2nd_pointee<K,V>::result_type
        add_const_to_2nd_pointee<K,V>::operator()(
            argument_type const& arg
        ) const
    {
        return result_type(arg.first, arg.second);
    }
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_FUNCTION_ADD_CONST_TO_2ND_POINTEE_HPP_INCLUDED

