/* Copyright (C) 2011 Étienne Dupuis
 * 
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 */

#include <M:/Boost/Sandbox/pool/boost/pool/static_pool.hpp>

#include <boost/assert.hpp>
#include <boost/detail/lightweight_test.hpp>

// Allocator that checks whether malloc() is called only once

struct user_allocator_once
{
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  static char * malloc BOOST_PREVENT_MACRO_SUBSTITUTION(const size_type bytes)
  {
		BOOST_TEST(reset);
		reset = false;

    return new (std::nothrow) char[bytes];
  }

  static void free BOOST_PREVENT_MACRO_SUBSTITUTION(char * const block)
  {
    delete [] block;
  }

	static bool reset;
};

bool user_allocator_once::reset = false;

// Main set of test

static void test_static_pool()
{
	static const int pool_size = 24;                     // Initial size of pool
	static const int num_iterations = pool_size + 8;     // Number of mallocs we will try on pool
	static const int consecutive_elements = 5;           // Number of consecutive elements we will request

	void *p[num_iterations];

	user_allocator_once::reset = true;
	boost::static_pool<user_allocator_once> pool(sizeof(int), pool_size);

	for (int n = 0; n < 2; n++)
	{
		// TEST #1
		for (int k = 0; k < num_iterations; k++)
		{
			p[k] = pool.malloc();
			BOOST_TEST((p[k] != NULL) == (k < pool_size));
		}

		for (int k = 0; k < num_iterations; k++)
			BOOST_ASSERT(!p[k] || pool.is_from(p[k]));

		for (int k = 0; k < num_iterations; k++)
			p[k] ? pool.ordered_free(p[k]) : (void)(0);

		// TEST #2
		for (int k = 0; k < num_iterations; k++)
		{
			p[k] = pool.ordered_malloc(consecutive_elements);
			BOOST_TEST((p[k] != NULL) == (k < pool_size / consecutive_elements));
		}

		for (int k = 0; k < num_iterations; k++)
			p[k] ? pool.ordered_free(p[k], consecutive_elements) : (void)(0);

		// TEST #3
		for (int k = 0; k < num_iterations; k++)
		{
			p[k] = pool.malloc();
			BOOST_TEST((p[k] != NULL) == (k < pool_size));
		}

		for (int k = 0; k < num_iterations; k++)
			p[k] ? pool.free(p[k]) : (void)(0);

		// TEST #4

		srand(NULL);

		int allocated = 0;
		for (int k = 0; k < pool_size / 2; k++)
			p[allocated++] = pool.malloc();

		for (int k = 0; k < 100 * num_iterations; k++)
		{
			if ((rand() & 8) && (allocated < pool_size))
			{
				p[allocated++] = pool.malloc();
			}
			else if (allocated > 0)
			{
				void *_p = p[--allocated];
				BOOST_TEST(_p && pool.is_from(_p));
				pool.free(_p);
			}
		}

		while (allocated > 0)
			pool.free(p[--allocated]);
	}
}

// Main

int main()
{
	test_static_pool();
	return 0;
}
