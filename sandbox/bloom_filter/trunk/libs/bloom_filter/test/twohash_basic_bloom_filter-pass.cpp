//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Alejandro Cabrera 2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/bloom_filter for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#define BOOST_TEST_DYN_LINK 1
#define BOOST_TEST_MODULE "Boost Bloom Filter" 1

#include <boost/bloom_filter/twohash_basic_bloom_filter.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

using boost::bloom_filters::twohash_basic_bloom_filter;
using boost::bloom_filters::boost_hash;
using boost::bloom_filters::murmurhash3;
using boost::bloom_filters::detail::cube;

BOOST_AUTO_TEST_CASE(defaultConstructor) {
  twohash_basic_bloom_filter<int, 8> bloom;
  twohash_basic_bloom_filter<int, 8, 16> sixteen_hash_value_bloom;
  twohash_basic_bloom_filter<int, 8, 16, 2> two_expected_insertion_count_bloom;
  twohash_basic_bloom_filter<int, 8, 16, 2, 
			     murmurhash3<int> > all_murmurhash_bloom;

  twohash_basic_bloom_filter<int, 8, 16, 2,
			     murmurhash3<int>,
			     boost_hash<int, 0> > hash_configured_bloom;

  twohash_basic_bloom_filter<int, 8, 16, 2,
			     murmurhash3<int>,
			     boost_hash<int, 0>, cube> cube_extender_bloom;
}

BOOST_AUTO_TEST_CASE(rangeConstructor) {
  int elems[5] = {1,2,3,4,5};
  twohash_basic_bloom_filter<int, 8> bloom(elems, elems+5);

  BOOST_CHECK_EQUAL(bloom.count(), 5ul);
}

#ifndef BOOST_NO_0X_HDR_INITIALIZER_LIST
BOOST_AUTO_TEST_CASE(initListConstructor) {
  twohash_basic_bloom_filter<int, 8> bloom = {1,2,3,4,5};

  BOOST_CHECK_EQUAL(bloom.count(), 5ul);
}
#endif

BOOST_AUTO_TEST_CASE(copyConstructor) {
  int elems[5] = {1,2,3,4,5};
  twohash_basic_bloom_filter<int, 8> bloom1(elems, elems+5);
  twohash_basic_bloom_filter<int, 8> bloom2(bloom1);

  BOOST_CHECK_EQUAL(bloom1.count(), bloom2.count());
}

BOOST_AUTO_TEST_CASE(assignment)
{
  twohash_basic_bloom_filter<int, 8> bloom1;
  twohash_basic_bloom_filter<int, 8> bloom2;

  for (size_t i = 0; i < 8; ++i) {
    bloom1.insert(i);
    BOOST_CHECK_EQUAL(bloom1.probably_contains(i), true);
  }

  bloom2 = bloom1;

  for (size_t i = 0; i < 8; ++i) {
    BOOST_CHECK_EQUAL(bloom2.probably_contains(i), true);
  }
}

BOOST_AUTO_TEST_CASE(bit_capacity) {
  twohash_basic_bloom_filter<size_t, 8> bloom_8;
  twohash_basic_bloom_filter<size_t, 256> bloom_256;
  twohash_basic_bloom_filter<size_t, 2048> bloom_2048;
  
  BOOST_CHECK_EQUAL(bloom_8.bit_capacity(), 8ul);
  BOOST_CHECK_EQUAL(bloom_256.bit_capacity(), 256ul);
  BOOST_CHECK_EQUAL(bloom_2048.bit_capacity(), 2048ul);
}

BOOST_AUTO_TEST_CASE(num_hash_values)
{
  twohash_basic_bloom_filter<size_t, 8, 8> bloom_8h;
  twohash_basic_bloom_filter<size_t, 8, 256> bloom_256h;
  twohash_basic_bloom_filter<size_t, 8, 2048> bloom_2048h;
  
  BOOST_CHECK_EQUAL(bloom_8h.num_hash_functions(), 8ul);
  BOOST_CHECK_EQUAL(bloom_256h.num_hash_functions(), 256ul);
  BOOST_CHECK_EQUAL(bloom_2048h.num_hash_functions(), 2048ul);
}

BOOST_AUTO_TEST_CASE(expected_insertion_count)
{
  twohash_basic_bloom_filter<size_t, 8, 2, 8> bloom_8i;
  twohash_basic_bloom_filter<size_t, 8, 2, 256> bloom_256i;
  twohash_basic_bloom_filter<size_t, 8, 2, 2048> bloom_2048i;
  
  BOOST_CHECK_EQUAL(bloom_8i.expected_insertion_count(), 8ul);
  BOOST_CHECK_EQUAL(bloom_256i.expected_insertion_count(), 256ul);
  BOOST_CHECK_EQUAL(bloom_2048i.expected_insertion_count(), 2048ul);
}

BOOST_AUTO_TEST_CASE(empty) {
  twohash_basic_bloom_filter<size_t, 8> bloom;
  
  BOOST_CHECK_EQUAL(bloom.empty(), true);
  bloom.insert(1);
  BOOST_CHECK_EQUAL(bloom.empty(), false);
  bloom.clear();
  BOOST_CHECK_EQUAL(bloom.empty(), true);
}

BOOST_AUTO_TEST_CASE(falsePositiveRate) {
  twohash_basic_bloom_filter<size_t, 64> bloom;

  BOOST_CHECK_EQUAL(bloom.false_positive_rate(), 0.0);

  bloom.insert(1);
  BOOST_CHECK_CLOSE(bloom.false_positive_rate(), 0.00094659, .01);

  bloom.insert(2);
  BOOST_CHECK_CLOSE(bloom.false_positive_rate(), 0.0036708, .01);

  bloom.insert(3);
  BOOST_CHECK_CLOSE(bloom.false_positive_rate(), 0.0080084, .01);

  bloom.insert(4);
  BOOST_CHECK_CLOSE(bloom.false_positive_rate(), 0.013807, .01);

  bloom.insert(5);
  BOOST_CHECK_CLOSE(bloom.false_positive_rate(), 0.020925, .01);

  bloom.insert(6);
  BOOST_CHECK_CLOSE(bloom.false_positive_rate(), 0.029231, .01);

  for (size_t i = 7; i < 5000; ++i)
    bloom.insert(i);
  
  BOOST_CHECK_GE(bloom.false_positive_rate(), 0.6);
  BOOST_CHECK_LE(bloom.false_positive_rate(), 1.0);
}

BOOST_AUTO_TEST_CASE(probably_contains) {
  twohash_basic_bloom_filter<size_t, 8> bloom;

  bloom.insert(1);
  BOOST_CHECK_EQUAL(bloom.probably_contains(1), true);
  BOOST_CHECK_LE(bloom.count(), 3ul);
  BOOST_CHECK_GE(bloom.count(), 1ul);
}

BOOST_AUTO_TEST_CASE(doesNotContain) {
  twohash_basic_bloom_filter<size_t, 8> bloom;

  BOOST_CHECK_EQUAL(bloom.probably_contains(1), false);
}

BOOST_AUTO_TEST_CASE(insertNoFalseNegatives) {
  twohash_basic_bloom_filter<size_t, 2048> bloom;

  for (size_t i = 0; i < 100; ++i) {
    bloom.insert(i);
    BOOST_CHECK_EQUAL(bloom.probably_contains(i), true);
  }
}

BOOST_AUTO_TEST_CASE(rangeInsert) {
  int elems[5] = {1,2,3,4,5};
  twohash_basic_bloom_filter<size_t, 8> bloom;

  bloom.insert(elems, elems+5);
  BOOST_CHECK_EQUAL(bloom.count(), 5ul);
}

BOOST_AUTO_TEST_CASE(clear) {
  twohash_basic_bloom_filter<size_t, 8> bloom;

  for (size_t i = 0; i < 1000; ++i)
    bloom.insert(i);

  bloom.clear();
  BOOST_CHECK_EQUAL(bloom.probably_contains(1), false);
  BOOST_CHECK_EQUAL(bloom.count(), 0ul);
}

BOOST_AUTO_TEST_CASE(memberSwap) {
  size_t elems[5] = {1,2,3,4,5};
  twohash_basic_bloom_filter<size_t, 8> bloom1(elems, elems+2);
  twohash_basic_bloom_filter<size_t, 8> bloom2(elems+2, elems+5);

  bloom1.swap(bloom2);

  BOOST_CHECK_EQUAL(bloom1.count(), 3ul);
  BOOST_CHECK_EQUAL(bloom2.count(), 2ul);
}

BOOST_AUTO_TEST_CASE(testUnion) {
  twohash_basic_bloom_filter<size_t, 300> bloom_1;
  twohash_basic_bloom_filter<size_t, 300> bloom_2;
  twohash_basic_bloom_filter<size_t, 300> bloom_union;

  for (size_t i = 0; i < 100; ++i)
    bloom_1.insert(i);

  for (size_t i = 100; i < 200; ++i)
    bloom_2.insert(i);

  bloom_union = bloom_1 | bloom_2;

  for (size_t i = 0; i < 200; ++i)
    BOOST_CHECK_EQUAL(bloom_union.probably_contains(i), true);
  BOOST_CHECK_GE(bloom_union.count(), bloom_1.count());
  BOOST_CHECK_GE(bloom_union.count(), bloom_2.count());
}

BOOST_AUTO_TEST_CASE(testUnionAssign) {
  twohash_basic_bloom_filter<size_t, 300> bloom_1;
  twohash_basic_bloom_filter<size_t, 300> bloom_union;

  for (size_t i = 0; i < 100; ++i) 
    bloom_1.insert(i);

  bloom_union |= bloom_1;

  for (size_t i = 0; i < 100; ++i)
    BOOST_CHECK_EQUAL(bloom_union.probably_contains(i), true);
  BOOST_CHECK_EQUAL(bloom_union.count(), bloom_1.count());
}

BOOST_AUTO_TEST_CASE(testIntersect) {
  twohash_basic_bloom_filter<size_t, 300> bloom_1;
  twohash_basic_bloom_filter<size_t, 300> bloom_2;
  twohash_basic_bloom_filter<size_t, 300> bloom_intersect;

  // overlap at 100
  for (size_t i = 0; i < 101; ++i) 
    bloom_1.insert(i);
  
  for (size_t i = 100; i < 200; ++i) 
    bloom_2.insert(i);

  bloom_intersect = bloom_1 & bloom_2;

  BOOST_CHECK_LE(bloom_intersect.count(), bloom_1.count());
  BOOST_CHECK_LE(bloom_intersect.count(), bloom_2.count());
  BOOST_CHECK_EQUAL(bloom_intersect.probably_contains(100), true);
}

BOOST_AUTO_TEST_CASE(testIntersectAssign) {
  twohash_basic_bloom_filter<size_t, 300> bloom_1;
  twohash_basic_bloom_filter<size_t, 300> bloom_intersect;

  for (size_t i = 0; i < 100; ++i) 
    bloom_1.insert(i);
  
  bloom_intersect &= bloom_1;

  for (size_t i = 0; i < 100; ++i)
    BOOST_CHECK_EQUAL(bloom_intersect.probably_contains(i), false);
}

BOOST_AUTO_TEST_CASE(globalSwap) {
  size_t elems[5] = {1,2,3,4,5};
  twohash_basic_bloom_filter<size_t, 8> bloom1(elems, elems+2);
  twohash_basic_bloom_filter<size_t, 8> bloom2(elems+2, elems+5);

  swap(bloom1, bloom2);

  BOOST_CHECK_EQUAL(bloom1.count(), 3ul);
  BOOST_CHECK_EQUAL(bloom2.count(), 2ul);
}

BOOST_AUTO_TEST_CASE(equalityOperator) {
  twohash_basic_bloom_filter<int, 8> bloom1;
  twohash_basic_bloom_filter<int, 8> bloom2;

  BOOST_CHECK_EQUAL(bloom1 == bloom2, true);
  bloom1.insert(1);
  BOOST_CHECK_EQUAL(bloom1 == bloom2, false);
  bloom2.insert(1);
  BOOST_CHECK_EQUAL(bloom1 == bloom2, true);
}

BOOST_AUTO_TEST_CASE(inequalityOperator) {
  twohash_basic_bloom_filter<int, 8> bloom1;
  twohash_basic_bloom_filter<int, 8> bloom2;

  BOOST_CHECK_EQUAL(bloom1 != bloom2, false);
  bloom1.insert(1);
  BOOST_CHECK_EQUAL(bloom1 != bloom2, true);
  bloom2.insert(1);
  BOOST_CHECK_EQUAL(bloom1 != bloom2, false);
}
