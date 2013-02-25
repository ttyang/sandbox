#ifndef __BOOST_POOL_POLICIES_HPP
#define __BOOST_POOL_POLICIES_HPP

#ifndef __BOOST_POOL_HPP
#error Please include <boost/pool.hpp>
#endif

/* -------------------------------------------------------------------------- */
/* -- typedef boost::pools::growth_policy                                  -- */
/* -------------------------------------------------------------------------- */

namespace pools
{
	/** --------------------------------------------------------------------------
	 * Pool growth policy function.
	 * The pool growth policy function controls how a pool grows if it runs out
	 * of buffers. 
	 * \param poolSize
	 *        Current number of buffers allocated by the pool.
	 * \return
	 *        Number of new buffers the pool should allocate. The returned value
	 *        can be zero, in which case the pool will no longer grow.
	 * ------------------------------------------------------------------------ */
	typedef size_t (*growth_policy)(size_t poolSize);

	/** --------------------------------------------------------------------------
	 * No growth policy function.
	 * This pools::policy function always return 0, regardless of the pool size.
	 * Hence it describes a pool which never grows.
	 * ----------------------------------------------------------------------- */
	/*static*/ size_t policy_no_growth(size_t)
	{
		return 0;
	}

	/** --------------------------------------------------------------------------
	 * Constant growth policy function.
	 * This pools::policy function returns a constant, regardless of the pool size.
	 * Hence it describes a pool which grows linearly.
	 * \tparam N 
	 *         Value returned by the policy function. There is no default value
	 *         for this parameter.
	 * ------------------------------------------------------------------------- */
	template<size_t N>
	static size_t policy_constant_growth(size_t)
	{
		return N;
	}

	/** --------------------------------------------------------------------------
	 * Exponential growth policy function.
	 * This pools::policy function returns a multiple of the current pool size.
	 * Hence it describes a pool which grows exponentially. An example of such
	 * an exponential growth is a pool which doubles its size when it runs out 
	 * of buffers.
	 * \tparam M
	 *         Numerator of the multiplicative factor applied to the pool size. 
	 *         Given template parameter M, the pool size after
	 *         growing will be M times the actual pool size. Use M = 2 for 
   *         a pool that should double its size whenever it runs out of buffers.
	 * \tparam N
	 *         Denominator of the multiplicative factor applied to the pool size.
	 *         Given template parameters M and N, the pool size after
	 *         growing will be M/N times the actual pool size. It is required
	 *         that N is greater than zero and M greater or equal than N.
	 *         N has a default value, one. If M equals N, then the pool can
	 *         not grow. Otherwise, this function ensures that the pool will grow by
	 *         at least one buffer.
	 * ------------------------------------------------------------------------- */
	template<size_t M, size_t N>
	static size_t policy_exponential_growth(size_t s)
	{
		/* -- Invalid parameters -- */

		BOOST_STATIC_ASSERT(M >= N);
		BOOST_STATIC_ASSERT(N > 0);

		if (!N || M <= N)
			return 0;

		/* -- Compute M/N -- */

		size_t Q = M / N;
		size_t R = M % N;

		/* -- Perform multiplication, taking care of overflows -- */

		if (!Q || (std::numeric_limits<size_t>::max() / Q < s))
			return 0;

		size_t size = (R && (std::numeric_limits<size_t>::max() / R < s)) ? (Q * s + R * (s / N)) : (Q * s + R * s / N);

		if (size < Q * s)
			return 0;

		/* -- Return result -- */

		return size ? size : 1;
	}

	/** --------------------------------------------------------------------------
	 * Exponential growth policy function with N = 1
	 * ------------------------------------------------------------------------- */
	template<size_t M>
	static size_t policy_exponential_growth(size_t s)
	{
		return policy_exponential_growth<M, 1>(s);
	}
}

/* -------------------------------------------------------------------------- */
/* -- Class boost::pools::policy                                           -- */
/* -------------------------------------------------------------------------- */

namespace pools
{
	class policy
	{
		public :
			policy(size_t initialPoolSize) : _initialPoolSize(initialPoolSize), _maximalPoolSize(initialPoolSize), _growth(policy_no_growth) {}
			policy(size_t initialPoolSize, growth_policy growth) : _initialPoolSize(initialPoolSize), _maximalPoolSize(std::numeric_limits<size_t>::max()), _growth(growth) {}
			policy(size_t initialPoolSize, size_t maximalPoolSize, growth_policy growth) : _initialPoolSize(initialPoolSize), _maximalPoolSize(maximalPoolSize), _growth(growth) {}

		public :
			size_t growth(size_t poolSize) const;

		private :
			size_t _initialPoolSize;
			size_t _maximalPoolSize;
			growth_policy _growth;
	};

	/* -------------------------------------------------------------------------- */

	inline 
	size_t policy::growth(size_t poolSize) const
	{
		/* -- Coherency checks -- */
	
		assert(poolSize <= _maximalPoolSize);

		/* -- Return pool growth -- */

		return std::min(_maximalPoolSize - poolSize, poolSize ? (*_growth)(poolSize) : _initialPoolSize);
	}

	/* -------------------------------------------------------------------------- */
}

/* -------------------------------------------------------------------------- */

#endif
