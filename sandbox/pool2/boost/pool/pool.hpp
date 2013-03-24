#ifndef __BOOST_POOL_HPP
#define __BOOST_POOL_HPP

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/iterator/iterator_facade.hpp>

#ifdef BOOST_MSVC
	#pragma warning(disable: 4996)  // Function call with parameters that may be unsafe
#endif

#include <algorithm>  // std::copy, std::sort
#include <cassert>    // assert
#include <cstddef>    // size_t
#include <limits>     // std:numeric_limits
#include <memory>     // std::allocator

#include <boost/array.hpp>   // std::array

#include <boost/tr1/type_traits.hpp>

#ifdef BOOST_POOL_VALGRIND
	#include <valgrind/memcheck.h>
#endif

#ifdef BOOST_MSVC
	#pragma warning(push)
	#pragma warning(disable: 4127)  // Conditional expression is constant
#endif

namespace boost
{

#include "policies.hpp"

/** ----------------------------------------------------------------------------
 * A pool holds memory buffers that are allocated only once.
 *  
 * A pool provides fixed sized buffers of objects. The object type is a pool 
 * template parameter and thus set at compilation time. The buffer size is 
 * the number of objects contained in a single buffer. The pool size is the
 * number of buffers the pool has allocated from memory.
 * 
 * Using a pool is straightforward; once a pool has been initialized, an
 * application requests buffers using pool::request() and releases them 
 * using pool::release(). The pool grows when necessary according to the
 * growth policy set at initialization time.
 * 
 * The pool class has been designed with the following contraints in mind:
 * - The pool is designed for application that needs to reduce the
 *   number of dynamic memory allocations or to have better control on
 *   where the allocated objects are located in memory.
 * - Buffer requests and releases should be extremely fast, unless the
 *   pool must be grown (in which case a memory allocation will occur).
 * - Buffer requests and releases should be thread safe. To meet the 
 *   performance requirement just stated above, lock free synchronization
 *   is used.
 * - Pool buffers are fixed size and the object type contained in the 
 *   buffer is known at compile time. When requesting a buffer, the objects
 *   contained in the buffer are constructed and when the buffer is released,
 *   the objects are destroyed. The objects may of course be basic types (like
 *   char), in which case no construction/destruction process takes place.
 * - Upon destruction, all buffers that have been requested from the pool
 *   but not properly released are automatically released (and their content
 *   destroyed). This feature is slow (i.e. O(n log n), where n is the pool
 *   size) and should be used only if properly releasing all requested buffers
 *   would be slower or too complex for the calling application.
 * - The pool is error proof; it does not fail or throw if invalid parameters
 *   are given. However, if allocation is impossible, pool::request() will
 *   simply return null. However, for performance considerations, the pool does not
 *   check the validity of the buffer released unless asserts are enabled.
 * - When a pool runs out of buffers, it must allocate new ones. This process
 *   is managed by a user defined policy. It is thus possible to define pools
 *   that never grows or grows slower than by the traditionnal size doubling
 *   paradigm.
 * - The pool is valgrind compatible. If BOOST_POOL_VALGRIND is defined,
 *   a requested buffer will be tagged as containing uninitialized memory,
 *   thus enabling to use valgrind's uninitialized memory checks.
 * - The amount of memory allocated by the pool through the user supplied
 *   memory allocator will always be equal to the buffer size in bytes multiplied 
 *   by the number of buffers allocated. The buffer size in bytes will be equal
 *   to the buffer size in number of objects multiplied by the object size,
 *   unless the resulting value is not a multiple of sizeof(void *), in which
 *   case the value will be rounded up. Consequently, it is very inefficient 
 *   to use a pool to store buffers containing a single char or short.
 * 
 * \tparam T
 *         Pool buffer object type. A single buffer holds 'n' of these objects,
 *         where 'n' is a constant chosen at initialization time.
 * \tparam ThreadSafe
 *         Boolean value stating whether the pool request() and release() 
 *         methods are thread safe. [Perhaps this should be always true unless
 *         BOOST_NO_THREADS is defined.]
 * \tparam Allocator
 *         Custom allocator for memory allocation of pool buffers.
 * 
 * -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe = false, class Allocator = std::allocator<char>>
class pool;

/* -------------------------------------------------------------------------- */
/* -- class boost::pool                                                    -- */
/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator>
class pool
{
	private :
		#include "details/pool.hpp"
		#include "details/chunks.hpp"

	public :
		/** ------------------------------------------------------------------------
		 * Creates a new pool.
		 * \param initialPoolSize
		 *        Number of buffers that should be allocated upon pool creation.
		 *        This value can be zero if no allocation is to be performed by the
		 *        constructor. Otherwise, the pool is grown to the given value,
		 *        using pool::grow(). If this allocation fails, no exception is thrown.
		 *        Allocation success can be asserted by checking that pool::allocated()
		 *        returns the initialPoolSize value.
		 * \param bufferSize
		 *        Pool buffer size, in number of T elements. This value can be zero,
		 *        in which case the pool will "allocate" null-sized buffers.
		 * \param policy
		 *        Pool growth policy. See documentation of pools::policy for details
		 *        on how the policy controls the pool growth.
		 * \param allocator
		 *        Custom allocator instance.
		 * ---------------------------------------------------------------------- */
		pool(const pools::policy& policy, size_t bufferSize = 1, const Allocator& allocator = Allocator());

		/** ------------------------------------------------------------------------
		 * Destroys a pool.
		 * The destructor calls pool::purge(), thereby releasing any outstanding
		 * requested buffers that were not properly released before calling the
		 * destructor.
		 *
		 * \warning The pool::purge() function runs with a complexity of O(n log n)
		 *          if there are outstanding buffers to be released, where n is 
		 *          the number of buffers allocated by the pool. Thus better
		 *          performances are obtained when the calling application properly
		 *          releases all allocated buffers before destroying the pool.
		 * ---------------------------------------------------------------------- */
		~pool();

	private :
		/** ------------------------------------------------------------------------
		 * Requests a pool buffer, \b without initializing it's content.
		 * This private function is used by the various flavors of pool::request().
		 * ----------------------------------------------------------------------- */
		T *request_core(void);

	public :
		/** ------------------------------------------------------------------------
		 * Requests and initializes a pool buffer.
		 * This function returns an initialized pool buffer, unless the pool is empty
		 * and can not grow. A pool may not grow if the pools::policy function states
		 * so or if the growth function failed to allocate memory.
		 * \p The request function comes in various flavors to suit up objects with
		 * constructors taking up to nine parameters.
		 * \p This function is thread safe if the ThreadSafe pool template parameter
		 * was set to true. State coherency is achieved using fast lock free atomic 
		 * operations if supported by the host operating system.
		 * \p This function is fast and runs in constant time unless the pool is 
		 * grown and new buffers are allocated.
		 * \p If valgrind support is enabled (by defining BOOST_POOL_VALGRIND), the
		 * buffer memory is labeled as uninitialized before calling the object
		 * constructors, thus enabling the detection of unitialized memory checks
		 * performed by valgrind.
		 * \returns A buffer containing N initialized objects of type T, where N is 
		 *          the pool buffer size given to the constructor. NULL if no buffer
		 *          could be allocated.
		 * \see The documentation of pool::grow() gives more details about the pool
		 *      growth process when there is no more available buffers in the pool.
		 * \see Function pool::release() must be called to release the allocated 
		 *      buffer.
		 * ---------------------------------------------------------------------- */
		T *request(void);

		/** ------------------------------------------------------------------------
		 * Releases and unitializes a pool buffer.
		 * This function destroys the objects in the given buffer and releases it
		 * by adding it to the pool's list of available buffers.
		 * \p This function is thread safe if the ThreadSafe pool template parameter 
		 * was set to true. State coherency is achieved using fast lock free atomic 
		 * operations if supported by the host operating system.
		 * \p This function runs is fast and runs in constant time.
		 * \warning If asserts are enabled (that is if NDEBUG is not defined), this
		 *          function validates that the given buffer comes from this pool.
		 *          This validation requires O(n) comparisons, where n is the number
		 *          of buffers allocated by the pool.
		 * \param buffer
		 *        Buffer previously obtained from pool::request(). It can be NULL,
		 *        in which case this function does nothing.
		 * ---------------------------------------------------------------------- */
		void release(T *buffer);

		template<typename T1>
		T *request(const T1& t1);
		template<typename T1, typename T2>
		T *request(const T1& t1, const T2& t2);
		template<typename T1, typename T2, typename T3>
		T *request(const T1& t1, const T2& t2, const T3& t3);
		template<typename T1, typename T2, typename T3, typename T4>
		T *request(const T1& t1, const T2& t2, const T3& t3, const T4& t4);
		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		T *request(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5);  // AND SO ON...

		/** ------------------------------------------------------------------------
		 * Releases all outstanding buffers.
		 * If there is any outstanding buffers, i.e. if pool::requested() returns 
		 * a non-zero value, this function releases all these buffers, calling
		 * pool::release() for each of them.
		 * \warning This function identifies which buffers must be released using
		 *          a procedure of O(n log n) complexity, where n is the number 
		 *          of buffers allocated by the pool. Of course, this does not 
		 *          apply if pool::requested() returns zero.
		 * \warning This function is not thread safe.
		 * ---------------------------------------------------------------------- */
		void purge();

		/** ------------------------------------------------------------------------
		 * Grows a pool by allocating more buffers.
		 * \param count
		 *        Number of buffers to allocate. This value can be zero, in which
		 *        case the function does nothing (but succeeds).
		 * \return
		 *        Returns false if allocation failed.
		 * ---------------------------------------------------------------------- */
		bool grow(size_t count);

		/** ------------------------------------------------------------------------
		 * Returns the number of buffers allocated by the pool.
		 * ----------------------------------------------------------------------- */
		inline size_t allocated() const
			{ return _allocated; }

		/** ------------------------------------------------------------------------
		 * Returns the number of buffers requested from this pool.
		 * This value is increased by pool::request() and released by pool::release().
		 * ---------------------------------------------------------------------- */
		inline size_t requested() const
			{ return _requested; }

	protected :
		/** ------------------------------------------------------------------------
		 * Returns the size in bytes of a pool buffer.
		 * Returns zero if the computed size would overflow size_t.
		 * ---------------------------------------------------------------------- */
		inline size_t bytes() const 
			{	return (std::numeric_limits<size_t>::max() / sizeof(T) >= _size) ? (_size ? (_size * sizeof(T) + (sizeof(T *) - 1)) & ~(sizeof(T *) - 1) : sizeof(T *)) : 0; }

	private :
		Allocator _allocator;        // Custom allocator. Set by the constructor.
		pools::policy _policy;       // Pool growth policy. Set by the constructor.

		typedef _chunks_t<T> chunks_t;
		typedef _chunk_t<T> chunk_t;

		chunks_t _chunks;            // Allocated memory chunks.
		list_t<T> _list;             // List of free pool buffers.

		mutable size_t _allocated;   // Number of pool buffers that have been allocated. Mutable since it can be computed from '_chunks'.
		mutable size_t _requested;   // Number of pool buffers requested by the application and not yet released. Mutable since it can be computed from '_list'.
		size_t _size;                // Pool buffer sizes, in number of objects.
};

/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator>
pool<T, ThreadSafe, Allocator>::pool(const pools::policy& policy, size_t bufferSize, const Allocator& allocator)
	: _allocator(allocator), _policy(policy), _allocated(0), _requested(0), _size(bufferSize)
{
	grow(_policy.growth(0));
}

/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator>
pool<T, ThreadSafe, Allocator>::~pool()
{
	/* -- Purge pool to destroy any outstanding objects -- */

	purge();

	/* -- Release all pool memory -- */

	for (chunks_t::const_iterator chunk = _chunks.cbegin(); chunk != _chunks.cend(); chunk++)
		_allocator.deallocate(chunk->pointer(), chunk->size());
}

/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator>
void pool<T, ThreadSafe, Allocator>::purge()
{
	/* -- Do not bother in case of POD buffers -- */

	if (std::tr1::has_trivial_destructor<T>::value)
		return;

	/* -- If there is no outstanding buffers, there is nothing to do -- */

	if (!_requested)
		return;

	/* -- Sort allocated chunks and list of free buffers -- */

	_chunks.sort();
	_list.sort();

	/* -- Release missing elements -- */

	list_t<T> list = _list;

	for (chunks_t::const_iterator chunk = _chunks.cbegin(); chunk != _chunks.cend(); chunk++)
		for (T *buffer = chunk->first(); buffer != chunk->last(); buffer = chunk->next(buffer))
			if (list.front() != buffer)
				release(buffer);
			else
				list.pop();

	/* -- Coherency checks -- */

	assert(!_requested);
}

/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator>
bool pool<T, ThreadSafe, Allocator>::grow(size_t count)
{
	/* -- Early exit if no growth is asked for -- */

	if (!count)
		return true;

	/* -- Get buffer size in bytes -- */

	const size_t size = bytes();
	if (!size)
		return false;

	/* -- Assert that the requested number of buffers can be allocated -- */

	if (std::numeric_limits<size_t>::max() / size < count)
		return false;

	/* -- Perform allocation -- */

	chunk_t chunk(_allocator.allocate(size * count), size, count);
	if (!chunk.pointer())
		return false;

	/* -- Keep allocated pointer for purge function -- */

	_chunks.push(chunk);
	_allocated += count;

	/* -- Push newly allocated buffers in list of free buffers -- */

	for (T *buffer = chunk.first(); buffer != chunk.last(); buffer = chunk.next(buffer))
		_list.push(buffer);

	/* -- Done -- */

	return true;
}

/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator>
T *pool<T, ThreadSafe, Allocator>::request_core()
{
	/* -- Try growing the pool if there is no free buffer availables -- */

	if (_list.empty())
		grow(_policy.growth(_allocated));

	/* -- Request a pointer from the free list -- */

	T *buffer = _list.pop();
	if (!buffer)
		return buffer;

	/* -- Valgrind management -- */

#ifdef BOOST_POOL_VALGRIND
	VALGRIND_MAKE_MEM_UNDEFINED(buffer, bytes());
#endif

	/* -- Return requested pool buffer -- */

	_requested += 1;
	return buffer;
}

/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator>
T *pool<T, ThreadSafe, Allocator>::request()
{
	/* -- Request buffer -- */

	T *buffer = request_core();
	if (!buffer)
		return buffer;

	/* -- Construct buffer content, using default constructor -- */

	for (size_t k = 0; k < _size; k++)
		new (&buffer[k]) T();

	/* -- Return requested pool buffer -- */

	return buffer;
}

/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator> template<typename T1>
T *pool<T, ThreadSafe, Allocator>::request(const T1& t1)
{
	/* -- Request buffer -- */

	T *buffer = request_core();
	if (!buffer)
		return buffer;

	/* -- Construct buffer content, using single argument constructor -- */

	for (size_t k = 0; k < _size; k++)
		new (&buffer[k]) T(t1);

	/* -- Return requested pool buffer -- */

	return buffer;
}

/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator> template<typename T1, typename T2>
T *pool<T, ThreadSafe, Allocator>::request(const T1& t1, const T2& t2)
{
	/* -- Request buffer -- */

	T *buffer = request_core();
	if (!buffer)
		return buffer;

	/* -- Construct buffer content, using two arguments constructor -- */

	for (size_t k = 0; k < _size; k++)
		new (&buffer[k]) T(t1, t2);

	/* -- Return requested pool buffer -- */

	return buffer;
}

/* -------------------------------------------------------------------------- */

template<typename T, bool ThreadSafe, class Allocator>
void pool<T, ThreadSafe, Allocator>::release(T *buffer)
{
	/* -- Early exit if given pointer is null -- */

	if (!buffer)
		return;

	/* -- Safety checks -- */

	assert(_requested > 0);
	assert(!_list.contains(buffer));
	assert(_chunks.contains(buffer));

	/* -- Destroy buffer content -- */

	for (size_t k = 0; k < _size; k++)
		buffer[k].~T();

	/* -- Push buffer into free list -- */

	_list.push(buffer);
	_requested -= 1;
}

/* -------------------------------------------------------------------------- */

};

#ifdef BOOST_MSVC
	#pragma warning(pop)
#endif

#endif
