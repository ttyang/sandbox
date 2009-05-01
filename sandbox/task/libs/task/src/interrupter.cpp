
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/task/detail/interrupter.hpp"

#include <boost/assert.hpp>

namespace boost { namespace task
{
namespace detail
{
void
interrupter::impl::interrupt_()
{
	if ( ! interruption_requested_)
	{
		interruption_requested_ = true;
		if ( thrd_) thrd_->interrupt();
	}
}

interrupter::impl::impl()
:
interruption_requested_( false),
done_( false),
cond_(),
mtx_(),
thrd_()
{}

interrupter::impl::~impl()
{ reset(); }

void
interrupter::impl::set( shared_ptr< thread > const& thrd)
{
	unique_lock< mutex > lk( mtx_);
	thrd_ = thrd;
	BOOST_ASSERT( thrd_);
	if ( interruption_requested_)
		if ( thrd_) thrd_->interrupt();
}

void
interrupter::impl::reset()
{
	unique_lock< mutex > lk( mtx_);
// 	BOOST_ASSERT( thrd_);
// 	try
// 	{ thrd_.reset(); }
// 	catch (...)
// 	{ printf("exception\n"); }
	try
	{ this_thread::interruption_point(); }
	catch ( thread_interrupted const&)
	{}
	BOOST_ASSERT( ! this_thread::interruption_requested() );
	done_ = true;
	cond_.notify_all();
}

void
interrupter::impl::interrupt()
{
	unique_lock< mutex > lk( mtx_);
	interrupt_();
}

void
interrupter::impl::interrupt_and_wait()
{
	unique_lock< mutex > lk( mtx_);
	interrupt_();
	while ( ! done_)
		cond_.wait( lk);
}

void
interrupter::impl::interrupt_and_wait( system_time const& abs_time)
{
	unique_lock< mutex > lk( mtx_);
	interrupt_();
	while ( ! done_)
		cond_.timed_wait( lk, abs_time);
}

bool
interrupter::impl::interruption_requested()
{
	unique_lock< mutex > lk( mtx_);
	return interruption_requested_;
}

interrupter::interrupter()
: impl_( new impl() )
{}

void
interrupter::set( shared_ptr< thread > const& thrd)
{ impl_->set( thrd); }

void
interrupter::reset()
{ impl_->reset(); }

void
interrupter::interrupt()
{ impl_->interrupt(); }

void
interrupter::interrupt_and_wait()
{ impl_->interrupt_and_wait(); }

void
interrupter::interrupt_and_wait( system_time const& abs_time)
{ impl_->interrupt_and_wait( abs_time); }

bool
interrupter::interruption_requested()
{ return impl_->interruption_requested(); }
}
} }

