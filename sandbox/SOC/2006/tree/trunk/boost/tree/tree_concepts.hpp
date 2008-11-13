//  Copyright (c) 2006-2008, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file tree_concepts.hpp
 * Tree concepts
 */
 
#ifndef BOOST_TREE_TREE_CONCEPTS_HPP
#define BOOST_TREE_TREE_CONCEPTS_HPP

#include <boost/concept_check.hpp>

namespace boost {
namespace tree {

template <class X>
struct Tree
{
public:
    typedef typename Tree::cursor cursor;
    typedef typename Tree::const_cursor const_cursor;

    BOOST_CONCEPT_USAGE(Tree)
    {
        t.root();
    }
    
private:
    X t;
    
};


} // namespace tree
} // namespace boost

#endif // BOOST_TREE_TREE_CONCEPTS_HPP
