// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_PROPERTY_MAP_KEY_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_PROPERTY_MAP_KEY_HPP_INCLUDED

#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/detail/metafunction/data_type.hpp>
#include <boost/detail/metafunction/has_key_type.hpp>

namespace boost { namespace detail {

    template <bool b>
    struct property_map_key_impl
    {
        template <typename T>
        struct apply
        {
            typedef typename property_traits<T>::key_type type;
        };
    };

    template <>
    struct property_map_key_impl<false>
    {
        template <typename T>
        struct apply
        {
            typedef void type;
        };
    };

    template <typename T>
    struct property_map_key
    {
     private:
        typedef typename data_type<T>::type
                DataType;
        typedef typename has_key_type<DataType>::type
                HasKeyType;

     public:
        typedef typename ::boost::mpl::apply_wrap1<
                    property_map_key_impl<HasKeyType::value>
                  , DataType
                >::type
                type;

        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,property_map_key,(T))
    };
}}  // namespace boost::detail

#endif  // BOOST_DETAIL_METAFUNCTION_PROPERTY_MAP_KEY_HPP_INCLUDED

