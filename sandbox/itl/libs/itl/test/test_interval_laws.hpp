/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------+
Function templates to call functions in object oriented or namespace glabal 
versions.
+-----------------------------------------------------------------------------*/
#ifndef BOOST_LIBS_ITL_TEST_INTERVAL_LAWS_HPP_JOFA_101011
#define BOOST_LIBS_ITL_TEST_INTERVAL_LAWS_HPP_JOFA_101011

#include <boost/itl/detail/notate.hpp>
#include <boost/itl/detail/design_config.hpp>
#include <boost/itl/type_traits/interval_type_default.hpp>
#include <boost/itl/interval.hpp>
#include <boost/itl/type_traits/is_interval.hpp>
#include <boost/itl/concept/interval.hpp>

namespace boost{ namespace itl
{

template<class Type>
typename enable_if<is_interval<Type>, void>::type
check_border_containedness(const Type& itv)
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    domain_type lo = itl::lower(itv);
    domain_type up = itl::upper(itv);

    //LAW: The empty set is contained in every set 
    BOOST_CHECK_EQUAL(itl::contains(itv, itl::identity_element<Type>::value()), true);
    //LAW: Reflexivity: Every interval contains itself
    BOOST_CHECK_EQUAL(itl::contains(itv, itv), true);

    if(itl::bounds(itv) == interval_bounds::closed())
    {
        BOOST_CHECK_EQUAL(itl::contains(itv, lo), true);
        BOOST_CHECK_EQUAL(itl::contains(itv, up), true);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::    closed(lo,up)), true);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::right_open(lo,up)), true);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>:: left_open(lo,up)), true);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::      open(lo,up)), true);
    }
    else if(itl::bounds(itv) == interval_bounds::right_open())
    {
        BOOST_CHECK_EQUAL(itl::contains(itv, lo), true);
        BOOST_CHECK_EQUAL(itl::contains(itv, up), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::    closed(lo,up)), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::right_open(lo,up)), true);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>:: left_open(lo,up)), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::      open(lo,up)), true);
    }
    else if(itl::bounds(itv) == interval_bounds::left_open())
    {
        BOOST_CHECK_EQUAL(itl::contains(itv, lo), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, up), true);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::    closed(lo,up)), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::right_open(lo,up)), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>:: left_open(lo,up)), true);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::      open(lo,up)), true);
    }
    else if(itl::bounds(itv) == interval_bounds::open())
    {
        BOOST_CHECK_EQUAL(itl::contains(itv, lo), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, up), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::    closed(lo,up)), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::right_open(lo,up)), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>:: left_open(lo,up)), false);
        BOOST_CHECK_EQUAL(itl::contains(itv, itl::interval<domain_type>::      open(lo,up)), true);
    }
    else
    {
        bool interval_borders_are_open_v_left_open_v_right_open_v_closed = true;
        BOOST_CHECK_EQUAL(interval_borders_are_open_v_left_open_v_right_open_v_closed, false);
    }
}

}} // namespace boost itl

#endif // BOOST_ITL_TEST_INTERVAL_LAWS_HPP_JOFA_100908

