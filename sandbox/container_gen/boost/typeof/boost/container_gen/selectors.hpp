//=============================================================================
// Copyright (C) 2012-2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_TYPEOF_BOOST_CONTAINER_GEN_SELECTORS_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_CONTAINER_GEN_SELECTORS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/container_gen/selectors.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/parameter/aux_/void.hpp>
#endif

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::equal_to_selector);
BOOST_TYPEOF_REGISTER_TYPE(::boost::less_than_selector);
BOOST_TYPEOF_REGISTER_TYPE(::boost::greater_than_selector);
BOOST_TYPEOF_REGISTER_TYPE(::boost::boost_hash_selector);
BOOST_TYPEOF_REGISTER_TYPE(::boost::tr1_hash_selector);
BOOST_TYPEOF_REGISTER_TYPE(::boost::std_allocator_selector);
BOOST_TYPEOF_REGISTER_TYPE(::boost::std_flat_allocator_selector);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::vector_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::vector_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::vector_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::vecS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::deque_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::deque_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::deque_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::dequeS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::list_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::list_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::list_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::listS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::set_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::set_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::set_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::set_selector, 3)
BOOST_TYPEOF_REGISTER_TYPE(::boost::setS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::map_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::map_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::map_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::map_selector, 3)
BOOST_TYPEOF_REGISTER_TYPE(::boost::mapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::multiset_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::multiset_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::multiset_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::multiset_selector, 3)
BOOST_TYPEOF_REGISTER_TYPE(::boost::multisetS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::multimap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::multimap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::multimap_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::multimap_selector, 3)
BOOST_TYPEOF_REGISTER_TYPE(::boost::multimapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_vector_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_vector_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_vector_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_vecS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_deque_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_deque_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_deque_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_dequeS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_list_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_list_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_list_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_listS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_set_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_set_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_set_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_set_selector, 3)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_setS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_map_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_map_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_map_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_map_selector, 3)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_mapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multiset_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multiset_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multiset_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multiset_selector, 3)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_multisetS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multimap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multimap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multimap_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multimap_selector, 3)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_multimapS);

#if !defined BOOST_MSVC
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::array_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::array_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_array_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_array_selector, 2)
#endif

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::slist_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::slist_selector, 1)
BOOST_TYPEOF_REGISTER_TYPE(::boost::slistS);
#endif

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_set_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_set_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_set_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_set_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_set_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::hash_setS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_map_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_map_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_map_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_map_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_map_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::hash_mapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multiset_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multiset_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multiset_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multiset_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multiset_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::hash_multisetS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multimap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multimap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multimap_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multimap_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::hash_multimap_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::hash_multimapS);
#endif  // supports partial specialization or has SGI hash

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::stable_vector_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::stable_vector_selector, 1)
BOOST_TYPEOF_REGISTER_TYPE(::boost::stable_vecS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_set_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_set_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_set_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::flat_setS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_map_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_map_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_map_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::flat_mapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_multiset_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_multiset_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_multiset_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::flat_multisetS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_multimap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_multimap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::flat_multimap_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::flat_multimapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_set_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_set_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_set_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_set_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_set_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_hash_setS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_map_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_map_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_map_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_map_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_map_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_hash_mapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multiset_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multiset_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multiset_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multiset_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multiset_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_hash_multisetS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multimap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multimap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multimap_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multimap_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_hash_multimap_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::ptr_hash_multimapS);
#endif  // !BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::stack_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::stack_selector, 1)
BOOST_TYPEOF_REGISTER_TYPE(::boost::stackS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::queue_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::queue_selector, 1)
BOOST_TYPEOF_REGISTER_TYPE(::boost::queueS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::std_heap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::std_heap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::std_heap_selector, 2)
BOOST_TYPEOF_REGISTER_TYPE(::boost::std_heapS);

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::priority_queue_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::priority_queue_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::priority_queue_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::priority_queue_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::priority_queue_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::priority_queueS);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::d_ary_heap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::d_ary_heap_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::d_ary_heap_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::d_ary_heap_selector, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::d_ary_heap_selector, 5)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::d_ary_heap_selector, 6)
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::binomial_heap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::binomial_heap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::binomial_heap_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::binomial_heap_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::binomial_heap_selector, 4)
BOOST_TYPEOF_REGISTER_TYPE(::boost::binomial_heapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::fibonacci_heap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::fibonacci_heap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::fibonacci_heap_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::fibonacci_heap_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::fibonacci_heap_selector, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::fibonacci_heap_selector, 5)
BOOST_TYPEOF_REGISTER_TYPE(::boost::fibonacci_heapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::pairing_heap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::pairing_heap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::pairing_heap_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::pairing_heap_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::pairing_heap_selector, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::pairing_heap_selector, 5)
BOOST_TYPEOF_REGISTER_TYPE(::boost::pairing_heapS);
//BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::skew_heap_selector, 0)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::skew_heap_selector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::skew_heap_selector, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::skew_heap_selector, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::skew_heap_selector, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::skew_heap_selector, 5)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::skew_heap_selector, 6)
BOOST_TYPEOF_REGISTER_TYPE(::boost::skew_heapS);
#endif  // !BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_TYPEOF_BOOST_CONTAINER_GEN_SELECTORS_HPP_INCLUDED

