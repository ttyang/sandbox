// Boost.Container StaticVector
// Unit Test

// Copyright (c) 2012 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2012 Andrew Hundt.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_SINGLE_HEADER_UTF
#define BOOST_TEST_MODULE static_vector_tests
#include <boost/test/unit_test.hpp>
#else // BOOST_SINGLE_HEADER_UTF
#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/impl/execution_monitor.ipp>
#endif // BOOST_SINGLE_HEADER_UTF

#include "static_vector_test.hpp"

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <algorithm>

template <typename V, typename SegmentManager>
struct interprocess_strategy
    : public boost::container::strategy::allocator_adaptor<
        boost::interprocess::allocator<V, SegmentManager>
    >
{
    typedef boost::container::strategy::allocator_adaptor<
        boost::interprocess::allocator<V, SegmentManager>
    > base_t;

    explicit interprocess_strategy(SegmentManager * sm) : base_t(sm) {}
};

template <typename T, size_t N>
void test_interprocess(T const& t)
{
    namespace bi = boost::interprocess;
    struct shm_remove
    {
        shm_remove() { bi::shared_memory_object::remove("shared_memory"); }
        ~shm_remove(){ bi::shared_memory_object::remove("shared_memory"); }
    } remover;

    bi::managed_shared_memory shmem(bi::create_only, "shared_memory", 10000 + sizeof(T) * N);

    typedef interprocess_strategy<T, bi::managed_shared_memory::segment_manager> S;
    typedef static_vector<T, N, S> SV;

    SV * sv_ptr = shmem.construct<SV>("my_object")(S(shmem.get_segment_manager()));

    for ( size_t i = 0 ; i < N ; ++i )
        sv_ptr->push_back(T(N - i));

    std::sort(sv_ptr->begin(), sv_ptr->end());

    for ( size_t i = 0 ; i < N ; ++i )
        BOOST_CHECK((*sv_ptr)[i] == T(i + 1));

    {
        T * p = sv_ptr->data();
        for ( size_t i = 0 ; p != sv_ptr->data() + sv_ptr->size() ; ++p, ++i )
            BOOST_CHECK(*p == T(i + 1));
    }

    sv_ptr->assign(N/2, t);
    for ( size_t i = 0 ; i < N/2 ; ++i )
        BOOST_CHECK(sv_ptr->at(i) == t);

    static_vector<int, 10> svvv;
    std::cout << sizeof(svvv) << std::endl;

    shmem.destroy_ptr(sv_ptr);
}

#ifdef BOOST_SINGLE_HEADER_UTF
BOOST_AUTO_TEST_CASE(static_vector_test)
#else // BOOST_SINGLE_HEADER_UTF
int test_main(int, char* [])
#endif // BOOST_SINGLE_HEADER_UTF
{
    BOOST_CHECK(counting_value::count() == 0);

    test_interprocess<int, 10>(50);
    test_interprocess<value_nd, 10>(value_nd(50));
    test_interprocess<counting_value, 10>(counting_value(50));
    BOOST_CHECK(counting_value::count() == 0);
    test_interprocess<shptr_value, 10>(shptr_value(50));

#ifndef BOOST_SINGLE_HEADER_UTF
    return 0;
#endif // BOOST_SINGLE_HEADER_UTF
}
