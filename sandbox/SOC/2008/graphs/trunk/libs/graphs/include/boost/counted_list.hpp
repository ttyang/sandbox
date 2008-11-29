
#ifndef BOOST_COUNTED_LIST_HPP
#define BOOST_COUNTED_LIST_HPP

#include <list>
#include <algorithm>

#include <boost/containers.hpp>
#include <boost/descriptors.hpp>

namespace boost {

/**
 * The counted_list is a very simple wrapper around a std::list that maintains
 * the size of the list. We can do this because graph operations don't require
 * any notion of spliceability.
 *
 * The interface to this class is given by functions.
 */
template <typename T, typename Alloc, typename List = std::list<T, Alloc>>
class counted_list
{
    typedef List base_type;
public:
    typedef typename base_type::value_type value_type;
    typedef typename base_type::pointer pointer;
    typedef typename base_type::reference reference;
    typedef typename base_type::const_reference const_reference;
    typedef typename base_type::iterator iterator;
    typedef typename base_type::const_iterator const_iterator;
    typedef typename base_type::reverse_iterator reverse_iterator;
    typedef typename base_type::const_reverse_iterator const_reverse_iterator;
    typedef typename base_type::size_type size_type;

    counted_list()
        : _list(), _size(0)
    { }

    counted_list(counted_list const& x)
        : _list(x._list), _size(x._size)
    { }

    counted_list(counted_list&& x)
        : _list(x._list), _size(x._size)
    { }

    counted_list(size_type n)
        : _list(n), _size(n)
    { }

    counted_list(size_type n, T const& x)
        : _list(n, x), _size(n)
    { }

    template <typename Iter>
    counted_list(Iter f, Iter l)
        : _list(f, l), _size(std::distance(f, l))
    { }

    iterator begin()                { return _list.begin(); }
    iterator end()                  { return _list.end(); }
    const_iterator begin() const    { return _list.begin(); }
    const_iterator end() const      { return _list.end(); }

    reverse_iterator rbegin()               { return _list.rbegin(); }
    reverse_iterator rend()                 { return _list.rend(); }
    const_reverse_iterator rbegin() const   { return _list.rbegin(); }
    const_reverse_iterator rend() const     { return _list.rend(); }

    size_type size() const          { return _size; }
    size_type max_size() const      { return _list.max_size(); }

    bool empty() const              { return _list.empty(); }

    reference front()               { return _list.front(); }
    const_reference front() const   { return _list.front(); }

    reference back()                { return _list.back(); }
    const_reference back() const    { return _list.back(); }

    void push_front(T const& x)     { _list.push_front(x); ++_size; }
    void pop_front()                { _list.pop_front(); --_size; }

    void push_back(T const& x)      { _list.push_back(x); ++_size; }
    void pop_back()                 { _list.pop_back(); --_size; }

    iterator insert(iterator i, T const& x)
    {
        iterator ret = _list.insert(i, x);
        ++_size;
        return ret;
    }

    template <typename Iter>
    iterator insert(iterator pos, Iter f, Iter l)
    {
        _list.insert(pos, f, l);
        _size += std::distance(f, l);
    }

    iterator erase(iterator pos)
    {
        iterator ret = _list.erase(pos);
        --_size;
        return ret;
    }

    iterator erase(iterator f, iterator l)
    {
        _size -= std::distance(f, l);
        return _list.erase(f, l);
    }

    void resize(size_type n, T const& x = T())
    { _list.resize(n, x); _size = n; }

    void clear()
    { _list.clear(); _size = 0; }

    counted_list& swap(counted_list&& x)
    { _list.swap(x._list); return* this; }

    counted_list& operator=(counted_list const& x)
    { return swap(counted_list(x)); }

    counted_list& operator=(counted_list&& x)
    { return swap(x); }

    bool operator==(counted_list const& x) const
    { return _list == x._list; }

    bool operator<(counted_list const& x) const
    { return _list < x._list; }

private:
    base_type   _list;
    size_type   _size;
};

// Specialize container traits
template <typename T, typename Alloc, typename List>
struct container_traits<counted_list<T, Alloc, List>>
{
    typedef list_tag category;
    typedef stable_iterator_tag iterator_stability;
};

// Specialize descriptor traits
template <typename T, typename Alloc, typename List, typename Kind>
struct descriptor_traits<counted_list<T, Alloc, List>, Kind>
{
    typedef node_descriptor<
        blob<sizeof(typename std::list<T, Alloc>::iterator)>, Kind
    > descriptor_type;
    typedef stable_mutators_tag descriptor_stability;

};

} /* namespace boost */

#endif
