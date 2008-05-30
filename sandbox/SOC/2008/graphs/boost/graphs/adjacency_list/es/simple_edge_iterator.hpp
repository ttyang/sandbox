
#ifndef BOOST_GRAPHS_ADJACENCY_LIST_SIMPLE_EDGE_ITERATOR_HPP
#define BOOST_GRAPHS_ADJACENCY_LIST_SIMPLE_EDGE_ITERATOR_HPP

namespace boost {
namespace graphs {
namespace adj_list {

/**
 * The value edge iterator provides a edge iterator unique associative
 * containers and sequences that don't invalidate memory on insertions
 * (lists).
 *
 * By virtue of the fact that the underlying store is not a vector, this
 * iterator is bidirectional but not random access.
 */
template <typename Store>
class simple_edge_iterator
{
    typedef typename Store::const_iterator iterator;
public:
    typedef typename Store::value_type edge_type;
    typedef typename edge_type::descriptor_type edge_descriptor;

    typedef typename iterator::iterator_category iterator_category;
    typedef typename iterator::difference_type difference_type;
    typedef edge_descriptor value_type;
    typedef edge_descriptor reference;
    typedef edge_descriptor pointer;

    inline simple_edge_iterator();
    inline simple_edge_iterator(simple_edge_iterator const& x);
    inline simple_edge_iterator(iterator const& x);

    inline simple_edge_iterator& operator=(simple_edge_iterator const& x);
    inline simple_edge_iterator& operator++();
    inline simple_edge_iterator& operator--();

    inline reference operator*();

    inline bool operator==(simple_edge_iterator const& x) const;
    inline bool operator!=(simple_edge_iterator const& x) const;

private:
    iterator iter;
};

template <typename S>
simple_edge_iterator<S>::simple_edge_iterator()
    : iter()
{ }

template <typename S>
simple_edge_iterator<S>::simple_edge_iterator(simple_edge_iterator const& x)
    : iter(x.iter)
{ }

template <typename S>
simple_edge_iterator<S>::simple_edge_iterator(iterator const& x)
    : iter(x)
{ }

template <typename S>
simple_edge_iterator<S>&
simple_edge_iterator<S>::operator=(simple_edge_iterator<S> const& x)
{
    iter = x.iter;
    return *this;
}

template <typename S>
simple_edge_iterator<S>&
simple_edge_iterator<S>::operator++()
{
    ++iter;
    return *this;
}

template <typename S>
simple_edge_iterator<S>&
simple_edge_iterator<S>::operator--()
{
    --iter;
    return *this;
}

template <typename S>
typename simple_edge_iterator<S>::reference
simple_edge_iterator<S>::operator*()
{
    return &const_cast<edge_type&>(*iter);
}

template <typename S>
bool
simple_edge_iterator<S>::operator==(simple_edge_iterator const& x) const
{ return iter == x.iter; }

template <typename S>
bool
simple_edge_iterator<S>::operator!=(simple_edge_iterator const& x) const
{
    return iter != x.iter;
}

} /* namespace adj_list */
} /* namespace graphs */
} /* namespace boost */

#endif
