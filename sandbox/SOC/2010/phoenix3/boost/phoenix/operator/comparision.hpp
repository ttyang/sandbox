/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_OPERATOR_COMPARISION_HPP
#define PHOENIX_OPERATOR_COMPARISION_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>

namespace boost { namespace phoenix
{
	
	PHOENIX_BINARY_OPERATORS(
		(equal_to)
		(not_equal_to)
		(less_equal)
		(greater_equal)
		(less)
		(greater)
	)
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif
