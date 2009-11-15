
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/fiber/scheduler.hpp>

#include <boost/fiber/detail/move.hpp>
#include <boost/fiber/detail/scheduler_impl.hpp>
#include <boost/fiber/exceptions.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost {
namespace fibers {

scheduler::tss_impl_t scheduler::impl_;

bool
scheduler::runs_as_fiber()
{ return impl_.get() != 0; }

fiber::id
scheduler::active_fiber()
{
	detail::scheduler_impl * impl( impl_.get() );
	if (  ! impl) throw fiber_error("not a fiber");
	return impl->active_fiber();
}

void
scheduler::yield_active_fiber()
{
	detail::scheduler_impl * impl( impl_.get() );
	if (  ! impl) throw fiber_error("not a fiber");
	impl->yield_active_fiber();
}

void
scheduler::cancel_active_fiber()
{
	detail::scheduler_impl * impl( impl_.get() );
	if (  ! impl) throw fiber_error("not a fiber");
	impl->cancel_active_fiber();
}

void
scheduler::suspend_active_fiber()
{
	detail::scheduler_impl * impl( impl_.get() );
	if (  ! impl) throw fiber_error("not a fiber");
	impl->suspend_active_fiber();
}

void
scheduler::cancel_fiber( fiber::id const& id)
{
	detail::scheduler_impl * impl( impl_.get() );
	if (  ! impl) throw fiber_error("not a fiber");
	impl->cancel_fiber( id);
}

void
scheduler::suspend_fiber( fiber::id const& id)
{
	detail::scheduler_impl * impl( impl_.get() );
	if (  ! impl) throw fiber_error("not a fiber");
	impl->suspend_fiber( id);
}

void
scheduler::resume_fiber( fiber::id const& id)
{
	detail::scheduler_impl * impl( impl_.get() );
	if (  ! impl) throw fiber_error("not a fiber");
	impl->resume_fiber( id);
}

int
scheduler::priority( fiber::id const& id)
{
	detail::scheduler_impl * impl( impl_.get() );
	if (  ! impl) throw fiber_error("not a fiber");
	return impl->priority( id);
}

void
scheduler::priority( fiber::id const& id, int prio)
{
	detail::scheduler_impl * impl( impl_.get() );
	if (  ! impl) throw fiber_error("not a fiber");
	impl->priority( id, prio);
	re_schedule( id);
}

void
scheduler::re_schedule( fiber::id const& id)
{
	detail::scheduler_impl * impl( impl_.get() );
	impl->re_schedule( id);
}

void
scheduler::join( fiber::id const& id)
{
	detail::scheduler_impl * impl( impl_.get() );
	impl->join( id);
}

detail::scheduler_impl *
scheduler::access_()
{
	if ( ! impl_.get() )
	{
		fiber::convert_thread_to_fiber();
		impl_.reset( new detail::scheduler_impl() );
	}
	return impl_.get();
}

scheduler::~scheduler()
{ impl_.reset(); }

bool
scheduler::run()
{ return access_()->run(); }

bool
scheduler::empty()
{ return access_()->empty(); }

std::size_t
scheduler::size()
{ return access_()->size(); }

void
scheduler::submit_fiber( fiber f)
{ access_()->add_fiber( f); }

}}

#include <boost/config/abi_suffix.hpp>
