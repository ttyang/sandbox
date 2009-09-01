
#ifndef BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source: /home/evansl/prog_dev/boost-svn/ro/boost-vrtmp/boost/mpl/set/aux_/RCS/begin_end_impl.hpp,v $
// $Date: 2009/08/27 16:11:32 $
// $Revision: 1.3 $
//GhangeLog:
//  2007-01-28.1246.CST Larry Evans
//    WHAT:
//      copied from corresponding boost-cvs file and renamed set0<> to set0
//    WHY:
//      In variadic template version of library, there's no set0.
//

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/set/aux_/iterator.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : s_iter_get<Set,typename Set::item_>
    {
    };
};

template<>
struct end_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef s_iter< Set,set0 > type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED
