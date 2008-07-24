
#ifndef ALGORITHM_ITERATOR_HPP
#define ALGORITHM_ITERATOR_HPP

/**
 * Provide an iterator abstraction over algorithm objects. Dereferencing this
 * iterator returns the algorithm which can then be queried for its current
 * state.
 *
 * This is kind of a strange iterator in the sense that it doesn't support
 * post-increment operations. That would require making a copy of underlying
 * algorithm, which would be very, very expensive. Is this a basic iterator
 * concept?
 *
 * @requires Algorithm<Algorithm>
 * 
 * @todo This probably works on any algorithm as long as it provides a next
 * function.
 */
template <typename Algorithm>
struct algorithm_iterator
{
    typedef std::forward_iterator_tag iterator_category;
    typedef std::size_t difference_type;
    typedef Algorithm value_type;
    typedef value_type const& reference;
    typedef value_type const* pointer;

    // Construct an end iterator.
    algorithm_iterator()
        : algo()
    { }

    // Explicitly build an iterator over the state of the given algo.
    algorithm_iterator(Algorithm* algo)
        : algo(algo)
    { }

    inline algorithm_iterator& operator++()
    { algo->next(); return *this; }

    // Return true if this iterator is past the end. An iterator is past the
    // end if a) the algo pointer is null or b) the current edge is null.
    bool end() const
    { return !algo || (algo && !algo->current()); }

    // Two iterators are equivalent if they're both at the end or both refer
    // to the same edge.
    inline bool operator==(algorithm_iterator const& x) const
    {
        return (!algo && x.end())
            || (!x.algo && end())
            || (algo && x.algo && algo->current() == x.algo->current());
    }

    inline bool operator!=(algorithm_iterator const& x) const
    { return !operator==(x); }

    inline reference operator*() const
    { return *algo; }

    inline pointer operator->() const
    { return algo; }

    Algorithm* algo;
};

#endif
