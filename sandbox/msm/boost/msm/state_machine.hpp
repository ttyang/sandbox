// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_STATEMACHINE_H
#define BOOST_MSM_STATEMACHINE_H

#include <vector>
#include <queue>
#include <functional>
#include <numeric>
#include <utility>

#include <boost/mpl/fold.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/logical.hpp>

#include <boost/assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/smart_ptr.hpp>

#include <boost/bind.hpp>
#include <boost/bind/apply.hpp>
#include <boost/function.hpp>
#include <boost/msm/metafunctions.hpp>
#include <boost/msm/history_policies.hpp>
#include <boost/msm/bind_helpers.hpp>
#include <boost/msm/copy_policies.hpp>
#include <boost/msm/common_types.hpp>
#include <boost/msm/args.hpp>
#include <boost/msm/dispatch_table.hpp>
#include <boost/msm/states.hpp>

BOOST_MPL_HAS_XXX_TRAIT_DEF(accept_sig)

namespace boost { namespace msm
{

// This declares the statically-initialized dispatch_table instance.
template <class Fsm, class HistoryPolicy,class BaseState, class CopyPolicy,class Stt, class Event>
const dispatch_table<Fsm, HistoryPolicy,BaseState,CopyPolicy,Stt, Event>
dispatch_table<Fsm, HistoryPolicy,BaseState,CopyPolicy,Stt, Event>::instance;

// CRTP base class for state machines.  Pass the actual FSM class as
// the Derived parameter.
template<class Derived,class HistoryPolicy=NoHistory,
         class BaseState=default_base_state, class CopyPolicy=NoCopy>
class state_machine : public state_base<BaseState>,CopyPolicy
{
private: 
    typedef ::boost::function<
        execute_return ()>                          transition_fct;
    typedef ::boost::function<
        execute_return () >                         deferred_fct;
    typedef std::queue<deferred_fct >               deferred_events_queue_t;
    typedef std::queue<transition_fct >	            events_queue_t;
    typedef bool (*flag_handler)(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>&);
    // all state machines are friend with each other to allow embedding any of them in another fsm
    template <class ,class ,class,class > friend class state_machine;

    // helper to add, if needed, visitors to all states
    // version without visitors
    template <class StateType,class Enable=void>
    struct visitor_fct_helper 
    {
    public:
        visitor_fct_helper(){}
        void fill_visitors(int number_of_states)
        {
        }
        template <class FCT>
        void insert(int index,FCT fct)
        {
        }
        template <class VISITOR>
        void execute(int index,VISITOR vis)
        {
        }
    };
    // version with visitors
    template <class StateType>
    struct visitor_fct_helper<StateType,typename ::boost::enable_if<has_accept_sig<StateType> >::type> 
    {
    public:
        visitor_fct_helper():m_state_visitors(){}
        void fill_visitors(int number_of_states)
        {
            m_state_visitors.resize(number_of_states);
        }
        template <class FCT>
        void insert(int index,FCT fct)
        {
            m_state_visitors[index]=fct;
        }
        void execute(int index)
        {
            m_state_visitors[index]();
        }

#define MSM_VISITOR_HELPER_EXECUTE_SUB(z, n, unused) ARG ## n vis ## n
#define MSM_VISITOR_HELPER_EXECUTE(z, n, unused)                                    \
        template <BOOST_PP_ENUM_PARAMS(n, class ARG)>                               \
        void execute(int index BOOST_PP_COMMA_IF(n)                                 \
                     BOOST_PP_ENUM(n, MSM_VISITOR_HELPER_EXECUTE_SUB, ~ ) )         \
        {                                                                           \
            m_state_visitors[index](BOOST_PP_ENUM_PARAMS(n,vis));                   \
        }
        BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_ADD(BOOST_MSM_VISITOR_ARG_SIZE,1), MSM_VISITOR_HELPER_EXECUTE, ~)
#undef MSM_VISITOR_HELPER_EXECUTE
#undef MSM_VISITOR_HELPER_EXECUTE_SUB
    private:
        typedef typename StateType::accept_sig::type                  visitor_fct;
        typedef std::vector<visitor_fct>                              visitors;

        visitors                                                      m_state_visitors;
    };

 public: 
    // tags
    typedef int composite_tag;

    // default: no flag
    typedef ::boost::mpl::vector0<>     flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector<>      deferred_events;
    // in case someone needs to know
    typedef HistoryPolicy               history_policy;
    typedef CopyPolicy                  copy_policy;

    struct InitEvent { };
    // flag handling
    struct Flag_AND
    {
        typedef std::logical_and<bool> type;
    };
    struct Flag_OR
    {
     typedef std::logical_or<bool> type;
    };
    typedef ::boost::shared_ptr<BaseState>   pBaseState;

    // Member functions

    // start the state machine (calls entry of the initial state)
    void start()
    {
        // call on_entry on this SM
        (static_cast<Derived*>(this))->on_entry(InitEvent());
        typedef typename get_initial_states<typename Derived::initial_state>::type init_states;
        ::boost::mpl::for_each<init_states, boost::msm::wrap<mpl::placeholders::_1> >
            (call_init<InitEvent>(&m_state_list[0],InitEvent()));
    }

    // Main function used by clients of the derived FSM to make
    // transitions. Can also be called for internally (for example in an action method) generated events.
    template<class Event>
    execute_return process_event(Event const& evt)
    {
        // extend the table with tables from composite states
        typedef typename extend_table<Derived>::type complete_table;
        // use this table as if it came directly from the user
        typedef dispatch_table<Derived,HistoryPolicy,BaseState,CopyPolicy,complete_table,Event> table;

        HandledEnum ret_handled=HANDLED_FALSE;
        // if the state machine is terminated, do not handle any event
        if (is_flag_active< ::boost::msm::TerminateFlag>())
            return ::boost::make_tuple(HANDLED_TRUE,&this->m_states);
        // if the state machine is interrupted, do not handle any event
        // unless the event is the end interrupt event
        if ( is_flag_active< ::boost::msm::InterruptedFlag>() && 
            !is_flag_active< ::boost::msm::EndInterruptFlag<Event> >())
            return ::boost::make_tuple(HANDLED_TRUE,&this->m_states);

        // if we are already processing an event
        if (m_event_processing)
        {
            // event has to be put into the queue
            execute_return (state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>::*pf) (Event const& evt) = 
                &state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>::process_event; 
            transition_fct f = ::boost::bind(pf,this,evt);
            m_events_queue.push(f);
            return ::boost::make_tuple(HANDLED_TRUE,&this->m_states);
        }
        else
        {
            // event can be handled, processing
            m_event_processing = true;
            // prepare the next deferred event for handling
            deferred_fct next_deferred_event;
            if (!m_deferred_events_queue.empty())
            {
                next_deferred_event = m_deferred_events_queue.front();
                m_deferred_events_queue.pop();
            }
            typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
            bool handled = false;
            try
            {
                // dispatch the event to every region
                for (int i=0; i<nr_regions::value;++i)
                {	
                    std::pair<int,HandledEnum> res =
                        table::instance.entries[this->m_states[i]](
                        *static_cast<Derived*>(this), this->m_states[i], &m_state_list[0],evt);
                    this->m_states[i] = res.first;
                    handled = (handled || res.second);
                }
                // if the event has not been handled and we have orthogonal zones, then
                // generate an error on every active state 
                // for state machine states contained in other state machines, do not handle
                // but let the containing sm handle the error
                if (!handled && !is_contained())
                {
                    for (int i=0; i<nr_regions::value;++i)
                    {	
                        (static_cast<Derived*>(this))->no_transition(this->m_states[i],evt);
                    }
                }
            }
            catch (std::exception& e)
            {
                // give a chance to the concrete state machine to handle
                (static_cast<Derived*>(this))->exception_caught(e);
            }
            if (handled)
            {
                ret_handled = HANDLED_TRUE;
            }
            // after handling, take care of the deferred events
            if (next_deferred_event)
            {
                next_deferred_event();
            }
            m_event_processing = false;
            // now check if some events were generated in a transition and was not handled
            // because of another processing, and if yes, start handling them
            process_message_queue();
            return ::boost::make_tuple(ret_handled,&this->m_states);
        }       
    }

    // Getter that returns the current state of the FSM
    const std::vector<int>& current_state() const
    {
        return this->m_states;
    }

    // return the state whose id is passed or 0 if not found
    // caution if you need this, you probably need polymorphic states
    const BaseState* get_state_by_id(int id) const
    {
        typedef typename create_stt<Derived>::type stt;
        typedef typename generate_state_set<stt>::type state_list;
        BOOST_STATIC_CONSTANT(int, max_state = ( ::boost::mpl::size<state_list>::value));
        BOOST_ASSERT(id < (max_state));
        if (id < max_state)
            return (this->m_state_list[id]).get();
        // error
        return 0;
    }
    // true if the sm is used in another sm
    bool is_contained() const
    {
        return m_is_included;
    }
    // get a state
    // as a pointer
    template <class State>
    State get_state(typename ::boost::enable_if<typename ::boost::is_pointer<State>::type,void >::type* =0)
    {
        typedef typename create_stt<Derived>::type stt;
        return &(static_cast<typename boost::add_reference<typename ::boost::remove_pointer<State>::type>::type > 
            (*(m_state_list[get_state_id<stt,typename ::boost::remove_pointer<State>::type>::type::value])));	
    }
    // as a reference
    template <class State>
    State get_state(typename ::boost::enable_if<typename ::boost::is_reference<State>::type,void >::type* =0)
    {
        typedef typename create_stt<Derived>::type stt;
        return static_cast<State > 
            (*(m_state_list[get_state_id<stt,typename ::boost::remove_reference<State>::type>::type::value]));	
    }	

    // checks if a flag is active using the BinaryOp as folding function
    template <class Flag,class BinaryOp>
    bool is_flag_active()
    {
        flag_handler* flags_entries = get_entries_for_flag<Flag>();

        typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
        return std::accumulate(m_states.begin(),
            m_states.end(),false,
            ::boost::bind(typename BinaryOp::type(),
                    ::boost::bind(::boost::apply<bool>(),
                    ::boost::bind(::boost::msm::deref<flag_handler>(),
                        ::boost::bind(::boost::msm::plus2<flag_handler*,int>(),
                        flags_entries, _2)),
                        ::boost::ref(*this)), _1));		
    }
    // checks if a flag is active using no binary op if 1 region, or OR if > 1 regions
    template <class Flag>
    bool is_flag_active()
    {
        typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
        return FlagHelper<Flag,(nr_regions::value>1)>::helper(*this,get_entries_for_flag<Flag>());
    }
    // visit the currently active states (if these are defined as visitable
    // by implementing accept)
    void visit_current_states()
    {
        typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
        for (int i=0; i<nr_regions::value;++i)
        {
            m_visitors.execute(m_states[i]);
        }
    }
#define MSM_VISIT_STATE_SUB(z, n, unused) ARG ## n vis ## n
#define MSM_VISIT_STATE_EXECUTE(z, n, unused)                                    \
        template <BOOST_PP_ENUM_PARAMS(n, class ARG)>                               \
        void visit_current_states(BOOST_PP_ENUM(n, MSM_VISIT_STATE_SUB, ~ ) )         \
        {                                                                           \
            typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;   \
            for (int i=0; i<nr_regions::value;++i)                                                      \
            {                                                                                           \
                m_visitors.execute(m_states[i],BOOST_PP_ENUM_PARAMS(n,vis));                            \
            }                                                                                           \
        }
        BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_ADD(BOOST_MSM_VISITOR_ARG_SIZE,1), MSM_VISIT_STATE_EXECUTE, ~)
#undef MSM_VISIT_STATE_EXECUTE
#undef MSM_VISIT_STATE_SUB

 protected:    // interface for the derived class
     typedef std::vector<pBaseState>	pstate_base_list;

     // helper used to fill the initial states
     struct init_states
     {
         init_states(std::vector<int>& init):m_initial_states(init){}

         // History initializer function object, used with mpl::for_each
         template <class State>
         void operator()(::boost::msm::wrap<State> const&)
         {
             typedef typename create_stt<Derived>::type stt; 
             m_initial_states.push_back(get_state_id<stt,State>::type::value);
         }
         std::vector<int>& m_initial_states;
     };
     // Construct with the default initial states
     state_machine()
	     :state_base<BaseState>()
         ,CopyPolicy()
         ,m_states()
	     ,m_events_queue() 
	     ,m_deferred_events_queue()
	     ,m_history()
	     ,m_state_list()
         ,m_event_processing(false)
         ,m_is_included(false)
         ,m_visitors()
     {
         typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
         m_states.reserve(nr_regions::value);
         // build a sequence of regions if needed
         typedef typename get_regions_as_sequence<typename Derived::initial_state>::type initial_states;
         // initialize our list of states with the ones defined in Derived::initial_state
         ::boost::mpl::for_each< initial_states, ::boost::msm::wrap<mpl::placeholders::_1> >
                        (init_states(m_states));
         m_history.set_initial_states(m_states);
         // create states
         fill_states(this);
     }
     // template constructor. Needed only for sub-fsms having exit pseudo states.
     template <class ContainingSM>
     state_machine(ContainingSM* containing_sm)
         :state_base<BaseState>()
         ,CopyPolicy()
         ,m_states()
         ,m_events_queue() 
         ,m_deferred_events_queue()
         ,m_history()
         ,m_state_list()
         ,m_event_processing(false)
         ,m_is_included(true)
         ,m_visitors()
     {
         typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
         m_states.reserve(nr_regions::value);
         // build a sequence of regions if needed
         typedef typename get_regions_as_sequence<typename Derived::initial_state>::type initial_states;
         // initialize our list of states with the ones defined in Derived::initial_state
         ::boost::mpl::for_each< initial_states, boost::msm::wrap<mpl::placeholders::_1> >
                        (init_states(m_states));
         m_history.set_initial_states(m_states);
         // create states
         fill_states(containing_sm);
     }
     // assignment operator using the copy policy to decide if non_copyable, shallow or deep copying is necessary
     state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>& operator= 
         (state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy> const& rhs)
     {
         if (this != &rhs) 
         {
            CopyPolicy::operator=(rhs);
            do_copy<mpl::bool_<CopyPolicy::shallow_copy::value> >(rhs);
         }
        return *this;
     }
     state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy> 
         (state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy> const& rhs):CopyPolicy(rhs)
     {
        if (this != &rhs) 
        {
            typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
            m_states.reserve(nr_regions::value);
            // build a sequence of regions if needed
            typedef typename get_regions_as_sequence<typename Derived::initial_state>::type initial_states;
            // initialize our list of states with the ones defined in Derived::initial_state
            fill_states(this);
            do_copy<mpl::bool_<CopyPolicy::shallow_copy::value> >(rhs);
        }
     }
    // default row arguments for the compilers which accept this
    template <class Event>
    bool no_guard(Event const&){return true;}
    template <class Event>
    void no_action(Event const&){}

    // Template used to form rows in the transition table
    template<
        typename T1
        , class Event
        , typename T2
        , void (Derived::*action)(Event const&) 
#if  !defined(__GNUC__)
        = static_cast<void (Derived::*)(Event const&)>(&no_action<Event>)
#endif
        , bool (Derived::*guard)(Event const&) 
#if  !defined(__GNUC__)
        = static_cast<bool (Derived::*)(Event const&)>(&no_guard<Event>)
#endif
    >
    struct row
    {
        // if the source has no automatic creation (i.e. is an exit pseudo state), then
        // current_state_type becomes the result of get_owner
        // meaning the containing SM from which the exit occurs
        typedef typename ::boost::mpl::eval_if<
            typename has_no_automatic_create<T1>::type,
            get_owner<T1,Derived>,
            ::boost::mpl::identity<T1> >::type current_state_type;

        // if Target is a sequence, then we have a fork and expect a sequence of explicit_entry
        // else if Target is an explicit_entry, next_state_type becomes the result of get_owner
        // meaning the containing SM if the row is "outside" the containing SM or else the explicit_entry state itself
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::is_sequence<T2>::type,
            get_fork_owner<T2,Derived>,
            ::boost::mpl::eval_if<
                    typename has_no_automatic_create<T2>::type,
                    get_owner<T2,Derived>,
                    ::boost::mpl::identity<T2> >
        >::type next_state_type;

        typedef Event event;

        // if a guard condition is here, call it to check that the event is accepted
        static bool check_guard(Derived& fsm,Event const& evt)
        {
            if (!guard || (guard && (fsm.*guard)(evt)))
                return true;
            return false;
        }
        // Take the transition action and return the next state.
        static std::pair<int,HandledEnum> execute(Derived& fsm, int state, pBaseState* all_states, Event const& evt)
        {
            typedef typename create_stt<Derived>::type stt;

            BOOST_STATIC_CONSTANT(int, current_state = (get_state_id<stt,current_state_type>::type::value));
            BOOST_STATIC_CONSTANT(int, next_state = (get_state_id<stt,next_state_type>::type::value));
            BOOST_ASSERT(state == (current_state));
            // if T1 is an exit pseudo state, then take the transition only if the pseudo exit state is active
            if (!::boost::is_same<T1,current_state_type>::value && 
                !is_exit_state_active<T1,get_owner<T1,Derived> >(fsm))
            {
                return std::make_pair(current_state,HANDLED_FALSE);
            }
            if (!check_guard(fsm,evt))
            {
                // guard rejected the event, we stay in the current one
                return std::make_pair(current_state,HANDLED_GUARD_REJECT);
            }

            // the guard condition has already been checked
            execute_exit<current_state_type>(all_states[current_state].get(),evt);
            if (action)
            {
                // then call the action method
                (fsm.*action)(evt);
            }
            // and finally the entry method of the new current state
            convert_event_and_execute_entry<next_state_type,T2>(all_states[next_state].get(),evt);
            return std::make_pair(next_state,HANDLED_TRUE);
        }
    };

    // row having only a guard condition
    template<
        typename T1
        , class Event
        , typename T2
        , bool (Derived::*guard)(Event const&)
    >
    struct g_row
    {
        // if the source has no automatic creation (i.e. is an exit pseudo state), then
        // current_state_type becomes the result of get_owner
        // meaning the containing SM from which the exit occurs
        typedef typename ::boost::mpl::eval_if<
            typename has_no_automatic_create<T1>::type,
            get_owner<T1,Derived>,
            ::boost::mpl::identity<T1> >::type current_state_type;

        // if Target is a sequence, then we have a fork and expect a sequence of explicit_entry
        // else if Target is an explicit_entry, next_state_type becomes the result of get_owner
        // meaning the containing SM if the row is "outside" the containing SM or else the explicit_entry state itself
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::is_sequence<T2>::type,
            get_fork_owner<T2,Derived>,
            ::boost::mpl::eval_if<
                    typename has_no_automatic_create<T2>::type,
                    get_owner<T2,Derived>,
                    ::boost::mpl::identity<T2> >
        >::type next_state_type;

        typedef Event event;

        // if a guard condition is defined, call it to check that the event is accepted
        static bool check_guard(Derived& fsm,Event const& evt)
        {
            if (!guard || (guard && (fsm.*guard)(evt)))
                return true;
            return false;
        }
        // Take the transition action and return the next state.
        static std::pair<int,HandledEnum> execute(Derived& fsm, int state, pBaseState* all_states, Event const& evt)
        {
            typedef typename create_stt<Derived>::type stt;
            BOOST_STATIC_CONSTANT(int, current_state = (get_state_id<stt,current_state_type>::type::value));
            BOOST_STATIC_CONSTANT(int, next_state = (get_state_id<stt,next_state_type>::type::value));
            BOOST_ASSERT(state == (current_state));
            // if T1 is an exit pseudo state, then take the transition only if the pseudo exit state is active
            if (!::boost::is_same<T1,current_state_type>::value && 
                !is_exit_state_active<T1,get_owner<T1,Derived> >(fsm))
            {
                return std::make_pair(current_state,HANDLED_FALSE);
            }
            if (!check_guard(fsm,evt))
            {
                // guard rejected the event, we stay in the current one
                return std::make_pair(current_state,HANDLED_GUARD_REJECT);
            }
            // the guard condition has already been checked
            execute_exit<current_state_type>(all_states[current_state].get(),evt);

            // and finally the entry method of the new current state
            convert_event_and_execute_entry<next_state_type,T2>(all_states[next_state].get(),evt);
            return std::make_pair(next_state,HANDLED_TRUE);
        }
    };

    // row having only an action method
    template<
        typename T1
        , class Event
        , typename T2
        , void (Derived::*action)(Event const&)
    >
    struct a_row
    {
        // if the source has no automatic creation (i.e. is an exit pseudo state), then
        // current_state_type becomes the result of get_owner
        // meaning the containing SM from which the exit occurs
        typedef typename ::boost::mpl::eval_if<
            typename has_no_automatic_create<T1>::type,
            get_owner<T1,Derived>,
            ::boost::mpl::identity<T1> >::type current_state_type;

        // if Target is a sequence, then we have a fork and expect a sequence of explicit_entry
        // else if Target is an explicit_entry, next_state_type becomes the result of get_owner
        // meaning the containing SM if the row is "outside" the containing SM or else the explicit_entry state itself
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::is_sequence<T2>::type,
            get_fork_owner<T2,Derived>,
            ::boost::mpl::eval_if<
                    typename has_no_automatic_create<T2>::type,
                    get_owner<T2,Derived>,
                    ::boost::mpl::identity<T2> >
        >::type next_state_type;

        typedef Event event;

        // Take the transition action and return the next state.
        static std::pair<int,HandledEnum> execute(Derived& fsm, int state, pBaseState* all_states, Event const& evt)
        {
            typedef typename create_stt<Derived>::type stt;
            BOOST_STATIC_CONSTANT(int, current_state = (get_state_id<stt,current_state_type>::type::value));
            BOOST_STATIC_CONSTANT(int, next_state = (get_state_id<stt,next_state_type>::type::value));
            BOOST_ASSERT(state == (current_state));

            // if T1 is an exit pseudo state, then take the transition only if the pseudo exit state is active
            if (!::boost::is_same<T1,current_state_type>::value && 
                !is_exit_state_active<T1,get_owner<T1,Derived> >(fsm))
            {
                return std::make_pair(current_state,HANDLED_FALSE);
            }
            // no need to check the guard condition
            // first call the exit method of the current state
            execute_exit<current_state_type>(all_states[current_state].get(),evt);
            if (action)
            {
                // then call the action method
                (fsm.*action)(evt);
            }
            // and finally the entry method of the new current state
            convert_event_and_execute_entry<next_state_type,T2>(all_states[next_state].get(),evt);
            return std::make_pair(next_state,HANDLED_TRUE);
        }
    };

    // row having no guard condition or action, simply transitions
    template<
        typename T1
        , class Event
        , typename T2
    >
    struct _row
    {
        // if the source has no automatic creation (i.e. is an exit pseudo state), then
        // current_state_type becomes the result of get_owner
        // meaning the containing SM from which the exit occurs
        typedef typename ::boost::mpl::eval_if<
                typename has_no_automatic_create<T1>::type,
                get_owner<T1,Derived>,
                ::boost::mpl::identity<T1> >::type current_state_type;

        // if Target is a sequence, then we have a fork and expect a sequence of explicit_entry
        // else if Target is an explicit_entry, next_state_type becomes the result of get_owner
        // meaning the containing SM if the row is "outside" the containing SM or else the explicit_entry state itself
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::is_sequence<T2>::type,
            get_fork_owner<T2,Derived>,
            ::boost::mpl::eval_if<
                    typename has_no_automatic_create<T2>::type,
                    get_owner<T2,Derived>,
                    ::boost::mpl::identity<T2> >
        >::type next_state_type;

        typedef Event event;

        // Take the transition action and return the next state.
        static std::pair<int,HandledEnum> execute(Derived& fsm, int state, pBaseState* all_states, Event const& evt)
        {
            typedef typename create_stt<Derived>::type stt;
            BOOST_STATIC_CONSTANT(int, current_state = (get_state_id<stt,current_state_type>::type::value));
            BOOST_STATIC_CONSTANT(int, next_state = (get_state_id<stt,next_state_type>::type::value));
            BOOST_ASSERT(state == (current_state));

            // if T1 is an exit pseudo state, then take the transition only if the pseudo exit state is active
            if (!::boost::is_same<T1,current_state_type>::value && 
                !is_exit_state_active<T1,get_owner<T1,Derived> >(fsm))
            {
                return std::make_pair(current_state,HANDLED_FALSE);
            }
            // first call the exit method of the current state
            execute_exit<current_state_type>(all_states[current_state].get(),evt);

            // and finally the entry method of the new current state
            convert_event_and_execute_entry<next_state_type,T2>(all_states[next_state].get(),evt);
            return std::make_pair(next_state,HANDLED_TRUE);
        }
    };
private:

	// helper used to call the init states at the start of the state machine
    template <class Event>
	struct call_init
	{
		call_init(pBaseState* states,Event const& an_event):all_states(states),evt(an_event){}
		template <class State>
		void operator()(boost::msm::wrap<State> const&)
		{
            typedef typename create_stt<Derived>::type stt;
			execute_entry<State>(all_states[get_state_id<stt,State>::type::value].get(),evt);
		}
	private:
		pBaseState* all_states;
        Event const& evt;
	};
    // helper for flag handling. Uses OR by default on orthogonal zones.
    template <class Flag,bool orthogonalStates>
    struct FlagHelper 
    {
        static bool helper(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>& sm,flag_handler* )
        {
            // by default we use OR to accumulate the flags
            return sm.is_flag_active<Flag,Flag_OR>();
        }
    };
    template <class Flag>
    struct FlagHelper<Flag,false>
    {
        static bool helper(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>& sm,flag_handler* flags_entries)
        {
            // just one active state, so we can call operator[] with 0
            return flags_entries[sm.current_state()[0]](sm);
        }
    };
    // handling of flag
    // defines a true and false functions plus a forwarding one for composite states
    template <class StateType,class Flag>
    struct FlagHandler
    {
        static bool flag_true(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>& )
        {
            return true;
        }
        static bool flag_false(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>& )
        {
            return false;
        }
        static bool forward(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>& fsm)
        {
            typedef typename create_stt<Derived>::type stt;
            return (static_cast<StateType& > 
                (*(fsm.m_state_list[get_state_id<stt,StateType>::type::value]))).is_flag_active<Flag>();
        }
    };
    template <class Flag>
    struct init_flags
    {
    private:
        // helper function, helps hiding the forward function for non-state machines states.
        template <class T>
        typename ::boost::enable_if<typename is_composite_state<T>::type,void >::type
            helper (flag_handler* an_entry,int offset,boost::msm::dummy<0> = 0 )
        {
            // composite => forward
            an_entry[offset] = &FlagHandler<T,Flag>::forward;
        }
        template <class T>
        typename ::boost::disable_if<typename is_composite_state<T>::type,void >::type
            helper (flag_handler* an_entry,int offset,boost::msm::dummy<1> = 0 )
        {
            // default no flag
            an_entry[offset] = &FlagHandler<T,Flag>::flag_false;
        }
        // attributes
        flag_handler* entries;

    public:
        init_flags(flag_handler* entries_)
            : entries(entries_)
        {}

        // Flags initializer function object, used with mpl::for_each
        template <class StateType>
        void operator()( ::boost::msm::wrap<StateType> const& )
        {
            typedef typename StateType::flag_list flags;
            typedef typename ::boost::mpl::contains<flags,Flag >::type found;
            typedef typename is_composite_state<StateType>::type composite;
            typedef typename create_stt<Derived>::type stt;

            BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,StateType>::type::value));
            if (found::type::value)
            {
                // the type defined the flag => true
                entries[state_id] = &FlagHandler<StateType,Flag>::flag_true;
            }
            else
            {
                // false or forward
                helper<StateType>(entries,state_id);
            }
        }
    };
    // maintains for every flag a static array containing the flag value for every state
    template <class Flag>
    flag_handler* get_entries_for_flag()
    {
        typedef typename create_stt<Derived>::type Stt;
        typedef typename generate_state_set<Stt>::type state_list;
        BOOST_STATIC_CONSTANT(int, max_state = (mpl::size<state_list>::value));

        static flag_handler flags_entries[max_state];
        // build a state list
        ::boost::mpl::for_each<state_list, boost::msm::wrap< ::boost::mpl::placeholders::_1> >
                        (init_flags<Flag>(flags_entries));
        return flags_entries;	
    }

    // helper used to create a state using the correct constructor
    template <class State, class Enable=void>
    struct create_state_helper
    {
        static void set_sm(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>* ,pBaseState )
        {
	        // state doesn't need its sm
        }
    };
    // create a state requiring a pointer to the state machine
    template <class State>
    struct create_state_helper<State,typename boost::enable_if<typename State::needs_sm >::type>
    {
        static void set_sm(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>* sm,pBaseState new_state)
        {
	        // create and set the fsm
	        static_cast<State*>(new_state.get())->set_sm_ptr(static_cast<Derived*>(sm));
        }
    };
	// A function object for use with mpl::for_each that stuffs
    // states into the state list.
    template<class ContainingSM>
    struct add_state
    {
        add_state(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>* self_,ContainingSM* sm)
	        : self(self_),containing_sm(sm){}

        // State is a sub fsm with exit pseudo states and gets a pointer to this fsm, so it can build a callback
        template <class StateType>
        typename ::boost::enable_if<
            typename has_exit_pseudo_states<StateType>::type,BaseState* >::type
        new_state_helper(boost::msm::dummy<0> = 0) const
        {
            return new StateType(containing_sm);
        }
        // State is a sub fsm without exit pseudo states and does not get a callback to this fsm
		// or state is a normal state and needs nothing except creation
        template <class StateType>
        typename ::boost::enable_if<
					typename ::boost::mpl::and_<typename ::boost::mpl::not_
                                                    <typename has_exit_pseudo_states<StateType>::type>::type,
									            typename ::boost::mpl::not_
                                                    <typename is_pseudo_exit<StateType>::type>::type
			       >::type,BaseState*>::type
        new_state_helper( ::boost::msm::dummy<1> = 0) const
        {
            return new StateType;
        }
        // state is exit pseudo state and gets callback to target fsm
        template <class StateType>
        typename ::boost::enable_if<typename is_pseudo_exit<StateType>::type,BaseState* >::type
        new_state_helper( ::boost::msm::dummy<2> = 0) const
        {
            BaseState* to_return = new StateType();
            execute_return (ContainingSM::*pf) (typename StateType::event const& evt)= 
                &ContainingSM::process_event;
            ::boost::function<execute_return (typename StateType::event const&)> fct = 
                ::boost::bind(pf,containing_sm,_1);
            static_cast<StateType*>(to_return)->set_forward_fct(fct);
            return to_return;
        }
        // for every defined state in the sm
        template <class State>
        void operator()( ::boost::msm::wrap<State> const&) const
        {
            //create a new state with the defined id and type
            typedef typename create_stt<Derived>::type stt;
            BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));

            pBaseState new_state (this->new_state_helper<State>());
            self->m_state_list[state_id]= new_state;
            create_state_helper<State>::set_sm(self,new_state);
            // create a visitor callback
            visitor_helper<State>(state_id,new_state.get());
        }
    private:
        // support possible use of a visitor if accept_sig is defined
        template <class StateType>
        typename ::boost::enable_if<typename has_accept_sig<StateType>::type,void >::type
        visitor_helper(int id,BaseState* astate,::boost::msm::dummy<0> = 0) const
        {
            visitor_args<StateType,StateType::accept_sig::args_number>::helper(self,id,astate);
        }
        template <class StateType>
        typename ::boost::disable_if<typename has_accept_sig<StateType>::type,void >::type
            visitor_helper(int id,BaseState* astate,::boost::msm::dummy<1> = 0) const
        {
            // nothing to do
        }
        // main unspecialized helper class
        template <class StateType,int ARGS>
        struct visitor_args;
#define MSM_VISITOR_ARGS_SUB(z, n, unused) BOOST_PP_CAT(_,BOOST_PP_ADD(n,1))
#define MSM_VISITOR_ARGS_EXECUTE(z, n, unused)                                              \
    template <class StateType>                                                              \
    struct visitor_args<StateType,n>                                                        \
    {                                                                                       \
        static void helper (state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>* sm,  \
        int id,BaseState* astate)                                                           \
        {                                                                                   \
            sm->m_visitors.insert(id, boost::bind(&StateType::accept,                       \
                static_cast<StateType*>(astate) BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM(n, MSM_VISITOR_ARGS_SUB, ~) ));                 \
        }                                                                                   \
    };
BOOST_PP_REPEAT(BOOST_PP_ADD(BOOST_MSM_VISITOR_ARG_SIZE,1), MSM_VISITOR_ARGS_EXECUTE, ~)
#undef MSM_VISITOR_ARGS_EXECUTE
#undef MSM_VISITOR_ARGS_SUB

        state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>* self;
        ContainingSM*                                    containing_sm;
    };

     // helper used to copy every state if needed
     struct copy_helper
     {
         copy_helper(pstate_base_list& to_fill,const pstate_base_list& rhs,
                     state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>* sm):
            m_tofill_states(to_fill),m_rhs(rhs),m_sm(sm){}
         template <class StateType>
         void operator()( ::boost::msm::wrap<StateType> const& )
         {
            typedef typename create_stt<Derived>::type stt;
            BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,StateType>::type::value));
            if (m_rhs.empty())
	            return;
            pBaseState copiedState 
	            (new StateType (*static_cast<StateType*> (m_rhs[state_id].get())));
            m_tofill_states[state_id] = copiedState;
            // possibly also set the visitor
            visitor_helper<StateType>(state_id,copiedState.get());

            // and for states that keep a pointer to the fsm, reset the pointer
            create_state_helper<StateType>::set_sm(m_sm,copiedState);
         }
         template <class StateType>
         typename ::boost::enable_if<typename has_accept_sig<StateType>::type,void >::type
             visitor_helper(int id,BaseState* astate) const
         {
             m_sm->m_visitors.insert(id, ::boost::bind(&StateType::accept,
                                                       static_cast<StateType*>(astate),_1));
         }
         template <class StateType>
         typename ::boost::disable_if<typename has_accept_sig<StateType>::type,void >::type
             visitor_helper(int id,BaseState* astate) const
         {
             // nothing to do
         }

         pstate_base_list&                         m_tofill_states;
         const pstate_base_list&                   m_rhs;
         state_machine<Derived,HistoryPolicy,
             BaseState,CopyPolicy>*	               m_sm;
     };

     // copy functions for shallow or deep copy (no need of a 3rd version for NoCopy as noncopyable handles it)
     template <class IsShallowCopy>
     typename ::boost::disable_if<typename IsShallowCopy::type,void >::type
     do_copy (state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy> const& rhs,
              ::boost::msm::dummy<0> = 0)
     {
         // deep copy simply assigns the data
         m_states = rhs.m_states;
         m_events_queue = rhs.m_events_queue;
         m_deferred_events_queue = rhs.m_deferred_events_queue;
         m_history = rhs.m_history;
         m_event_processing = rhs.m_event_processing;
         m_is_included = rhs.m_is_included;
         // except for the states themselves, which get duplicated
         typedef typename create_stt<Derived>::type Stt;

         typedef typename generate_state_set<Stt>::type state_list;
         ::boost::mpl::for_each<state_list, ::boost::msm::wrap< ::boost::mpl::placeholders::_1> >
                        (copy_helper(m_state_list,rhs.m_state_list,this));
     }
     template <class IsShallowCopy>
     typename ::boost::enable_if<typename IsShallowCopy::type,void >::type
     do_copy (state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy> const& rhs,
              ::boost::msm::dummy<1> = 0)
     {
         // shallow copy simply assigns the data
         m_states = rhs.m_states;
         m_events_queue = rhs.m_events_queue;
         m_deferred_events_queue = rhs.m_deferred_events_queue;
         m_history = rhs.m_history;
         m_state_list = rhs.m_state_list;
         m_event_processing = rhs.m_event_processing;
         m_is_included = rhs.m_is_included;
         m_visitors = rhs.m_visitors;
     }

     // helper used to call the correct entry/exit method
     // unfortunately in O(number of states in the sub-sm) but should be better than a virtual call
     template<class Event,bool is_entry> 
     struct entry_exit_helper
     {
         entry_exit_helper(int id,Event const& e,pBaseState* states):state_id(id),evt(e),all_states(states){}
         // helper for entry actions
         template <class IsEntry,class State>
         typename ::boost::enable_if<typename IsEntry::type,void >::type
         helper( ::boost::msm::dummy<0> = 0)
         {
             typedef typename create_stt<Derived>::type stt;
             BOOST_STATIC_CONSTANT(int, id = (get_state_id<stt,State>::value));
             if (id == state_id)
             {
                execute_entry<State>(all_states[id].get(),evt);
             }
         }
         // helper for exit actions
         template <class IsEntry,class State>
         typename boost::disable_if<typename IsEntry::type,void >::type
         helper( ::boost::msm::dummy<1> = 0)
         {
             typedef typename create_stt<Derived>::type stt;
             BOOST_STATIC_CONSTANT(int, id = (get_state_id<stt,State>::value));
             if (id == state_id)
             {
                 execute_exit<State>(all_states[id].get(),evt);
             }
         }
         // iterates through all states to find the one to be activated
         template <class State>
         void operator()( ::boost::msm::wrap<State> const&)
         {
             entry_exit_helper<Event,is_entry>::template helper< ::boost::mpl::bool_<is_entry>,State >();
         }
     private:
         int            state_id;
         Event const&   evt;
         pBaseState*    all_states;
     };
     // start for states machines which are themselves embedded in other state machines (composites)
	 template <class Event>
     void start(Event const& incomingEvent)
     {
         typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
         typedef typename create_stt<Derived>::type stt;
         typedef typename generate_state_set<stt>::type state_list;
         for (int i=0; i<nr_regions::value;++i)
         {
             //forward the event for handling by sub state machines
             ::boost::mpl::for_each<state_list, ::boost::msm::wrap< ::boost::mpl::placeholders::_1> >
                 (entry_exit_helper<Event,true>(m_states[i],incomingEvent,&m_state_list[0]));
         }
     }

     // helper used to set the correct state as active state upon entry into a fsm
     struct direct_event_start_helper 
     {
         direct_event_start_helper(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>* self_):self(self_){}
         // this variant is for the standard case, entry due to activation of the containing FSM
         template <class EventType>
         typename ::boost::disable_if<typename has_direct_entry<EventType>::type,void>::type
             operator()(EventType const& evt, ::boost::msm::dummy<0> = 0)
         {
             (static_cast<Derived*>(self))->on_entry(evt);
             self->start(evt);
         }

         // this variant is for the direct entry case (just one entry, not a sequence of entries)
         template <class EventType>
         typename ::boost::enable_if<
             typename ::boost::mpl::and_<
                        typename ::boost::mpl::not_< typename is_pseudo_entry<
                                    typename EventType::active_state>::type >::type,
                        typename ::boost::mpl::and_<typename has_direct_entry<EventType>::type,
                                                    typename ::boost::mpl::not_<typename ::boost::mpl::is_sequence
                                                            <typename EventType::active_state>::type >::type 
                                                    >::type>::type,void
                                  >::type
         operator()(EventType const& evt, ::boost::msm::dummy<1> = 0)
         {
             (static_cast<Derived*>(self))->on_entry(evt);
             typedef typename create_stt<Derived>::type stt;
             int state_id = get_state_id<stt,typename EventType::active_state>::value;
             BOOST_STATIC_ASSERT(EventType::active_state::zone_index >= 0);
             BOOST_STATIC_ASSERT(EventType::active_state::zone_index <= 
                 get_number_of_regions<typename Derived::initial_state>::type::value);
             // just set the correct zone, the others will be default/history initialized
             self->m_states[EventType::active_state::zone_index] = state_id;
             self->start(evt.m_event);
         }

         // this variant is for the fork entry case (a sequence on entries)
         template <class EventType>
         typename ::boost::enable_if<
             typename ::boost::mpl::and_<
                    typename ::boost::mpl::not_<
                                    typename is_pseudo_entry<typename EventType::active_state>::type >::type,
                    typename ::boost::mpl::and_<typename has_direct_entry<EventType>::type,
                                                typename ::boost::mpl::is_sequence<
                                                                typename EventType::active_state>::type 
                                                >::type>::type,void 
                                >::type
         operator()(EventType const& evt, ::boost::msm::dummy<2> = 0)
         {
             (static_cast<Derived*>(self))->on_entry(evt);
             ::boost::mpl::for_each<typename EventType::active_state, 
                                    ::boost::msm::wrap< ::boost::mpl::placeholders::_1> >
                                                        (fork_helper<EventType>(self,evt));
             // set the correct zones, the others (if any) will be default/history initialized
             self->start(evt.m_event);
         }

         // this variant is for the pseudo state entry case
         template <class EventType>
         typename ::boost::enable_if<
             typename is_pseudo_entry<typename EventType::active_state >::type,void
                                    >::type
         operator()(EventType const& evt, ::boost::msm::dummy<3> = 0)
         {
             // entry on the FSM
             (static_cast<Derived*>(self))->on_entry(evt);
             typedef typename create_stt<Derived>::type stt;
             int state_id = get_state_id<stt,typename EventType::active_state>::value;
             // given region starts with the entry pseudo state as active state
             self->m_states[EventType::active_state::zone_index] = state_id;
             self->start(evt.m_event);
             // and we process the transition in the zone of the newly active state
             // (entry pseudo states are, according to UML, a state connecting 1 transition outside to 1 inside
             self->process_event(evt.m_event);
         }
     private:
         // helper for the fork case, does almost like the direct entry
         state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>* self;
         template <class EventType>
         struct fork_helper
         {
             fork_helper(state_machine<Derived,HistoryPolicy,BaseState,CopyPolicy>* self_,EventType const& evt_):
                helper_self(self_),helper_evt(evt_){}
             template <class StateType>
             void operator()( ::boost::msm::wrap<StateType> const& )
             {
                 typedef typename create_stt<Derived>::type stt;
                 int state_id = get_state_id<stt,StateType>::value;
                 BOOST_STATIC_ASSERT(StateType::zone_index >= 0);
                 BOOST_STATIC_ASSERT(StateType::zone_index <= 
                                     get_number_of_regions<typename Derived::initial_state>::type::value);
                 helper_self->m_states[StateType::zone_index] = state_id;
             }
         private:
             state_machine<Derived,HistoryPolicy,
                                 BaseState,CopyPolicy>*       helper_self;
             EventType const&                                 helper_evt;
         };
     };

     // entry/exit for states machines which are themselves embedded in other state machines (composites)
	 template <class Event>
     void entry(Event const& incomingEvent)
     {
        // by default we activate the history/init states, can be overwritten by direct_event_start_helper
        typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
        for (int i=0; i<nr_regions::value;++i)
        {
            this->m_states[i] = m_history.history_entry(incomingEvent)[i];
        }
        // block immediate handling of events
        m_event_processing = true;
        // if the event is generating a direct entry/fork, set the current state(s) to the direct state(s)
        direct_event_start_helper(this)(incomingEvent);
        // handle messages which were generated and blocked in the init calls
        m_event_processing = false;
        process_message_queue();
     }
	 template <class Event>
     void exit(Event const& incomingEvent)
     {
        typedef typename get_number_of_regions<typename Derived::initial_state>::type nr_regions;
        typedef typename create_stt<Derived>::type stt;
        typedef typename generate_state_set<stt>::type state_list;
        for (int i=0; i<nr_regions::value;++i)
        {
            // first recursively exit the sub machines
            // forward the event for handling by sub state machines
            ::boost::mpl::for_each<state_list, ::boost::msm::wrap< ::boost::mpl::placeholders::_1> >
                (entry_exit_helper<Event,false>(m_states[i],incomingEvent,&m_state_list[0]));
        }
        // then call our own exit
        (static_cast<Derived*>(this))->on_exit(incomingEvent);
        // give the history a chance to handle this (or not).
        m_history.history_exit(this->m_states);
     }

    // no transition for event.
    template <class Event>
    static std::pair<int,HandledEnum> call_no_transition(Derived& , int state, pBaseState* ,Event const& )
    {
        return std::make_pair(state,HANDLED_FALSE);
    }
    // called for deferred events. Address set in the dispatch_table at init
    template <class Event>
    static std::pair<int,HandledEnum> defer_transition(Derived& fsm, int state, pBaseState*,Event const& e)
    {
        execute_return (Derived::*pf) (Event const& evt)= &Derived::process_event;
        Event temp (e);
        ::boost::function<execute_return () > f= ::boost::bind(pf,&fsm,temp);
        fsm.post_deferred_event(f);
        return std::make_pair(state,HANDLED_TRUE);
    }

    // Default no-transition handler. Can be replaced in the Derived SM class.
    template <class Event>
    int no_transition(int state, Event const& )
    {
        BOOST_ASSERT(false);
        return state;
    }
    // default exception handler. Can be replaced in the Derived SM class.
    void exception_caught (std::exception& )
    {
        BOOST_ASSERT(false);
    }
    // puts a deferred event in the queue
    void post_deferred_event(deferred_fct& deferred)
    {
        m_deferred_events_queue.push(deferred);
    }
    // removes one event from the message queue and processes it
    void process_message_queue()
    {
        if (!m_events_queue.empty())
        {
            transition_fct to_call = m_events_queue.front();
            m_events_queue.pop();
            to_call();
        }
    }

    // calls the entry/exit or on_entry/on_exit depending on the state type
    // (avoids calling virtually)
    // variant for FSMs
    template <class StateType,class EventType>
    static
        typename boost::enable_if<typename is_composite_state<StateType>::type,void >::type
        execute_entry(BaseState* astate,EventType const& evt,boost::msm::dummy<0> = 0)
    {
        // calls on_entry on the fsm then handles direct entries, fork, entry pseudo state
        (static_cast<StateType*>(astate))->entry(evt);
    }
    // variant for states
    template <class StateType,class EventType>
    static
        typename ::boost::disable_if<
            typename ::boost::mpl::or_<typename is_composite_state<StateType>::type,
                                       typename is_pseudo_exit<StateType>::type >::type,void >::type
    execute_entry(BaseState* astate,EventType const& evt, ::boost::msm::dummy<1> = 0)
    {
        // simple call to on_entry
        (static_cast<StateType*>(astate))->on_entry(evt);
    }
    // variant for exit pseudo states
    template <class StateType,class EventType>
    static
        typename ::boost::enable_if<typename is_pseudo_exit<StateType>::type,void >::type
    execute_entry(BaseState* astate,EventType const& evt, ::boost::msm::dummy<2> = 0)
    {
        // calls on_entry on the state then forward the event to the transition which should be defined inside the 
        // contained fsm
        (static_cast<StateType*>(astate))->on_entry(evt);
        (static_cast<StateType*>(astate))->forward_event(evt);
    }
    template <class StateType,class EventType>
    static
        typename ::boost::enable_if<typename is_composite_state<StateType>::type,void >::type
    execute_exit(BaseState* astate,EventType const& evt, ::boost::msm::dummy<0> = 0)
    {
        (static_cast<StateType*>(astate))->exit(evt);
    }
    template <class StateType,class EventType>
    static
        typename ::boost::disable_if<typename is_composite_state<StateType>::type,void >::type
    execute_exit(BaseState* astate,EventType const& evt, ::boost::msm::dummy<1> = 0)
    {
        // simple call to on_exit
        (static_cast<StateType*>(astate))->on_exit(evt);
    }

    // helper allowing special handling of direct entries / fork
    template <class StateType,class TargetType,class EventType>
    static
        typename ::boost::disable_if<
            typename ::boost::mpl::or_<typename has_explicit_entry_state<TargetType>::type,
                                       ::boost::mpl::is_sequence<TargetType> >::type,void>::type
    convert_event_and_execute_entry(BaseState* astate,EventType const& evt, ::boost::msm::dummy<1> = 0)
    {
        // if the target is a normal state, do the standard entry handling
        execute_entry<StateType>(astate,evt);
    }
    template <class StateType,class TargetType,class EventType>
    static
        typename ::boost::enable_if<
            typename ::boost::mpl::or_<typename has_explicit_entry_state<TargetType>::type,
                                       ::boost::mpl::is_sequence<TargetType> >::type,void >::type
    convert_event_and_execute_entry(BaseState* astate,EventType const& evt, ::boost::msm::dummy<0> = 0)
    {
        // for the direct entry, pack the event in a wrapper so that we handle it differently during fsm entry
        execute_entry<StateType>(astate,direct_entry_event<TargetType,EventType>(evt));
    }

    // creates all the states
    template <class ContainingSM>
    void fill_states(ContainingSM* containing_sm=0)
    {
        typedef typename create_stt<Derived>::type stt;
        typedef typename generate_state_set<stt>::type state_list;
        BOOST_STATIC_CONSTANT(int, max_state = (mpl::size<state_list>::value));
        // allocate the place without reallocation
        m_state_list.resize(max_state);
        m_visitors.fill_visitors(max_state);
        ::boost::mpl::for_each<state_list, ::boost::msm::wrap< ::boost::mpl::placeholders::_1> >
            (add_state<ContainingSM>(this,containing_sm));
    }

    // Template used to form forwarding rows in the transition table for every row of a composite SM
    template<
        typename T1
        , class Event
    >
    struct frow
    {
        typedef T1                  current_state_type;
        typedef T1                  next_state_type;
        typedef Event               event;

        // Take the transition action and return the next state.
        static std::pair<int,HandledEnum> execute(Derived& fsm, int state, pBaseState* ,Event const& evt)
        {
	        execute_return res = 
                (static_cast<T1& > (*(fsm.m_state_list[state]))).process_event(evt);
            typedef typename create_stt<Derived>::type stt;
	        return std::make_pair(get_state_id<stt,T1>::type::value,res.get<0>());
        }
    };
public:
    template <class Composite,class Event>
    struct make_frow 
    {
        typedef frow<Composite,Event> type;
    };
    // gets the transition table from a composite and make from it a forwarding row
    template <class Composite>
    struct get_transition_table_as_frow
    {
        // first get the table of a composite
        typedef typename recursive_get_transition_table<Composite>::type original_table;
        // and add for every event a forwarding row
        typedef typename generate_event_set<original_table>::type all_events;
        typedef typename ::boost::mpl::fold<
            all_events, ::boost::mpl::vector<>,
            ::boost::mpl::push_back< ::boost::mpl::placeholders::_1,
                                     frow<Composite, ::boost::mpl::placeholders::_2> > >::type type;
    };

    // extends the transition table with rows from composite states
    template <class Composite>
    struct extend_table
    {
        // add the init states
        typedef typename create_stt<Composite>::type stt;
		// get the state set
		typedef typename generate_state_set<stt>::type states;
        // for every state, add its transition table (if any)
        // transformed as frow
		typedef typename ::boost::mpl::fold<states,stt,
				::boost::mpl::insert_range< ::boost::mpl::placeholders::_1, 
                                            ::boost::mpl::end< ::boost::mpl::placeholders::_1>,
								            get_transition_table_as_frow< ::boost::mpl::placeholders::_2> > 
		>::type type;
    };
private:
    template <class Fsm, class History,class UserBaseState, class Copy,class Stt, class Event>
    friend struct dispatch_table;
    template <typename T1,class Event> friend struct frow;

    // data members
    std::vector<int>            m_states;
    events_queue_t              m_events_queue;
    deferred_events_queue_t     m_deferred_events_queue;
    HistoryPolicy               m_history;
    pstate_base_list            m_state_list;
    bool                        m_event_processing;
    bool                        m_is_included;
    visitor_fct_helper<BaseState>
                                m_visitors;
};

} } // boost::msm
#endif //BOOST_MSM_STATEMACHINE_H

