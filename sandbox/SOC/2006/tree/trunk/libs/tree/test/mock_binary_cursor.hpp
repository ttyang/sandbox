//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_TEST_MOCK_BINARY_CURSOR_HPP
#define LIBS_TREE_TEST_MOCK_BINARY_CURSOR_HPP

template <class Iter>
class mock_binary_cursor;

template <class Iter>
class mock_binary_cursor
: public boost::tree::cursor_facade<
        mock_binary_cursor<Iter>
      , mock_binary_cursor<Iter>
      , boost::bidirectional_traversal_tag
      , boost::tree::descending_vertical_traversal_tag
    >
{
private:
    Iter& m_iter;
public:
    typedef mock_binary_cursor<Iter> cursor;
    typedef mock_binary_cursor<Iter/* const*/> const_cursor;

    typedef typename mock_binary_cursor<Iter>::cursor_facade_::size_type size_type;
    
    mock_binary_cursor(Iter& iter)
    : m_iter(iter)
    {
    }

    void operator=(typename Iter::value_type const& val)
    {
        BOOST_CHECK_EQUAL(val, *m_iter++);
    }
    
private:
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;
    
    typename mock_binary_cursor<Iter>::cursor_facade_::reference
    dereference() const
    {
        return const_cast< mock_binary_cursor<Iter>& >(*this);
    }

    bool equal(mock_binary_cursor<Iter> const& other) const
    {
        return false;
    }

    void increment()
    {
    }
    
    void decrement()
    {
    }  

    void left()
    {
    }

    void right()
    {
    }
    
    bool const empty_() const
    {
        return true;
    }

    size_type const idx() const
    {
        return 0;
    }
};

#endif // LIBS_TREE_TEST_MOCK_BINARY_CURSOR_HPP
