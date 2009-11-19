
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/fiber/fiber.hpp>

extern "C" {

#include <ucontext.h>

}

#include <cerrno>

#include <boost/system/system_error.hpp>

#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/utility.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost {
namespace fibers {

void trampoline( detail::fiber_info_base * self)
{
	BOOST_ASSERT( self);
	try
	{ self->run(); }
	catch ( fiber_interrupted const&) {}
	catch (...) {}
	while ( ! self->at_exit.empty() )
	{
		detail::fiber_info_base::callable_t ca;
		self->at_exit.top().swap( ca);
		self->at_exit.pop();
		ca();
	}
 	this_fiber::cancel();
}

void
fiber::init_()
{
	typedef void fn_type( detail::fiber_info_base *);
	typedef void ( * st_fn)();
	fn_type * fn_ptr( trampoline);

	if ( ! info_base_) throw fiber_moved();

	::makecontext(
		& info_base_->uctx,
		( st_fn)( fn_ptr),
		1,
		info_base_.get() );
}

void
fiber::switch_to_( fiber & to)
{
	if ( ! info_base_) throw fiber_moved();

	if ( ::swapcontext( & info_base_->uctx, & to.info_base_->uctx) != 0)
		throw system::system_error(
			system::error_code(
				errno,
				system::system_category) );
}

void
fiber::convert_thread_to_fiber()
{} 

void
fiber::convert_fiber_to_thread()
{}

}}

#include <boost/config/abi_suffix.hpp>
