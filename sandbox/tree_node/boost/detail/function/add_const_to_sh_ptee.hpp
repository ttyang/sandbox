// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_FUNCTION_ADD_CONST_TO_SH_PTEE_HPP_INCLUDED
#define BOOST_DETAIL_FUNCTION_ADD_CONST_TO_SH_PTEE_HPP_INCLUDED

#include <boost/tr1/memory.hpp>

namespace boost { namespace detail {

    template <typename T>
    struct add_const_to_shared_pointee
    {
        typedef ::std::tr1::shared_ptr<T const> result_type;
        typedef ::std::tr1::shared_ptr<T> argument_type;

        result_type operator()(argument_type const& arg) const;
    };

    template <typename T>
    inline typename add_const_to_shared_pointee<T>::result_type
        add_const_to_shared_pointee<T>::operator()(
            argument_type const& arg
        ) const
    {
        return result_type(arg);
    }
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_FUNCTION_ADD_CONST_TO_SH_PTEE_HPP_INCLUDED

