// Copyright (C) 2005-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UTILITY_IS_MPL_INTEGRAL_CONSTANT_HPP_INCLUDED
#define BOOST_UTILITY_IS_MPL_INTEGRAL_CONSTANT_HPP_INCLUDED

#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/tag.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/integral_c_tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/tr1/type_traits.hpp>

namespace boost {

    template <typename Tag>
    struct is_mpl_integral_constant_dispatch
    {
        template <typename T>
        struct apply
        {
            typedef ::boost::mpl::false_ type;
        };
    };

    /*
     * Boolean Constants are not Integral Constants.
     */
    template <>
    struct is_mpl_integral_constant_dispatch< ::boost::mpl::integral_c_tag>
    {
        template <typename T>
        struct apply
#if !defined BOOST_MPL_CFG_NO_NESTED_FORWARDING
          : ::boost::mpl::if_<
                ::std::tr1::is_same<typename T::value_type,bool>
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >
        {
#else
        {
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_same<typename T::value_type,bool>
                      , ::boost::mpl::false_
                      , ::boost::mpl::true_
                    >::type
                    type;
#endif  // BOOST_MPL_CFG_NO_NESTED_FORWARDING
        };
    };

    template <typename T>
    struct is_mpl_integral_constant_impl
      : ::boost::mpl::apply_wrap1<
            is_mpl_integral_constant_dispatch<
                typename ::boost::mpl::tag<T>::type
            >
          , T
        >::type
    {
    };

    //[reference__is_mpl_integral_constant
    template <typename T>
    struct is_mpl_integral_constant
        //<-
      : ::boost::mpl::if_<
            ::boost::mpl::aux::has_tag<T>
          , is_mpl_integral_constant_impl<T>
          , ::boost::mpl::false_
        >::type
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_mpl_integral_constant, (T))
        //->
    };
    //]
}  // namespace boost

#endif  // BOOST_UTILITY_IS_MPL_INTEGRAL_CONSTANT_HPP_INCLUDED

