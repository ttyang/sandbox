
#ifndef PROPERTY_LIST_HPP
#define PROPERTY_LIST_HPP

#include <list>
#include <algorithm>

#include <boost/descriptors.hpp>
#include <boost/graphs/utility.hpp>

/**
 * The property list implements global list of properties for node-based edge
 * storage. Note that we can get away with only a list because the edge
 * addition logic is implemented by the incidence list.
 *
 * The property store actually maintains the number of elements internally.
 * Because this store is built over a list, but only allows the insertion and
 * removal of one element at a time, we do this to optimize calls to the size()
 * function (which is used for the number of edges).
 */
template <typename Edge, typename Alloc>
class property_list
{
public:
    typedef std::list<Edge, Alloc> store_type;

    typedef Edge edge_type;
    typedef typename Edge::first_type edge_properties;
    typedef typename Edge::second_type edge_pair;

    typedef typename store_type::iterator iterator;
    typedef typename store_type::size_type size_type;

    typedef typename descriptor_traits<store_type>::descriptor_type property_descriptor;

    // Constructors.
    inline property_list()
        : _props(), _size(0)
    { }

    /** @name Add Property
     * Add a property tot the global set, leaving the incidence descriptors
     * empty for the time being.
     */
    //@{
    inline property_descriptor add()
    { return add(edge_properties()); }

    inline property_descriptor add(edge_properties const& ep)
    {
        ++_size;
        iterator i = _props.insert(_props.end(), make_pair(ep, edge_pair()));
        return make_descriptor(_props, i);
    }
    //@}

    /**
     * Find the edge with the given properties. Finding an edge by its
     * properties is guaranteed to be O(E).
     */
    inline property_descriptor find(edge_properties const& ep) const
    {
        iterator i = std::find_if(_props.begin(), _props.end(), find_first(ep));
        return make_descriptor(_props, i);
    }

    /** Remove the described property from the property set. */
    inline void remove(property_descriptor d)
    {
        _props.erase(make_iterator(_props, d));
        --_size;
    }

    // Property access.
    inline edge_properties& properties(property_descriptor d)
    { return make_iterator(_props, d)->first; }

    /** Bind iterators into the incidence lists into the global property. */
    template <typename Iter>
    void bind(property_descriptor d, Iter src, Iter tgt)
    {
        d.value().second.put(src);
        d.value().third.put(tgt);
    }

    /** Return the number of properties. */
    inline size_type size() const
    { return _size; }

    /** @name Iterators */
    //@{
    inline iterator begin() const
    { return _props.begin(); }

    inline iterator end() const
    { return _props.end(); }
    //@}

private:
    mutable store_type  _props;
    size_type           _size;
};

#endif

