
#ifndef BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date: 2008-10-10 04:10:26 -0500 (Fri, 10 Oct 2008) $
// $Revision: 49239 $

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/list_fwd.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Node >
struct l_iter
{
    typedef aux::l_iter_tag tag;
    typedef forward_iterator_tag category;
};

template< typename Node >
struct deref< l_iter<Node> >
{
    typedef typename Node::item type;
};

template< typename Node >
struct next< l_iter<Node> >
{
    typedef l_iter< typename Node::next > type;
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< typename Node >
struct l_iter
{
    typedef aux::l_iter_tag tag;
    typedef forward_iterator_tag category;
    typedef typename Node::item type;
    typedef l_iter< typename mpl::next<Node>::type > next;
};

#endif


template<> struct l_iter<list<> >
{
    typedef aux::l_iter_tag tag;
    typedef forward_iterator_tag category;
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef na type;
    typedef na next;
#endif
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, l_iter)

}}

#endif // BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED
