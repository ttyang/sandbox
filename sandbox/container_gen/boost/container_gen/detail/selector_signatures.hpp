//=============================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_DETAIL_SELECTOR_SIGNATURES_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_DETAIL_SELECTOR_SIGNATURES_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/container_gen/selector_keywords.hpp>

#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#include <boost/container_gen/detail/metafunction/is_compare_selector.hpp>
#include <boost/container_gen/detail/metafunction/is_allocator_selector.hpp>
#include <boost/utility/is_mpl_integral_constant.hpp>

#endif

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <boost/heap/policies.hpp>

namespace boost { namespace detail {

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    ::boost::parameter::deduced<
#endif
                        ::boost::compare_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    >
                  , ::boost::detail::metafunction::is_compare_selector<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    ::boost::parameter::deduced<
#endif
                        ::boost::allocator_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    >
                  , ::boost::detail::metafunction::is_compare_selector<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional< ::boost::heap::tag::stable>
              , ::boost::parameter::optional<
                    ::boost::heap::tag::stability_counter_type
                >
            >
            priority_queue_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::required<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    ::boost::parameter::deduced<
#endif
                        ::boost::heap::tag::arity
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    >
                  , ::boost::is_mpl_integral_constant< ::boost::mpl::_>
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    ::boost::parameter::deduced<
#endif
                        ::boost::compare_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    >
                  , ::boost::detail::metafunction::is_compare_selector<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    ::boost::parameter::deduced<
#endif
                        ::boost::allocator_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    >
                  , ::boost::detail::metafunction::is_compare_selector<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional< ::boost::heap::tag::stable>
              , ::boost::parameter::optional<
                    ::boost::heap::tag::stability_counter_type
                >
              , ::boost::parameter::optional< ::boost::heap::tag::mutable_>
            >
            d_ary_heap_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    ::boost::parameter::deduced<
#endif
                        ::boost::compare_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    >
                  , ::boost::detail::metafunction::is_compare_selector<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    ::boost::parameter::deduced<
#endif
                        ::boost::allocator_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    >
                  , ::boost::detail::metafunction::is_compare_selector<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional< ::boost::heap::tag::stable>
              , ::boost::parameter::optional<
                    ::boost::heap::tag::stability_counter_type
                >
              , ::boost::parameter::optional<
                    ::boost::heap::tag::constant_time_size
                >
            >
            fibonacci_heap_selector_signature;

    typedef fibonacci_heap_selector_signature
            pairing_heap_selector_signature;

    typedef fibonacci_heap_selector_signature
            binomial_heap_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    ::boost::parameter::deduced<
#endif
                        ::boost::compare_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    >
                  , ::boost::detail::metafunction::is_compare_selector<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    ::boost::parameter::deduced<
#endif
                        ::boost::allocator_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX \
 && !defined BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
                    >
                  , ::boost::detail::metafunction::is_compare_selector<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional< ::boost::heap::tag::stable>
              , ::boost::parameter::optional<
                    ::boost::heap::tag::store_parent_pointer
                >
              , ::boost::parameter::optional<
                    ::boost::heap::tag::stability_counter_type
                >
              , ::boost::parameter::optional<
                    ::boost::heap::tag::constant_time_size
                >
              , ::boost::parameter::optional< ::boost::heap::tag::mutable_>
            >
            skew_heap_selector_signature;
}}  // namespace boost::detail

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_DETAIL_SELECTOR_SIGNATURES_HPP_INCLUDED

