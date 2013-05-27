// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTAINER_GEN_DETAIL_METAFUNCTION_IS_ALLOCATOR_SELECTOR_HPP
#define BOOST_CONTAINER_GEN_DETAIL_METAFUNCTION_IS_ALLOCATOR_SELECTOR_HPP

#include <boost/mpl/aux_/config/has_xxx.hpp>

#if defined BOOST_MPL_CFG_NO_HAS_XXX
#error Your compiler must be able to detect nested type definitions.
#endif

#if defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
#error Your compiler must be able to detect nested template definitions.
#endif

#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/detail/metafunction/has_apply_template.hpp>
#include <boost/detail/metafunction/is_allocator.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct does_allocator_selector_return_allocator
      : ::boost::detail::metafunction::is_allocator<
            typename ::boost::mpl::apply_wrap1<
                ::boost::mpl::unpack_args<T>
              , ::boost::mpl::vector1<T>
            >::type
        >
    {
    };

    template <typename T>
    struct is_allocator_selector_metafunction_class
      : ::boost::mpl::if_<
            typename ::boost::mpl::aux::has_type<
                ::boost::mpl::apply_wrap1<
                    ::boost::mpl::unpack_args<T>
                  , ::boost::mpl::vector1<T>
                >
              , ::boost::mpl::false_
            >::type
          , does_allocator_selector_return_allocator<T>
          , ::boost::mpl::false_
        >
    {
    };

    template <typename T>
    struct is_allocator_selector
      : ::boost::mpl::eval_if<
            typename ::boost::detail::metafunction::has_apply_template<T>::type
          , is_allocator_selector_metafunction_class<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_allocator_selector, (T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_CONTAINER_GEN_DETAIL_METAFUNCTION_IS_ALLOCATOR_SELECTOR_HPP

