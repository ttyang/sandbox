//=============================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2010 Thomas Claveirole
// Copyright 2011-2013 Cromwell D. Enage
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Thomas Claveirole,
//          Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_SELECTORS_FWD_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_SELECTORS_FWD_HPP_INCLUDED

#include <memory>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/ptr_container/clone_allocator.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/parameter/aux_/void.hpp>
#endif

namespace boost {

    struct equal_to_selector;
    struct less_than_selector;
    struct greater_than_selector;

    struct boost_hash_selector;
    struct tr1_hash_selector;

    struct std_allocator_selector;
    struct std_flat_allocator_selector;
}  // namespace boost

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost {

#if !defined BOOST_MSVC
    struct array_selector_base;
    struct ptr_array_selector_base;
#endif
    struct vector_selector_base;
    struct deque_selector_base;
    struct list_selector_base;
#if !defined BOOST_NO_SLIST
    struct slist_selector_base;
#endif
    struct set_selector_base;
    struct map_selector_base;
    struct multiset_selector_base;
    struct multimap_selector_base;
#if defined BOOST_HAS_HASH
    struct hash_set_selector_base;
    struct hash_map_selector_base;
    struct hash_multiset_selector_base;
    struct hash_multimap_selector_base;
#endif  // BOOST_HAS_HASH
    struct ptr_vector_selector_base;
    struct ptr_deque_selector_base;
    struct ptr_list_selector_base;
    struct ptr_set_selector_base;
    struct ptr_map_selector_base;
    struct ptr_multiset_selector_base;
    struct ptr_multimap_selector_base;
    struct stack_selector_base;
    struct queue_selector_base;
    struct std_heap_selector_base;
}  // namespace boost
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__container_selector_templates
namespace boost {

//<-
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if !defined BOOST_MSVC
//->
    template <typename ConstantSize, typename IsTR1 = ::boost::mpl::false_>
    struct array_selector;
//<-
#endif
//->

    template <
        typename AllocatorSelector = std_allocator_selector
      , typename IsBoostNotStd = ::boost::mpl::false_
    >
    struct vector_selector;

    template <
        typename AllocatorSelector = std_allocator_selector
      , typename IsBoostNotStd = ::boost::mpl::false_
    >
    struct deque_selector;

    template <
        typename AllocatorSelector = std_allocator_selector
      , typename IsBoostNotStd = ::boost::mpl::false_
    >
    struct list_selector;
//<-
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if !defined BOOST_MSVC
    template <typename T0, typename T1 = ::boost::parameter::void_>
    struct array_selector;
#endif

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct vector_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct deque_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct list_selector;
//->

    template <typename AllocatorSelector = std_allocator_selector>
    struct stable_vector_selector;
//<-
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//->

//<-
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || \
    !defined BOOST_NO_SLIST
//->
    template <typename AllocatorSelector = std_allocator_selector>
    struct slist_selector;
//<-
#endif
//->

//<-
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//->
    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsBoostNotStd = ::boost::mpl::false_
    >
    struct set_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsBoostNotStd = ::boost::mpl::false_
    >
    struct map_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsBoostNotStd = ::boost::mpl::false_
    >
    struct multiset_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsBoostNotStd = ::boost::mpl::false_
    >
    struct multimap_selector;

//<-
#if 0  // for documentation purposes
//->
    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_flat_allocator_selector
    >
    struct flat_set_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_flat_allocator_selector
    >
    struct flat_map_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_flat_allocator_selector
    >
    struct flat_multiset_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_flat_allocator_selector
    >
    struct flat_multimap_selector;
//<-
#endif  // for documentation purposes
//->

//<-
#if defined BOOST_HAS_HASH
//->
    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = equal_to_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsTR1NotBoost = ::boost::mpl::false_
    >
    struct hash_set_selector;

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = equal_to_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsTR1NotBoost = ::boost::mpl::false_
    >
    struct hash_map_selector;

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = equal_to_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsTR1NotBoost = ::boost::mpl::false_
    >
    struct hash_multiset_selector;

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = equal_to_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsTR1NotBoost = ::boost::mpl::false_
    >
    struct hash_multimap_selector;
//<-
#endif  // BOOST_HAS_HASH
//->

//<-
#if !defined BOOST_MSVC
//->
    template <
        typename ConstantSize
      , typename CloneAllocator = ::boost::heap_clone_allocator
    >
    struct ptr_array_selector;
//<-
#endif
//->

    template <
        typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_vector_selector;

    template <
        typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_deque_selector;

    template <
        typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_list_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_set_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_map_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_multiset_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_multimap_selector;

//<-
#if 0  // for documentation purposes
//->
    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = equal_to_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_hash_set_selector;

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = equal_to_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_hash_map_selector;

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = equal_to_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_hash_multiset_selector;

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = equal_to_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_hash_multimap_selector;
//<-
#endif  // for documentation purposes
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    struct set_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    struct map_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    struct multiset_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    struct multimap_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct flat_set_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct flat_map_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct flat_multiset_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct flat_multimap_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct hash_set_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct hash_map_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct hash_multiset_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct hash_multimap_selector;

#if !defined BOOST_MSVC
    template <typename T0, typename T1 = ::boost::parameter::void_>
    struct ptr_array_selector;
#endif

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct ptr_vector_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct ptr_deque_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct ptr_list_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    struct ptr_set_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    struct ptr_map_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    struct ptr_multiset_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
    >
    struct ptr_multimap_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct ptr_hash_set_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct ptr_hash_map_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct ptr_hash_multiset_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct ptr_hash_multimap_selector;
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//->

    template <typename SequenceSelector = deque_selector<> >
    struct stack_selector;

    template <typename SequenceSelector = deque_selector<> >
    struct queue_selector;

//<-
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//->
    template <
        typename CompareSelector = less_than_selector
      , typename SequenceSelector = deque_selector<>
    >
    struct std_heap_selector;

//<-
#if 0  // for documentation purposes
//->
    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsStable = ::boost::heap::stable<false>
      , typename StabilityCounterType = ::boost::heap::stability_counter_type<
            ::boost::uintmax_t
        >
    >
    struct priority_queue_selector;

    template <
        typename Arity
      , typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsStable = ::boost::heap::stable<false>
      , typename StabilityCounterType = ::boost::heap::stability_counter_type<
            ::boost::uintmax_t
        >
      , typename IsMutable = ::boost::heap::mutable_<false>
    >
    struct d_ary_heap_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsStable = ::boost::heap::stable<false>
      , typename StabilityCounterType = ::boost::heap::stability_counter_type<
            ::boost::uintmax_t
        >
    >
    struct binomial_heap_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsStable = ::boost::heap::stable<false>
      , typename StabilityCounterType = ::boost::heap::stability_counter_type<
            ::boost::uintmax_t
        >
      , typename ConstantTimeSize = ::boost::heap::constant_time_size<true>
    >
    struct fibonacci_heap_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsStable = ::boost::heap::stable<false>
      , typename StabilityCounterType = ::boost::heap::stability_counter_type<
            ::boost::uintmax_t
        >
      , typename ConstantTimeSize = ::boost::heap::constant_time_size<true>
    >
    struct pairing_heap_selector;

    template <
        typename CompareSelector = less_than_selector
      , typename AllocatorSelector = std_allocator_selector
      , typename IsStable = ::boost::heap::stable<false>
      , typename StoresParentPointer = ::boost::heap::store_parent_pointer<
            false
        >
      , typename StabilityCounterType = ::boost::heap::stability_counter_type<
            ::boost::uintmax_t
        >
      , typename ConstantTimeSize = ::boost::heap::constant_time_size<true>
      , typename IsMutable = ::boost::heap::mutable_<false>
    >
    struct skew_heap_selector;
//<-
#endif  // for documentation purposes
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
    >
    struct std_heap_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct priority_queue_selector;

    template <
        typename T0
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
      , typename T4 = ::boost::parameter::void_
      , typename T5 = ::boost::parameter::void_
    >
    struct d_ary_heap_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
    >
    struct binomial_heap_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
      , typename T4 = ::boost::parameter::void_
    >
    struct fibonacci_heap_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
      , typename T4 = ::boost::parameter::void_
    >
    struct pairing_heap_selector;

    template <
        typename T0 = ::boost::parameter::void_
      , typename T1 = ::boost::parameter::void_
      , typename T2 = ::boost::parameter::void_
      , typename T3 = ::boost::parameter::void_
      , typename T4 = ::boost::parameter::void_
      , typename T5 = ::boost::parameter::void_
      , typename T6 = ::boost::parameter::void_
    >
    struct skew_heap_selector;
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//->
}  // namespace boost
//]

//[reference__container_selector_typedefs
namespace boost {

    typedef vector_selector<> vecS;
    typedef deque_selector<> dequeS;
    typedef list_selector<> listS;
//<-
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || \
    !defined BOOST_NO_SLIST
//->
    typedef slist_selector<> slistS;
//<-
#endif
//->
    typedef set_selector<> setS;
    typedef map_selector<> mapS;
    typedef multiset_selector<> multisetS;
    typedef multimap_selector<> multimapS;
//<-
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
//->
    typedef hash_set_selector<> hash_setS;
    typedef hash_map_selector<> hash_mapS;
    typedef hash_multiset_selector<> hash_multisetS;
    typedef hash_multimap_selector<> hash_multimapS;
//<-
#endif
//->
    typedef ptr_vector_selector<> ptr_vecS;
    typedef ptr_deque_selector<> ptr_dequeS;
    typedef ptr_list_selector<> ptr_listS;
    typedef ptr_set_selector<> ptr_setS;
    typedef ptr_map_selector<> ptr_mapS;
    typedef ptr_multiset_selector<> ptr_multisetS;
    typedef ptr_multimap_selector<> ptr_multimapS;
//<-
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//->
    typedef ptr_hash_set_selector<> ptr_hash_setS;
    typedef ptr_hash_map_selector<> ptr_hash_mapS;
    typedef ptr_hash_multiset_selector<> ptr_hash_multisetS;
    typedef ptr_hash_multimap_selector<> ptr_hash_multimapS;
    typedef stable_vector_selector<> stable_vecS;
    typedef flat_set_selector<> flat_setS;
    typedef flat_map_selector<> flat_mapS;
    typedef flat_multiset_selector<> flat_multisetS;
    typedef flat_multimap_selector<> flat_multimapS;
//<-
#endif
//->
    typedef stack_selector<> stackS;
    typedef queue_selector<> queueS;
    typedef std_heap_selector<> std_heapS;
//<-
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//->
    typedef priority_queue_selector<> priority_queueS;
    typedef binomial_heap_selector<> binomial_heapS;
    typedef fibonacci_heap_selector<> fibonacci_heapS;
    typedef pairing_heap_selector<> pairing_heapS;
    typedef skew_heap_selector<> skew_heapS;
//<-
#endif
//->
}  // namespace boost
//]

#endif  // BOOST_CONTAINER_GEN_SELECTORS_HPP_INCLUDED

