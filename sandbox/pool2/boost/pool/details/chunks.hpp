#ifndef __BOOST_POOL_DETAILS_CHUNKS
#define __BOOST_POOL_DETAILS_CHUNKS

#include "iterators.hpp"

/* -------------------------------------------------------------------------- */
/* -- boost::pool::_chunk_t                                                -- */
/* -------------------------------------------------------------------------- */

/** ----------------------------------------------------------------------------
 * A chunk describes a pointer to a memory space large enough to hold 'count'
 * buffers of 'size' bytes.
 *
 * It provides helper functions to get a pointer to the nth buffer and to check 
 * whether an arbitrary pointer is a valid buffer pointer.
 *
 * \tparam T
 *         Buffer object type, provided for convenience, i.e. for casting
 *         pointers given or returned by this object.
 * -------------------------------------------------------------------------- */

template<typename T>
class _chunk_t
{
	public :
		/** ------------------------------------------------------------------------
		 * Default constructor. All members are left uninitialized.
		 * ---------------------------------------------------------------------- */
		_chunk_t() {}

		/** ------------------------------------------------------------------------
		 * Constructor.
		 * \param pointer
		 *        Memory chunk pointer. It is expected that it's size is equal to
		 *        \p size times \p count and that the alignment constraints of 
		 *        type T are satisfied.
		 * \param size
		 *        Individual buffer size, in bytes. It is assumed that this value
		 *        is a multiple of the alignment constraints of type T.
		 * \param count
		 *        Number of buffers in memory chunk.
		 * ---------------------------------------------------------------------- */
		_chunk_t(char *pointer, size_t size, size_t count) : _pointer(pointer), _size(size), _count(count) {}

		/** ------------------------------------------------------------------------
		 * Returns the memory chunk pointer given to the constructor.
		 * ---------------------------------------------------------------------- */
		inline char *pointer() const
			{ return _pointer; }

		/** ------------------------------------------------------------------------
		 * Returns the size of buffer in bytes, as given to the constructor.
		 * ---------------------------------------------------------------------- */
		inline size_t size() const
			{ return _size; }

		/** ------------------------------------------------------------------------
		 * Returns the number of buffers in the chunk, as given to the constructor.
		 * ---------------------------------------------------------------------- */
		inline size_t count() const
			{ return _count; }

		/** ------------------------------------------------------------------------
		 * Defines a linear order between chunks. Chunks are ordered according to
		 * their memory addresses.
		 * ---------------------------------------------------------------------- */
		inline bool operator<(const _chunk_t& chunk) const
			{ return _pointer < chunk._pointer; }

	public :
		/** ------------------------------------------------------------------------
		 * Returns a pointer to the nth buffer contained in this chunk.
		 * \param n
		 *        Buffer index. This value shall be smaller than the number of
		 *        buffers returned by count().
		 * ---------------------------------------------------------------------- */
		inline T *operator[](size_t n) const
			{ assert(n < _count); return reinterpret_cast<T *>(_pointer + _size * n); }

		/** ------------------------------------------------------------------------
		 * Returns a pointer to the first buffer contained in this chunk. This
		 * function, along with last() and next(), may be used to iterate over the 
		 * buffers of the chunk.
		 * ---------------------------------------------------------------------- */
		inline T *first() const
			{ return reinterpret_cast<T *>(_pointer); }			

		/** ------------------------------------------------------------------------
		 * Returns a pointer to the first buffer past the end of the chunk. This 
		 * function, along with first() and next(), may be used to iterator over the
		 * buffer of the chunk.
		 * ---------------------------------------------------------------------- */
		inline T *last() const
			{ return reinterpret_cast<T *>(_pointer + _size * _count); }

		/** ------------------------------------------------------------------------
		 * Returns the next chunk buffer, given one. This function, along with
		 * first() and last(), can be used to iterate over all buffers of a chunk.
		 * \param buffer
		 *        Valid chunk buffer, as asserted with contains(). This pointer
		 *        could have been obtained with first() or a previous call to
		 *        next().
		 * ---------------------------------------------------------------------- */
		inline T *next(T *buffer) const
			{ assert(contains(buffer)); return reinterpret_cast<T *>(reinterpret_cast<char *>(buffer) + _size); }

	public :
		/** ------------------------------------------------------------------------
		 * Returns true if the given buffer is part of the chunk.
		 * ---------------------------------------------------------------------- */
		bool contains(const T *buffer) const
		{
			const char *pointer = reinterpret_cast<const char *>(buffer);

			/* -- Check if buffer is contained in memory chunk -- */

			if (pointer < _pointer)
				return false;

			size_t index = _size ? (pointer - _pointer) / _size : 0;
			if (index >= _count)
				return false;

			/* -- Check if pointer is correctly aligned on a buffer boundary -- */

			if (_pointer + _size * index != pointer)
				return false;

			/* -- Everything's fine -- */

			return true;
		}

	private :
		char *_pointer;    // Memory chunk pointer.
		size_t _size;      // Size of a buffer, in bytes.
		size_t _count;     // Number of buffers in chunk.
};

/* -------------------------------------------------------------------------- */
/* -- boost::pool::chunks_t                                                -- */
/* -------------------------------------------------------------------------- */

/** ----------------------------------------------------------------------------
 * Chunks describes a list of _chunk_t chunks. It is a hybrid class between
 * std::array and std::vector. The first N chunks are stored in a statically
 * allocated array while the remainders are stored in a dynamically allocated 
 * one.
 *
 * Functions provided are a small subset of the standard std::vector<chunk_t>.
 *
 * \tparam T
 *         Chunk buffer object type. Chunks will be of type _chunk_t<T>.
 * \tparam N
 *         Maximum number of chunks that can be handled before resorting to
 *         dynamic memory allocation. Defaults to one.
 * \tparam Allocator
 *         Allocator for chunks, if required. Defaults to the standard
 *         allocator for type _chunk_t<T>.
 * -------------------------------------------------------------------------- */

template<typename T, size_t N = 1, class Allocator = std::allocator<_chunk_t<T>>>
class _chunks_t
{
	public :
		/** ------------------------------------------------------------------------
		 * Chunk type.
		 * ---------------------------------------------------------------------- */
		typedef _chunk_t<T> chunk_t;

		/** ------------------------------------------------------------------------
		 * Iterator over chunks.
		 * ---------------------------------------------------------------------- */
		typedef obvious_iterator<_chunks_t, chunk_t> iterator;

		/** ------------------------------------------------------------------------
		 * Constant iterator over chunks.
		 * ---------------------------------------------------------------------- */
		typedef obvious_iterator<const _chunks_t, const chunk_t> const_iterator;

	public :
		/** ------------------------------------------------------------------------
		 * Constructor. Constructs an empty list of chunks.
		 * ---------------------------------------------------------------------- */
		_chunks_t(Allocator allocator = Allocator()) : _allocator(allocator), _pchunks(NULL), _maxChunks(N), _numChunks(0), _sorted(true) {}

		/** ------------------------------------------------------------------------
		 * Returns the number of chunks in list.
		 * ---------------------------------------------------------------------- */
		inline size_t chunks() const
			{ return _numChunks; }

	public :
		/** ------------------------------------------------------------------------
		 * Returns the nth chunk.
		 * ---------------------------------------------------------------------- */
		inline chunk_t& operator[](size_t chunk)
			{ assert(chunk < _numChunks); return (chunk < N) ? _achunks[chunk] : _pchunks[chunk - N]; }

		/** ------------------------------------------------------------------------
		 * Returns the nth chunk.
		 * ---------------------------------------------------------------------- */
		inline const chunk_t& operator[](size_t chunk) const
			{ assert(chunk < _numChunks); return (chunk < N) ? _achunks[chunk] : _pchunks[chunk - N]; }

		/** ------------------------------------------------------------------------
		 * Returns an iterator to the chunk list start.
		 * ---------------------------------------------------------------------- */
		inline iterator begin()
			{ return iterator(*this); }

		/** ------------------------------------------------------------------------
		 * Returns a constant iterator to the chunk list start.
		 * ---------------------------------------------------------------------- */
		inline const_iterator cbegin() const
			{ return const_iterator(*this); }

		/** ------------------------------------------------------------------------
		 * Returns an iterator to the chunk list end.
		 * ---------------------------------------------------------------------- */
		inline iterator end()
			{ return iterator(*this, _numChunks); }

		/** ------------------------------------------------------------------------
		 * Returns a constant iterator to the chunk list end.
		 * ---------------------------------------------------------------------- */
		inline const_iterator cend() const
			{ return const_iterator(*this, _numChunks); }

	public :
		/** ------------------------------------------------------------------------
		 * Adds a chunk to the chunk list.
		 *
		 * This function may allocate memory if the chunk list is full, in which
		 * case the list size will be doubled. It is expected that the pool growth
		 * policy is defined as to keep this list small.
		 *
		 * Returns false in case of memory allocation failure.
		 * ---------------------------------------------------------------------- */
		bool push(const chunk_t& chunk)
		{
			/* -- Grow list of chunks if it is full, doubling it's capacity -- */

			if (_numChunks >= _maxChunks)
			{
				size_t maxChunks = 2 * _numChunks;		
				chunk_t *pchunks = _allocator.allocate(maxChunks - N);
				if (!pchunks)
					return false;

				std::copy(_pchunks, _pchunks + _numChunks - N, pchunks);
				_allocator.deallocate(_pchunks, _maxChunks - N);

				_pchunks = pchunks;
				_maxChunks = maxChunks;
			}

			/* -- Insert new chunk -- */

			(*this)[++_numChunks] = chunk;

			/* -- Update sorted state -- */

			if (_sorted && (_numChunks > 1))
				if ((*this)[_numChunks - 1] < (*this)[_numChunks - 2])
					_sorted = false;

			/* -- Done -- */

			return true;
		}

		/** ------------------------------------------------------------------------
		 * Sorts the chunk lists, by increasing order of memory addresses.
		 * ---------------------------------------------------------------------- */
		void sort()
		{
			if (!_sorted)
				std::sort(begin(), end());

			_sorted = true;
		}

		/** ------------------------------------------------------------------------
		 * Returns true if the given buffer is a valid buffer from one of the
		 * chunks in chunk list, using _chunk_t::contains().
		 * ---------------------------------------------------------------------- */
		bool contains(const T *buffer) const
		{
			for (size_t chunk = 0; chunk < _numChunks; chunk++)
				if ((*this)[chunk].contains(buffer))
					return true;

			return false;
		}

	private :
		Allocator _allocator;   // Allocator.

		chunk_t _achunks[N];    // Chunks, static array.
		chunk_t *_pchunks;      // Chunks, dynamic array.

		size_t _maxChunks;      // Maximum number of chunks that may be holded.
		size_t _numChunks;      // Number of chunks holded.

		mutable bool _sorted;   // True if chunk list is sorted.
};
 
/* -------------------------------------------------------------------------- */

#endif