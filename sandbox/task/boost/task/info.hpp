
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_INFO_H
#define BOOST_TASK_INFO_H

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/task/detail/info.hpp>

namespace boost { namespace task
{
template< typename Pool >
struct has_priority : public mpl::bool_<
						is_same<
							detail::has_priority,
							typename Pool::scheduler_type::priority_tag_type
						>::value
					>
{};

template< typename Pool >
struct priority_type
{
	typedef typename Pool::scheduler_type::attribute_type	type;
};
} }

#endif // BOOST_TASK_INFO_H

