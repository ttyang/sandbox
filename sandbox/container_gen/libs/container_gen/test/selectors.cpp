// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TYPEOF_COMPLIANT

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/is_reversible_selector.hpp>
#include <boost/container_gen/is_random_access_selector.hpp>
#include <boost/container_gen/is_associative_selector.hpp>
#include <boost/container_gen/is_unique_assoc_selector.hpp>
#include <boost/container_gen/is_multiple_assoc_selector.hpp>
#include <boost/container_gen/is_hashed_assoc_selector.hpp>
#include <boost/container_gen/is_flat_assoc_selector.hpp>
#include <boost/container_gen/is_ptr_selector.hpp>
#include <boost/container_gen/is_recursive_selector.hpp>
#include <boost/container_gen/is_tr1_selector.hpp>
#include <boost/container_gen/has_stable_iters_selector.hpp>

#if defined BOOST_MPL_CFG_NO_HAS_XXX || defined BOOST_TYPEOF_EMULATION
#include <boost/typeof/std/vector.hpp>
#include <boost/typeof/std/deque.hpp>
#include <boost/typeof/std/list.hpp>
#include <boost/typeof/std/set.hpp>
#include <boost/typeof/std/map.hpp>
#include <boost/typeof/boost/ptr_container/ptr_vector.hpp>
#include <boost/typeof/boost/ptr_container/ptr_deque.hpp>
#include <boost/typeof/boost/ptr_container/ptr_list.hpp>
#include <boost/typeof/boost/ptr_container/ptr_set.hpp>
#include <boost/typeof/boost/ptr_container/ptr_map.hpp>

#if !defined BOOST_MSVC
#include <boost/typeof/std/tr1/array.hpp>
#include <boost/typeof/boost/array.hpp>
#include <boost/typeof/boost/ptr_container/ptr_array.hpp>
#endif

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/std/slist.hpp>
#include <boost/typeof/std/hash_set.hpp>
#include <boost/typeof/std/hash_map.hpp>
#else
#include <boost/typeof/std/tr1/unordered_set.hpp>
#include <boost/typeof/std/tr1/unordered_map.hpp>
#include <boost/typeof/boost/unordered/unordered_set.hpp>
#include <boost/typeof/boost/unordered/unordered_map.hpp>
#include <boost/typeof/boost/ptr_container/ptr_unordered_set.hpp>
#include <boost/typeof/boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/typeof/boost/container/vector.hpp>
#include <boost/typeof/boost/container/stable_vector.hpp>
#include <boost/typeof/boost/container/deque.hpp>
#include <boost/typeof/boost/container/list.hpp>
#include <boost/typeof/boost/container/slist.hpp>
#include <boost/typeof/boost/container/set.hpp>
#include <boost/typeof/boost/container/map.hpp>
#include <boost/typeof/boost/container/flat_set.hpp>
#include <boost/typeof/boost/container/flat_map.hpp>
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_MPL_CFG_NO_HAS_XXX, BOOST_TYPEOF_EMULATION

#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::vecS>));
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::dequeS>));
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::listS>));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::slistS>));
#endif
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::setS>));
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::mapS>));
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::multisetS>));
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::multimapS>));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::hash_setS>));
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::hash_mapS>));
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::hash_multisetS>));
    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<boost::hash_multimapS>));
#endif
    BOOST_MPL_ASSERT((boost::is_ptr_selector<boost::ptr_vecS>));
    BOOST_MPL_ASSERT((boost::is_ptr_selector<boost::ptr_dequeS>));
    BOOST_MPL_ASSERT((boost::is_ptr_selector<boost::ptr_listS>));
    BOOST_MPL_ASSERT((boost::is_ptr_selector<boost::ptr_setS>));
    BOOST_MPL_ASSERT((boost::is_ptr_selector<boost::ptr_mapS>));
    BOOST_MPL_ASSERT((boost::is_ptr_selector<boost::ptr_multisetS>));
    BOOST_MPL_ASSERT((boost::is_ptr_selector<boost::ptr_multimapS>));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT((
        boost::is_ptr_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_ptr_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_ptr_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_ptr_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::hash_multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::hash_multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<boost::flat_multimapS>
    ));
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::listS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::slistS>
    ));
#endif
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::hash_multimapS>
    ));
#endif
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::ptr_multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::hash_multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_reversible_selector<boost::hash_multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_reversible_selector<boost::flat_multimapS>
    ));
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT((
        boost::is_random_access_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_random_access_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::listS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::slistS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::hash_multimapS>
    ));
#endif
    BOOST_MPL_ASSERT((
        boost::is_random_access_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_random_access_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::ptr_multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_random_access_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_random_access_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_random_access_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::hash_multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::hash_multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_random_access_selector<boost::flat_multimapS>
    ));
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::listS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::slistS>
    ));
#endif
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::hash_multimapS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::ptr_multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::hash_multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::hash_multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_associative_selector<boost::flat_multimapS>
    ));
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::listS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::slistS>
    ));
#endif
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::hash_multimapS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::ptr_multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<
            boost::hash_multiset_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<
            boost::hash_multimap_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_unique_associative_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<boost::flat_multimapS>
    ));
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::listS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::slistS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::hash_multimapS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::ptr_multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<
            boost::multiset_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<
            boost::multimap_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<
            boost::hash_set_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<
            boost::hash_map_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<
            boost::hash_multiset_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<
            boost::hash_multimap_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_multiple_associative_selector<boost::flat_multimapS>
    ));
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::listS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::slistS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::hash_multimapS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::ptr_multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<
            boost::hash_multiset_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT((
        boost::is_hashed_associative_selector<
            boost::hash_multimap_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<boost::flat_multimapS>
    ));
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::listS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::slistS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::hash_multimapS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::hash_multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_flat_associative_selector<boost::hash_multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_flat_associative_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_flat_associative_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_flat_associative_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_flat_associative_selector<boost::flat_multimapS>
    ));
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::listS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::multimapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_multimapS>
    ));
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::slistS>
    ));
#endif
#if defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<boost::hash_multimapS>
    ));
#endif
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::hash_multimapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::slistS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::hash_multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::hash_multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<boost::flat_multimapS>
    ));
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::listS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::slistS>
    ));
#endif
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::hash_multimapS>
    ));
#endif
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::ptr_multimapS>
    ));
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<
            boost::hash_multiset_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<
            boost::hash_multimap_selector<true_>
        >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::has_stable_iterators_selector<boost::flat_multimapS>
    ));
#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

MPL_TEST_CASE()
{
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::listS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::slistS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::hash_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_dequeS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_listS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_hash_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_hash_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_hash_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::ptr_hash_multimapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::vector_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::stable_vecS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::deque_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::list_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::set_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::map_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_tr1_selector<boost::hash_set_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_tr1_selector<boost::hash_map_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_tr1_selector<boost::hash_multiset_selector<true_> >
    ));
    BOOST_MPL_ASSERT((
        boost::is_tr1_selector<boost::hash_multimap_selector<true_> >
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::flat_setS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::flat_mapS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::flat_multisetS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<boost::flat_multimapS>
    ));
}

#endif  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if !defined BOOST_MSVC
// size_t ambiguity

MPL_TEST_CASE()
{
    typedef boost::array_selector<int_<1> > exArrayS;
    typedef boost::array_selector<int_<1>,true_> exTR1ArrayS;
    typedef boost::ptr_array_selector<int_<1> > exPtrArrayS;

    BOOST_MPL_ASSERT_NOT((boost::is_ptr_selector<exArrayS>));
    BOOST_MPL_ASSERT((boost::is_random_access_selector<exArrayS>));
    BOOST_MPL_ASSERT_NOT((boost::is_associative_selector<exArrayS>));
    BOOST_MPL_ASSERT_NOT((boost::is_unique_associative_selector<exArrayS>));
    BOOST_MPL_ASSERT_NOT((boost::is_multiple_associative_selector<exArrayS>));
    BOOST_MPL_ASSERT_NOT((boost::is_hashed_associative_selector<exArrayS>));
    BOOST_MPL_ASSERT_NOT((boost::is_recursive_selector<exArrayS>));
    BOOST_MPL_ASSERT_NOT((boost::is_tr1_selector<exArrayS>));
    BOOST_MPL_ASSERT((boost::has_stable_iterators_selector<exArrayS>));

    BOOST_MPL_ASSERT_NOT((
        boost::is_ptr_selector<exTR1ArrayS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_random_access_selector<exTR1ArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<exTR1ArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<exTR1ArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<exTR1ArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<exTR1ArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_recursive_selector<exTR1ArrayS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_tr1_selector<exTR1ArrayS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<exTR1ArrayS>
    ));

    BOOST_MPL_ASSERT((
        boost::is_ptr_selector<exPtrArrayS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_random_access_selector<exPtrArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_associative_selector<exPtrArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_unique_associative_selector<exPtrArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_multiple_associative_selector<exPtrArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_hashed_associative_selector<exPtrArrayS>
    ));
    BOOST_MPL_ASSERT((
        boost::is_recursive_selector<exPtrArrayS>
    ));
    BOOST_MPL_ASSERT_NOT((
        boost::is_tr1_selector<exPtrArrayS>
    ));
    BOOST_MPL_ASSERT((
        boost::has_stable_iterators_selector<exPtrArrayS>
    ));
}

#endif  // BOOST_MSVC

