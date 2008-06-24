
#ifndef OUT_LIST_HPP
#define OUT_LIST_HPP

#include <list>

#include <boost/next_prior.hpp>
#include <boost/tuple/tuple.hpp>

/**
 * The out list implements list-based, out-edge storage for directed graphs.
 * out-edges are uniquely identified by their target vertex and property
 * descriptor. List-based stores support fast inserts, slow finds, but do allow
 * removals.
 *

 * @param Edge A tuple describing a vertex descriptor and the edge properties.
 * @param Alloc The allocator for edge pairs.
 */
template <typename Edge, typename Alloc>
class out_list
{
    typedef std::list<Edge, Alloc> store_type;
public:
    typedef Edge out_tuple;
    typedef typename boost::tuples::element<0, Edge>::type vertex_descriptor;
    typedef typename boost::tuples::element<1, Edge>::type edge_properties;
private:
    typedef typename boost::tuples::element<1, Edge>::type in_edge_place;
public:
    typedef typename store_type::iterator iterator;
    typedef typename store_type::size_type size_type;

    inline out_list()
        : _edges()
        , _size(0)
    { }

    /** Allow an edge insertion? */
    std::pair<iterator, bool> allow(vertex_descriptor v) const
    { return std::make_pair(_edges.end(), true); }

    /** Add the edge to the list. */
    iterator add(vertex_descriptor v, edge_properties const& ep)
    {
        ++_size;
        _edges.push_back(out_tuple(v, ep, in_edge_place()));
        return boost::prior(_edges.end());
    }

    /**
     * Remove the edge with the given vertex.
     * @complexity O(1)
     */
    void remove(iterator i)
    {
        --_size;
        _edges.erase(i);
    }

    /** Find the edge with the given vertex. */
    iterator find(vertex_descriptor v) const
    {
        // TODO How do I write this with std::find?
        iterator i = _edges.begin(), end = _edges.end();
        for( ; i != end; ++i) {
            if(i->template get<0>() == v) return i;
        }
        return end;
    }

    /** Remove all incoming edges from the list, resetting the size to 0. */
    void clear()
    {
        _size = 0;
        _edges.clear();
    }

    /** @name Iterators and Size */
    //@{
    inline iterator begin() const
    { return _edges.begin(); }

    inline iterator end() const
    { return _edges.end(); }
    //@}

    /** Get the number of outgoing edges. */
    inline size_type size() const
    { return _size; }

private:
    mutable store_type  _edges;
    size_type           _size;
};

#endif
