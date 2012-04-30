/* Copyright (C) 2011 Étienne Dupuis
 * 
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/pool/static_pool.hpp>
#include <boost/pool/object_pool.hpp>

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

// Object that counts the number of calls to constructor / destructor

class Count
{
	public :
		static int count;
		Count() { count += 1; }
		~Count() { count -= 1; }
};

int Count::count = 0;

// Testing static_pool

template<int SIZE>
void test_static_pool()
{
	static const int pool_size = 24;                     // Initial size of pool
	static const int num_iterations = pool_size + 8;     // Number of mallocs we will try on pool in following tests
	static const int num_random_iterations = 2000;       // Number of iterations for test #4 that follows
	static const int consecutive_elements = 5;           // Number of consecutive elements we will request

	void *p[num_iterations];

	user_allocator_once::reset = true;
	boost::static_pool<user_allocator_once> pool(SIZE, pool_size);

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

		for (int k = 0; k < num_random_iterations; k++)
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

// Testing static_object_pool

template<typename T>
void test_static_object_pool()
{
	static const int pool_size = 24;                     // Initial size of pool
	static const int num_random_iterations = 200;        // Number of iterations f

	user_allocator_once::reset = true;
	boost::static_object_pool<T, user_allocator_once> pool(pool_size);

	T *p[pool_size];

	// TEST #1

	srand(NULL);

	int allocated = 0;
	for (int k = 0; k < pool_size / 2; k++)
		p[allocated++] = pool.construct();

	for (int k = 0; k < num_random_iterations; k++)
	{
		if ((rand() & 8) && (allocated < pool_size))
		{
			p[allocated++] = pool.construct();
		}
		else if (allocated > 0)
		{
			pool.destroy(p[--allocated]);
		}

		BOOST_TEST(Count::count == allocated);
	}

	while (allocated < pool_size / 4)
		p[allocated++] = pool.construct();
}

// Main

int main()
{
	test_static_pool<8>();
	test_static_object_pool<Count>();
	BOOST_TEST(Count::count == 0);

	return 0;
}
