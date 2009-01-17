//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_HPP
#define LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_HPP

#include <boost/tree/binary_tree.hpp>
#include <boost/tree/algorithm.hpp>

#include <vector>

#include <boost/mpl/list.hpp>

#include "helpers.hpp"

typedef boost::mpl::list<boost::tree::preorder
                        ,boost::tree::inorder
                        ,boost::tree::postorder> orders;

template <class T = int>
struct test_binary_tree_fixture {
    test_binary_tree_fixture()
    {
        create_test_dataset1_tree(bt);
        create_test_dataset1_tree(bt2);
        
        typename boost::tree::binary_tree<T>::cursor d = bt2.root();

        // Just to make sure we won't be getting any false positives when 
        // copying test_tree1 to test_tree2, we'll change one of test_tree2's
        // values.
        d = d.begin().end().begin().begin();
        *d = T(29);
    }
    
    // Test data from http://en.wikipedia.org/wiki/Image:Binary_search_tree.svg
    // (With two additional nodes: 11 inserted left of 13; 12 right of 11)
    // and in combination with http://en.wikipedia.org/wiki/Tree_traversal#Examples
    // (as tree shapes are equal [apart from the extra nodes])
    static void create_test_dataset1_tree(boost::tree::binary_tree<T>& ret)
    {
        // For augmented trees. (Why is this necessary? Nothing here is explicit!)
        typedef typename boost::tree::binary_tree<T>::value_type value_type; 
        
        typename boost::tree::binary_tree<T>::cursor cur = ret.insert(ret.root(), value_type(8));
        cur = ret.insert(cur.to_begin(), value_type(3));
        ret.insert(cur.to_begin(), value_type(1));
        cur = ret.insert(++cur, value_type(6));
        ret.insert(cur.to_begin(), value_type(4));
        ret.insert(++cur, value_type(7));
        cur = ret.insert(ret.root().end(), value_type(10));
        cur = ret.insert(ret.root().end().end(), value_type(14));
        cur = ret.insert(cur.to_begin(), value_type(13));
        cur = ret.insert(cur.to_begin(), value_type(11));
        cur = ret.insert(++cur.to_begin(), value_type(12));
    }
    
    template <class Cursor>
    static void validate_test_dataset1_tree(Cursor cur)
    {
        BOOST_CHECK_EQUAL(*cur.begin(), 8);
        BOOST_CHECK_EQUAL(*cur.begin().begin(), 3);
        BOOST_CHECK_EQUAL(*cur.begin().begin().begin(), 1);
        BOOST_CHECK(cur.begin().begin().end().empty());
        BOOST_CHECK(cur.begin().begin().begin().empty()); //Leaf
        
        BOOST_CHECK_EQUAL(*cur.begin().end().begin(), 6);
        BOOST_CHECK_EQUAL(*cur.begin().end().begin().begin(), 4);
        BOOST_CHECK(cur.begin().end().begin().begin().empty()); //Leaf

        BOOST_CHECK_EQUAL(*cur.begin().end().end().begin(), 7);
        BOOST_CHECK(cur.begin().end().end().begin().empty()); //Leaf

        BOOST_CHECK_EQUAL(*cur.end().begin(), 10);
        BOOST_CHECK(cur.end().begin().empty());
        BOOST_CHECK_EQUAL(*cur.end().end().begin(), 14);
        BOOST_CHECK(cur.end().end().end().empty());
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin(), 13);
        BOOST_CHECK(cur.end().end().begin().end().empty());
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().begin(), 11);
        BOOST_CHECK(cur.end().end().begin().begin().begin().empty()); 
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().end().begin(), 12);
        BOOST_CHECK(cur.end().end().begin().begin().end().begin().empty()); //Leaf
    }

    static void validate_test_dataset1_minus_1_tree(typename boost::tree::binary_tree<T>::const_cursor cur)
    {
        BOOST_CHECK_EQUAL(*cur.begin(), 7);
        BOOST_CHECK_EQUAL(*cur.begin().begin(), 2);    
        BOOST_CHECK_EQUAL(*cur.begin().begin().begin(), 0);  //Leaf
        BOOST_CHECK_EQUAL(*cur.begin().end().begin(), 5);        
        BOOST_CHECK_EQUAL(*cur.begin().end().begin().begin(), 3); //Leaf
        BOOST_CHECK_EQUAL(*cur.begin().end().end().begin(), 6); //Leaf
    
        BOOST_CHECK_EQUAL(*cur.end().begin(), 9);
        BOOST_CHECK_EQUAL(*cur.end().end().begin(), 13);
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin(), 12);
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().begin(), 10); 
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().end().begin(), 11); //Leaf
    }
    
    boost::tree::binary_tree<T> bt, bt2;
};

template <class T = int>
struct test_binary_tree_with_list_fixture
: public test_binary_tree_fixture<T>
, public test_with_list_fixture {
    test_binary_tree_with_list_fixture()
    : test_binary_tree_fixture<T>()
    , test_with_list_fixture() {}
};

template <class Tree>
void validate_corresponding_forest(Tree const& t)
{
    typename Tree::const_cursor c = t.root().begin();
    BOOST_CHECK_EQUAL(*c, 8);
    BOOST_CHECK_EQUAL(*c.to_begin(), 3);
    BOOST_CHECK_EQUAL(*c.to_begin(), 1);
    BOOST_CHECK(c.empty());
    BOOST_CHECK(++c == t.root().begin().begin().end());
    --c;
    c.to_parent();
    BOOST_CHECK_EQUAL(*++c, 6);
    BOOST_CHECK_EQUAL(*c.to_begin(), 4);
    c.to_parent();
    BOOST_CHECK_EQUAL(*++c, 7);
    BOOST_CHECK(++c == t.root().begin().end());
    
    c = t.root().begin();
    BOOST_CHECK_EQUAL(*++c, 10);
    BOOST_CHECK_EQUAL(*++c, 14);
    BOOST_CHECK(++c == t.root().end());
    --c;
    BOOST_CHECK_EQUAL(*c.to_begin(), 13);
    BOOST_CHECK_EQUAL(*c.to_begin(), 11);
    BOOST_CHECK_EQUAL(*++c, 12);
}

template <class Iter>
class mock_cursor;

template <class Iter>
class mock_cursor
: public boost::tree::cursor_facade<
        mock_cursor<Iter>
      , mock_cursor<Iter>
      , boost::bidirectional_traversal_tag
      , boost::tree::descending_vertical_traversal_tag
    >
{
private:
    Iter& m_iter;
public:
    typedef mock_cursor<Iter> cursor;
    typedef mock_cursor<Iter/* const*/> const_cursor;

    typedef typename mock_cursor<Iter>::cursor_facade_::size_type size_type;
    
    mock_cursor(Iter& iter)
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
    
    typename mock_cursor<Iter>::cursor_facade_::reference
    dereference() const
    {
        return const_cast< mock_cursor<Iter>& >(*this);
    }

    bool equal(mock_cursor<Iter> const& other) const
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

template <class Iterator>
void test_traversal(boost::tree::preorder, Iterator a, Iterator b) 
{
    BOOST_CHECK_EQUAL(*a++, 8);
    BOOST_CHECK_EQUAL(*a++, 3);
    BOOST_CHECK_EQUAL(*a++, 1);
    BOOST_CHECK_EQUAL(*a++, 6);
    BOOST_CHECK_EQUAL(*a++, 4);
    BOOST_CHECK_EQUAL(*a++, 7);
    BOOST_CHECK_EQUAL(*a++, 10);
    BOOST_CHECK_EQUAL(*a++, 14);
    BOOST_CHECK_EQUAL(*a++, 13);
    BOOST_CHECK_EQUAL(*a++, 11);
    BOOST_CHECK_EQUAL(*a++, 12);
    BOOST_CHECK(a == b);
}

template <class Iterator>
void test_reverse_traversal(boost::tree::preorder, Iterator a, Iterator b)
{     
    BOOST_CHECK_EQUAL(*--a, 12);
    BOOST_CHECK_EQUAL(*--a, 11);
    BOOST_CHECK_EQUAL(*--a, 13);
    BOOST_CHECK_EQUAL(*--a, 14);
    BOOST_CHECK_EQUAL(*--a, 10);
    BOOST_CHECK_EQUAL(*--a, 7);
    BOOST_CHECK_EQUAL(*--a, 4);
    BOOST_CHECK_EQUAL(*--a, 6);
    BOOST_CHECK_EQUAL(*--a, 1);
    BOOST_CHECK_EQUAL(*--a, 3);
    BOOST_CHECK_EQUAL(*--a, 8);
    BOOST_CHECK(a == b);
}

template <class Iterator>
void test_subtree_traversal(boost::tree::preorder, Iterator a, Iterator b
                          , std::vector<int>::difference_type x = 0) 
{
    std::vector<int> preorder(11);
    preorder[0] = 8;
    preorder[1] = 3;
    preorder[2] = 1;
    preorder[3] = 6;
    preorder[4] = 4;
    preorder[5] = 7;
    preorder[6] = 10;
    preorder[7] = 14;
    preorder[8] = 13;
    preorder[9] = 11;
    preorder[10] = 12;
    
    BOOST_CHECK(std::equal(a, b, preorder.begin() + x));
}

//template <class Iterator>
//void test_subtree_traversal(boost::tree::preorder, Iterator a, Iterator b) 
//{
//    BOOST_CHECK_EQUAL(*a++, 3);
//    BOOST_CHECK_EQUAL(*a++, 1);
//    BOOST_CHECK_EQUAL(*a++, 6);
//    BOOST_CHECK_EQUAL(*a++, 4);
//    BOOST_CHECK_EQUAL(*a++, 7);
//    BOOST_CHECK(a == b);
//}

template <class Iterator>
void test_traversal(boost::tree::inorder, Iterator a, Iterator b)
{        
    BOOST_CHECK_EQUAL(*a++, 1);
    BOOST_CHECK_EQUAL(*a++, 3);
    BOOST_CHECK_EQUAL(*a++, 4);
    BOOST_CHECK_EQUAL(*a++, 6);
    BOOST_CHECK_EQUAL(*a++, 7);
    BOOST_CHECK_EQUAL(*a++, 8);
    BOOST_CHECK_EQUAL(*a++, 10);
    BOOST_CHECK_EQUAL(*a++, 11);
    BOOST_CHECK_EQUAL(*a++, 12);
    BOOST_CHECK_EQUAL(*a++, 13);
    BOOST_CHECK_EQUAL(*a++, 14);
    BOOST_CHECK(a == b);
}

template <class Iterator>
void test_reverse_traversal(boost::tree::inorder, Iterator a, Iterator b)
{
    BOOST_CHECK_EQUAL(*--a, 14);
    BOOST_CHECK_EQUAL(*--a, 13);
    BOOST_CHECK_EQUAL(*--a, 12);
    BOOST_CHECK_EQUAL(*--a, 11);
    BOOST_CHECK_EQUAL(*--a, 10);
    BOOST_CHECK_EQUAL(*--a, 8);
    BOOST_CHECK_EQUAL(*--a, 7);
    BOOST_CHECK_EQUAL(*--a, 6);
    BOOST_CHECK_EQUAL(*--a, 4);
    BOOST_CHECK_EQUAL(*--a, 3);
    BOOST_CHECK_EQUAL(*--a, 1);
    BOOST_CHECK(a == b);
}

template <class Iterator>
void test_subtree_traversal(boost::tree::inorder, Iterator a, Iterator b
                          , std::vector<int>::difference_type x = 0) 
{
    std::vector<int> inorder(11);
    inorder[0] = 1;
    inorder[1] = 3;
    inorder[2] = 4;
    inorder[3] = 6;
    inorder[4] = 7;
    inorder[5] = 8;
    inorder[6] = 10;
    inorder[7] = 11;
    inorder[8] = 12;
    inorder[9] = 13;
    inorder[10] = 14;
    
    BOOST_CHECK(std::equal(a, b, inorder.begin() + x));
}

template <class Iterator>
void test_traversal(boost::tree::postorder, Iterator a, Iterator b)
{    
    BOOST_CHECK_EQUAL(*a++, 1);
    BOOST_CHECK_EQUAL(*a++, 4);
    BOOST_CHECK_EQUAL(*a++, 7);
    BOOST_CHECK_EQUAL(*a++, 6);
    BOOST_CHECK_EQUAL(*a++, 3);
    BOOST_CHECK_EQUAL(*a++, 12);
    BOOST_CHECK_EQUAL(*a++, 11);
    BOOST_CHECK_EQUAL(*a++, 13);
    BOOST_CHECK_EQUAL(*a++, 14);
    BOOST_CHECK_EQUAL(*a++, 10);
    BOOST_CHECK_EQUAL(*a++, 8);
    BOOST_CHECK(a == b);
}

template <class Iterator>
void test_reverse_traversal(boost::tree::postorder, Iterator a, Iterator b)
{    
    BOOST_CHECK_EQUAL(*--a, 8);
    BOOST_CHECK_EQUAL(*--a, 10);
    BOOST_CHECK_EQUAL(*--a, 14);
    BOOST_CHECK_EQUAL(*--a, 13);
    BOOST_CHECK_EQUAL(*--a, 11);
    BOOST_CHECK_EQUAL(*--a, 12);
    BOOST_CHECK_EQUAL(*--a, 3);
    BOOST_CHECK_EQUAL(*--a, 6);
    BOOST_CHECK_EQUAL(*--a, 7);
    BOOST_CHECK_EQUAL(*--a, 4);
    BOOST_CHECK_EQUAL(*--a, 1);
    BOOST_CHECK(a == b);
}

template <class Iterator>
void test_subtree_traversal(boost::tree::postorder, Iterator a, Iterator b
                          , std::vector<int>::difference_type x = 0) 
{
    std::vector<int> postorder(11);
    postorder[0] = 1;
    postorder[1] = 4;
    postorder[2] = 7;
    postorder[3] = 6;
    postorder[4] = 3;
    postorder[5] = 12;
    postorder[6] = 11;
    postorder[7] = 13;
    postorder[8] = 14;
    postorder[9] = 10;
    postorder[10] = 8;
    
    BOOST_CHECK(std::equal(a, b, postorder.begin() + x));
}

template <class Iterator>
void test_traversal_from_leaf4(Iterator a, Iterator b)
{    
    BOOST_CHECK_EQUAL(*a, 4);
    BOOST_CHECK_EQUAL(*++a, 6);
    BOOST_CHECK_EQUAL(*++a, 3);
    BOOST_CHECK_EQUAL(*++a, 8);
    BOOST_CHECK(++a == b);

} // namespace ascending


#endif // LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_HPP
