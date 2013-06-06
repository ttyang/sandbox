//=============================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_IS_COMPARE_SELECTOR_HPP
#define BOOST_CONTAINER_GEN_IS_COMPARE_SELECTOR_HPP

#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/bool.hpp>

#if defined BOOST_MPL_CFG_NO_HAS_XXX || \
    defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#include <boost/container_gen/selectors_fwd.hpp>
#include <boost/container_gen/c_str_cmp_selectors_fwd.hpp>

namespace boost {

    template <typename T>
    struct is_compare_selector : ::boost::mpl::false_
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_compare_selector, (T))
    };

    template <>
    struct is_compare_selector<equal_to_selector> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_compare_selector<less_than_selector> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_compare_selector<greater_than_selector> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_compare_selector<c_str_less_than_selector> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_compare_selector<c_str_greater_than_selector>
      : ::boost::mpl::true_
    {
    };
}  // namespace boost

#else  // !defined BOOST_MPL_CFG_NO_HAS_XXX && \
//    !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#include <boost/config.hpp>
#include <cstddef>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/detail/metafunction/has_apply_template.hpp>
#include <boost/detail/metafunction/is_function_wrt.hpp>

#if defined BOOST_DETAIL_METAFUNCTION_ATTEMPT_ARITY_DETECTION
#include <boost/mpl/if.hpp>
#include <boost/detail/metafunction/is_n_ary_function.hpp>
#include <boost/detail/metafunction/is_adaptable_binary_func.hpp>
#endif

namespace boost { namespace detail { namespace metafunction {

    template <typename Metafunction>
    struct is_compare_selector_result_predicate
#if !defined BOOST_DETAIL_METAFUNCTION_ATTEMPT_ARITY_DETECTION
      : ::boost::detail::metafunction::is_function_with_result_type<
            typename Metafunction::type
          , bool
        >
#endif
    {
#if defined BOOST_DETAIL_METAFUNCTION_ATTEMPT_ARITY_DETECTION
     private:
        typedef typename Metafunction::type _function;

     public:
        typedef typename ::boost::mpl::eval_if<
                    ::boost::detail::metafunction
                    ::is_function_with_result_type<_function,bool>
                  , ::boost::mpl::if_<
                        ::boost::detail::metafunction::is_n_ary_function<
                            _function
                          , ::boost::mpl::integral_c<unsigned int,2>
                        >
                      , ::boost::mpl::true_
                      , ::boost::detail::metafunction
                        ::is_adaptable_binary_function<_function>
                    >
                  , ::boost::mpl::false_
                >::type
                type;
#endif
    };

    template <typename T>
    struct is_compare_selector_metafunction_class
    {
     private:
        typedef ::boost::mpl::apply_wrap1<
                    ::boost::mpl::unpack_args<T>
                  , ::boost::mpl::vector1<T>
                >
                _metafunction;

     public:
        typedef typename ::boost::mpl::eval_if<
                    typename ::boost::mpl::aux::has_type<
                        _metafunction
                      , ::boost::mpl::false_
                    >::type
                  , is_compare_selector_result_predicate<_metafunction>
                  , ::boost::mpl::false_
                >::type
                type;
    };
}}}  // namespace boost::detail::metafunction

//[reference__is_compare_selector
namespace boost {

    template <typename T>
    struct is_compare_selector
      : ::boost::mpl::eval_if<
            typename ::boost::detail::metafunction::has_apply_template<T>::type
          , ::boost::detail::metafunction
            ::is_compare_selector_metafunction_class<T>
          , ::boost::mpl::false_
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_compare_selector, (T))
    };
}  // namespace boost
//]

#endif  // BOOST_MPL_CFG_NO_HAS_XXX, BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#endif  // BOOST_CONTAINER_GEN_IS_COMPARE_SELECTOR_HPP

