// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_METAFUNCTION_IS_ALLOCATOR_HPP_INCLUDED
#define BOOST_DETAIL_METAFUNCTION_IS_ALLOCATOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/container/allocator_traits.hpp>
#include <boost/detail/metafunction/has_allocator_type.hpp>
#endif

#include <boost/detail/metafunction/has_value_type.hpp>
#include <boost/detail/metafunction/has_pointer.hpp>
#include <boost/detail/metafunction/has_reference.hpp>
#include <boost/detail/metafunction/has_const_pointer.hpp>
#include <boost/detail/metafunction/has_const_reference.hpp>
#include <boost/detail/metafunction/has_size_type.hpp>
#include <boost/detail/metafunction/has_difference_type.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename T>
    struct is_allocator_impl
      : ::boost::mpl::eval_if<
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
          typename ::boost::mpl::eval_if<
            typename ::boost::mpl::eval_if<
              typename ::boost::mpl::eval_if<
                typename ::boost::mpl::eval_if<
#endif
                  typename ::boost::mpl::eval_if<
                    typename ::boost::mpl::eval_if<
                      typename ::boost::mpl::eval_if<
                        typename ::boost::mpl::eval_if<
                          typename ::boost::mpl::eval_if<
                            typename ::boost::detail::metafunction
                            ::has_value_type<T>::type
                          , ::boost::detail::metafunction::has_size_type<
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                              ::boost::container::allocator_traits<
#endif
                                T
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                              >
#endif
                            >
                          , ::boost::mpl::false_
                          >::type
                        , ::boost::detail::metafunction::has_difference_type<
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                            ::boost::container::allocator_traits<
#endif
                              T
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                            >
#endif
                          >
                        , ::boost::mpl::false_
                        >::type
                      , ::boost::detail::metafunction::has_pointer<
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                          ::boost::container::allocator_traits<
#endif
                            T
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                          >
#endif
                        >
                      , ::boost::mpl::false_
                      >::type
                    , ::boost::detail::metafunction::has_const_pointer<
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                        ::boost::container::allocator_traits<
#endif
                          T
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                        >
#endif
                      >
                    , ::boost::mpl::false_
                    >::type
                  , ::boost::detail::metafunction::has_reference<
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                      ::boost::container::allocator_traits<
#endif
                        T
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                      >
#endif
                    >
                  , ::boost::mpl::false_
                  >::type
                , ::boost::detail::metafunction::has_const_reference<
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                    ::boost::container::allocator_traits<
#endif
                      T
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                    >
#endif
                  >
                , ::boost::mpl::false_
                >::type
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
              , ::boost::detail::metafunction::has_allocator_type<
                  ::boost::container::allocator_traits<T>
                >
              , ::boost::mpl::false_
              >::type
            , ::boost::detail::metafunction::has_propagate_on_container_swap<
                ::boost::container::allocator_traits<T>
              >
            , ::boost::mpl::false_
            >::type
          , ::boost::detail::metafunction
            ::has_propagate_on_container_copy_assignment<
              ::boost::container::allocator_traits<T>
            >
          , ::boost::mpl::false_
          >::type
        , ::boost::detail::metafunction
          ::has_propagate_on_container_move_assignment<
            ::boost::container::allocator_traits<T>
          >
        , ::boost::mpl::false_
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        >
    {
    };

    template <typename T>
    struct is_allocator
      : ::boost::mpl::eval_if<
            is_container<T>
          , ::boost::mpl::false_
          , is_allocator_impl<T>
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_container,(T))
    };
}}}  // namespace boost::detail::metafunction

#endif  // BOOST_DETAIL_METAFUNCTION_IS_ALLOCATOR_HPP_INCLUDED

