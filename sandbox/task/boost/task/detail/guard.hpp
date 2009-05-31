
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_DETAIL_GUARD_H
#define BOOST_TASK_DETAIL_GUARD_H

#include <boost/cstdint.hpp>
#include <boost/utility.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost { namespace task
{
namespace detail
{
class guard : private noncopyable
{
private:
	volatile uint32_t	&	active_worker_;

public:
	guard( volatile uint32_t & active_worker);

	~guard();
};
} } }

#include <boost/config/abi_suffix.hpp>

#endif // BOOST_TASK_DETAIL_GUARD_H

