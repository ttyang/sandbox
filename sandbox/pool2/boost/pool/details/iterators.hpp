#ifndef BOOST_POOL_DETAILS_ITERATORS
#define BOOST_POOL_DETAILS_ITERATORS

/* -------------------------------------------------------------------------- */
/* -- boost::pool::obvious_iterator                                        -- */
/* -------------------------------------------------------------------------- */

/** ----------------------------------------------------------------------------
 * An "obvious iterator" is an iterator derived from an object which implements
 * the [] operator to access it's elements.
 *
 * The implementation uses boost::iterator_facade for convenience.
 *
 * \tparam Collection
 *         Container class which implements the [] operators to access it's
 *         elements.
 * \tparam Element
 *         Type of the element contained by the Collection class.
 * -------------------------------------------------------------------------- */

template<typename Collection, typename Element>
class obvious_iterator : public boost::iterator_facade<obvious_iterator<Collection, Element>, Element, boost::random_access_traversal_tag>
{
	public :
		obvious_iterator() {}
		obvious_iterator(Collection& collection, size_t index = 0) : _collection(&collection), _index(index) {}

	protected :
		friend class boost::iterator_core_access;
		typedef boost::iterator_facade<obvious_iterator<Collection, Element>, Element, boost::random_access_traversal_tag> Base;

		inline void increment()
			{ advance(1); }
		inline void decrement()
			{ advance(-1); }
		inline void advance(typename Base::difference_type n)
			{ _index += n; }

		inline typename Base::reference dereference() const
			{ return (*_collection)[_index]; }
		
		inline bool equal(const obvious_iterator& i) const
			{ assert(_collection == i._collection); return _index == i._index; }

		inline typename Base::difference_type distance_to(const obvious_iterator& i) const
			{ return i._index - _index; }

	private :
		Collection *_collection;
		size_t _index;
};

/* -------------------------------------------------------------------------- */

#endif