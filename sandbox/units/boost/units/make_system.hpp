// mcs::units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2007 Matthias Christian Schabel
// Copyright (C) 2007 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_MAKE_SYSTEM_HPP
#define BOOST_UNITS_MAKE_SYSTEM_HPP

#include <boost/mpl/list/list10.hpp>

#include <boost/units/config.hpp>
#include <boost/units/dimensionless_type.hpp>
#include <boost/units/homogeneous_system.hpp>
#include <boost/units/detail/dimension_list.hpp>
#include <boost/units/detail/sort.hpp>

namespace boost {

namespace units {

#ifdef BOOST_UNITS_DOXYGEN

namespace detail {

struct unspecified {};

}

/// Metafunction returning a homogeneous system that can
/// represent any combination of the base units.  There must
/// be no way to represent any of the base units in terms
/// of the others.  make_system<foot_base_unit, meter_base_unit>::type
/// is not allowed, for example.
template<class BaseUnit0, class BaseUnit1, class BaseUnit2, ..., class BaseUnitN>
struct make_system
{
    typedef homogeneous_system<detail::unspecified> type;
};

#else

struct na {};

template<
    class U0 = na,
    class U1 = na,
    class U2 = na,
    class U3 = na,
    class U4 = na,
    class U5 = na,
    class U6 = na,
    class U7 = na,
    class U8 = na,
    class U9 = na
>
struct make_system;

template<>
struct make_system<>
{
    typedef homogeneous_system<dimensionless_type> type;
};

// Codewarrior 9.2 doesn't like using the defaults.  Need
// to specify na explicitly.
template<class T0>
struct make_system<T0, na, na, na, na, na, na, na, na, na>
{
    typedef homogeneous_system<dimension_list<T0, dimensionless_type> > type;
};

template<class T0, class T1>
struct make_system<T0, T1, na, na, na, na, na, na, na, na>
{
    typedef homogeneous_system<typename detail::bubble_sort<mpl::list2<T0, T1> >::type> type;
};

template<class T0, class T1, class T2>
struct make_system<T0, T1, T2, na, na, na, na, na, na, na>
{
    typedef homogeneous_system<typename detail::bubble_sort<mpl::list3<T0, T1, T2> >::type> type;
};

template<class T0, class T1, class T2, class T3>
struct make_system<T0, T1, T2, T3, na, na, na, na, na, na>
{
    typedef homogeneous_system<typename detail::bubble_sort<mpl::list4<T0, T1, T2, T3> >::type> type;
};

template<class T0, class T1, class T2, class T3, class T4>
struct make_system<T0, T1, T2, T3, T4, na, na, na, na, na>
{
    typedef homogeneous_system<typename detail::bubble_sort<mpl::list5<T0, T1, T2, T3, T4> >::type> type;
};

template<class T0, class T1, class T2, class T3, class T4, class T5>
struct make_system<T0, T1, T2, T3, T4, T5, na, na, na, na>
{
    typedef homogeneous_system<typename detail::bubble_sort<mpl::list6<T0, T1, T2, T3, T4, T5> >::type> type;
};

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6>
struct make_system<T0, T1, T2, T3, T4, T5, T6, na, na, na>
{
    typedef homogeneous_system<typename detail::bubble_sort<mpl::list7<T0, T1, T2, T3, T4, T5, T6> >::type> type;
};

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
struct make_system<T0, T1, T2, T3, T4, T5, T6, T7, na, na>
{
    typedef homogeneous_system<typename detail::bubble_sort<mpl::list8<T0, T1, T2, T3, T4, T5, T6, T7> >::type> type;
};

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
struct make_system<T0, T1, T2, T3, T4, T5, T6, T7, T8, na>
{
    typedef homogeneous_system<typename detail::bubble_sort<mpl::list9<T0, T1, T2, T3, T4, T5, T6, T7, T8> >::type> type;
};

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
struct make_system
{
    typedef homogeneous_system<typename detail::bubble_sort<mpl::list10<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >::type> type;
};

#endif

} // namespace units

} // namespace boost

#endif
