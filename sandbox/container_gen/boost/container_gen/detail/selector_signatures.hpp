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

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/heap/policies.hpp>
#include <boost/container_gen/selector_keywords.hpp>
#include <boost/container_gen/is_container_selector.hpp>
#include <boost/container_gen/is_compare_selector.hpp>
#include <boost/container_gen/is_hasher_selector.hpp>
#include <boost/container_gen/is_allocator_selector.hpp>

#if !defined BOOST_MPL_CFG_NO_HAS_XXX
#include <boost/utility/is_mpl_integral_constant.hpp>
#include <boost/utility/is_mpl_boolean_constant.hpp>
#include <boost/container_gen/detail/metafunction/is_clone_allocator.hpp>
#include <boost/detail/metafunction/is_allocator.hpp>
#endif

namespace boost { namespace detail {

    typedef ::boost::parameter::parameters<
                ::boost::parameter::required<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::constant_size_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::is_mpl_integral_constant< ::boost::mpl::_>
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::is_tr1_not_boost_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::is_mpl_boolean_constant< ::boost::mpl::_>
#endif
                >
            >
            array_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
                    ::boost::parameter::deduced<
                        ::boost::allocator_selector_tag
                    >
                  , ::boost::is_allocator_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::is_boost_not_std_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::is_mpl_boolean_constant< ::boost::mpl::_>
#endif
                >
            >
            sequence_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
                    ::boost::parameter::deduced< ::boost::compare_selector_tag>
                  , ::boost::is_compare_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
                    ::boost::parameter::deduced<
                        ::boost::allocator_selector_tag
                    >
                  , ::boost::is_allocator_selector< ::boost::mpl::_>
                >
            >
            associative_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
                    ::boost::parameter::deduced< ::boost::compare_selector_tag>
                  , ::boost::is_compare_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
                    ::boost::parameter::deduced<
                        ::boost::allocator_selector_tag
                    >
                  , ::boost::is_allocator_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::is_boost_not_std_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::is_mpl_boolean_constant< ::boost::mpl::_>
#endif
                >
            >
            boost_or_std_assoc_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
                    ::boost::parameter::deduced< ::boost::hasher_selector_tag>
                  , ::boost::is_hasher_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
                    ::boost::parameter::deduced< ::boost::compare_selector_tag>
                  , ::boost::is_compare_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
                    ::boost::parameter::deduced<
                        ::boost::allocator_selector_tag
                    >
                  , ::boost::is_allocator_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::is_tr1_not_boost_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::is_mpl_boolean_constant< ::boost::mpl::_>
#endif
                >
            >
            hashed_associative_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::required<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::constant_size_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::is_mpl_integral_constant< ::boost::mpl::_>
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::ptr_clone_allocator_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::detail::metafunction::is_clone_allocator<
                        ::boost::mpl::_
                    >
#endif
                >
            >
            ptr_array_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::ptr_clone_allocator_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::detail::metafunction::is_clone_allocator<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::ptr_allocator_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::detail::metafunction::is_allocator<
                        ::boost::mpl::_
                    >
#endif
                >
            >
            ptr_sequence_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
                    ::boost::parameter::deduced< ::boost::compare_selector_tag>
                  , ::boost::is_compare_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::ptr_clone_allocator_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::detail::metafunction::is_clone_allocator<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::ptr_allocator_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::detail::metafunction::is_allocator<
                        ::boost::mpl::_
                    >
#endif
                >
            >
            ptr_associative_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
                    ::boost::parameter::deduced< ::boost::hasher_selector_tag>
                  , ::boost::is_hasher_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
                    ::boost::parameter::deduced< ::boost::compare_selector_tag>
                  , ::boost::is_compare_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::ptr_clone_allocator_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::detail::metafunction::is_clone_allocator<
                        ::boost::mpl::_
                    >
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::ptr_allocator_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::detail::metafunction::is_allocator<
                        ::boost::mpl::_
                    >
#endif
                >
            >
            ptr_hashed_assoc_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
                    ::boost::parameter::deduced< ::boost::compare_selector_tag>
                  , ::boost::is_compare_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
                    ::boost::parameter::deduced<
                        ::boost::sequence_selector_tag
                    >
                  , ::boost::is_container_selector< ::boost::mpl::_>
                >
            >
            std_heap_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::optional<
                    ::boost::parameter::deduced< ::boost::compare_selector_tag>
                  , ::boost::is_compare_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
                    ::boost::parameter::deduced<
                        ::boost::allocator_selector_tag
                    >
                  , ::boost::is_allocator_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional< ::boost::heap::tag::stable>
              , ::boost::parameter::optional<
                    ::boost::heap::tag::stability_counter_type
                >
            >
            priority_queue_selector_signature;

    typedef ::boost::parameter::parameters<
                ::boost::parameter::required<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::heap::tag::arity
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::is_mpl_integral_constant< ::boost::mpl::_>
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::compare_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::is_compare_selector< ::boost::mpl::_>
#endif
                >
              , ::boost::parameter::optional<
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    ::boost::parameter::deduced<
#endif
                        ::boost::allocator_selector_tag
#if !defined BOOST_MPL_CFG_NO_HAS_XXX
                    >
                  , ::boost::is_allocator_selector< ::boost::mpl::_>
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
                    ::boost::parameter::deduced< ::boost::compare_selector_tag>
                  , ::boost::is_compare_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
                    ::boost::parameter::deduced<
                        ::boost::allocator_selector_tag
                    >
                  , ::boost::is_allocator_selector< ::boost::mpl::_>
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
                    ::boost::parameter::deduced< ::boost::compare_selector_tag>
                  , ::boost::is_compare_selector< ::boost::mpl::_>
                >
              , ::boost::parameter::optional<
                    ::boost::parameter::deduced<
                        ::boost::allocator_selector_tag
                    >
                  , ::boost::is_allocator_selector< ::boost::mpl::_>
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

