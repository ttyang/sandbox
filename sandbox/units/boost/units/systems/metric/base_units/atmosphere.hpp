// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2007-2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNIT_SYSTEMS_METRIC_ATMOSPHERE_HPP_INCLUDED
#define BOOST_UNIT_SYSTEMS_METRIC_ATMOSPHERE_HPP_INCLUDED

#include <boost/units/systems/detail/non_si_unit.hpp>
#include <boost/units/systems/si/pressure.hpp>

BOOST_UNITS_DEFINE_BASE_UNIT_WITH_CONVERSIONS(metric, atmosphere, "atmosphere", "atm", 1.01325e5, SI::pressure, 33);

#endif // BOOST_UNIT_SYSTEMS_METRIC_ATMOSPHERE_HPP_INCLUDED
