#include <boost/fiber/strategy.hpp>

#include <utility>

#include <boost/assert.hpp>

#include <boost/fiber/detail/info.hpp>
#include <boost/fiber/detail/info_base.hpp>
#include <boost/fiber/detail/state_flags.hpp>
#include <boost/fiber/exceptions.hpp>

namespace boost {
namespace fibers {

strategy::fiber_t strategy::active_fiber;

bool
strategy::runs_as_fiber_()
{ return active_fiber.get() != 0; }

fiber::id
strategy::get_id_()
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	return active->get_id();
}

void
strategy::interruption_point_()
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	if ( detail::INTERRUPTION_ENABLED == active->info_()->interrupt)
		throw fiber_interrupted();
}

bool
strategy::interruption_requested_()
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	return active->interruption_requested();
}

detail::interrupt_t &
strategy::interrupt_flags_()
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	return active->info_()->interrupt;
}

bool
strategy::interruption_enabled_()
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	return ( active->info_()->interrupt & detail::INTERRUPTION_ENABLED) != 0;
}

int
strategy::priority_()
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	return active->priority();
}

void
strategy::priority_( int prio)
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	active->priority( prio);
}

void
strategy::at_fiber_exit_( callable_t ca)
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	active->info_()->at_exit.push( ca);
}

void
strategy::yield_()
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	if ( ! active->info_()->st) throw scheduler_error("no valid scheduler");
	active->info_()->st->yield();
}

void
strategy::cancel_()
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	if ( ! active->info_()->st) throw scheduler_error("no valid scheduler");
	active->info_()->st->cancel( active_fiber->get_id() );
}

void
strategy::register_object_( object::id const& oid)
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	if ( ! active->info_()->st) throw scheduler_error("no valid scheduler");
	active->info_()->st->register_object( oid);
}

void
strategy::unregister_object_( object::id const& oid)
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	if ( ! active->info_()->st) throw scheduler_error("no valid scheduler");
	active->info_()->st->unregister_object( oid);
}

void
strategy::wait_for_object_( object::id const& oid)
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	if ( ! active->info_()->st) throw scheduler_error("no valid scheduler");
	active->info_()->st->wait_for_object( oid);
}

void
strategy::object_notify_one_( object::id const& oid)
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	if ( ! active->info_()->st) throw scheduler_error("no valid scheduler");
	active->info_()->st->object_notify_one( oid);
}

void
strategy::object_notify_all_( object::id const& oid)
{
	fiber * active( active_fiber.get() );
	if ( ! active) throw fiber_error("not a fiber");
	if ( ! active->info_()->st) throw scheduler_error("no valid scheduler");
	active->info_()->st->object_notify_all( oid);
}

strategy::strategy() :
	master_fiber()
{
	fiber::convert_thread_to_fiber();
	master_fiber = fiber( 
			detail::info_base::ptr_t(
				new detail::info_default() ) );
	attach( master_fiber);
}

strategy::~strategy()
{ fiber::convert_fiber_to_thread(); }

void
strategy::attach( fiber & f)
{ f.info_()->st = this; }

void
strategy::detach( fiber & f)
{ f.info_()->st = 0; }

void
strategy::switch_between( fiber & from, fiber & to)
{ from.switch_to_( to); }

void
strategy::enable_interruption( fiber & f)
{
	// remove disabled flag
	f.info_()->interrupt &= ~detail::INTERRUPTION_DISABLED;

	// set enabled flag
	f.info_()->interrupt |= detail::INTERRUPTION_ENABLED;
}

bool
strategy::interruption_enabled( fiber const& f)
{ return detail::INTERRUPTION_ENABLED == f.info_()->interrupt; }

bool
strategy::is_master( fiber const& f)
{ return f == master_fiber; }

bool
strategy::in_state_not_started( fiber const& f)
{ return detail::STATE_NOT_STARTED == f.info_()->state; }

bool
strategy::in_state_ready( fiber const& f)
{ return detail::STATE_READY == f.info_()->state; }

bool
strategy::in_state_running( fiber const& f)
{ return detail::STATE_RUNNING == f.info_()->state; }

bool
strategy::in_state_wait_for_fiber( fiber const& f)
{ return detail::STATE_WAIT_FOR_FIBER == f.info_()->state; }

bool
strategy::in_state_wait_for_object( fiber const& f)
{ return detail::STATE_WAIT_FOR_OBJECT == f.info_()->state; }

bool
strategy::in_state_terminated( fiber const& f)
{ return detail::STATE_TERMINATED == f.info_()->state; }

void
strategy::set_state_ready( fiber & f)
{ f.info_()->state = detail::STATE_READY; }

void
strategy::set_state_running( fiber & f)
{ f.info_()->state = detail::STATE_RUNNING; }

void
strategy::set_state_wait_for_fiber( fiber & f)
{ f.info_()->state = detail::STATE_WAIT_FOR_FIBER; }

void
strategy::set_state_wait_for_object( fiber & f)
{ f.info_()->state = detail::STATE_WAIT_FOR_OBJECT; }

void
strategy::set_state_terminated( fiber & f)
{ f.info_()->state = detail::STATE_TERMINATED; }

}}
