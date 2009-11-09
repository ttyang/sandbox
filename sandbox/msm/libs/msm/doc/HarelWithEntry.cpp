#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>

namespace msm = boost::msm;

namespace {
    // events
    struct AnyBtnPressed {};
    struct AlarmBeeps30s {};
    struct P1 {};
    struct P2 {};
    struct P {};
    // Concrete FSM implementation
    struct Clock_ : public msm::front::state_machine_def<Clock_>
    {
        struct Displays : public msm::front::state<> 
        {
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) {std::cout << "Entering Displays"<< std::endl;}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {std::cout << "Leaving Displays"<< std::endl;}
        };
        struct AlarmBeeps_ : public msm::front::state_machine_def<AlarmBeeps_>
        {  
            // states
            struct Alarm1Beeps : public msm::front::state<>, public msm::front::explicit_entry<0>
            {
                template <class Event,class FSM>
                void on_entry(Event const&,FSM& ) {std::cout << "Entering Alarm1Beeps"<< std::endl;}
                template <class Event,class FSM>
                void on_exit(Event const&,FSM& ) {std::cout << "Leaving Alarm1Beeps"<< std::endl;}
            };
            struct Alarm2Beeps : public msm::front::state<>, public msm::front::explicit_entry<0>
            {
                template <class Event,class FSM>
                void on_entry(Event const&,FSM& ) {std::cout << "Entering Alarm2Beeps"<< std::endl;}
                template <class Event,class FSM>
                void on_exit(Event const&,FSM& ) {std::cout << "Leaving Alarm2Beeps"<< std::endl;}
            };
            struct BothBeep : public msm::front::state<>, public msm::front::explicit_entry<0>
            {
                template <class Event,class FSM>
                void on_entry(Event const&,FSM& ) {std::cout << "Entering BothBeep"<< std::endl;}
                template <class Event,class FSM>
                void on_exit(Event const&,FSM& ) {std::cout << "Leaving BothBeep"<< std::endl;}
            };

            // the initial state of the AlarmBeeps SM. Must be defined. Will not be used as we use only explicit entries
            typedef mpl::vector< Alarm1Beeps > initial_state;
            // as we have no transition table, we need to create the states explicitly
            typedef mpl::vector<Alarm1Beeps,Alarm2Beeps,BothBeep> explicit_creation;

            // Transition table for AlarmBeeps. Can be empty as no transition defined
            struct transition_table : mpl::vector<> {};
        };
        typedef msm::back::state_machine<AlarmBeeps_> AlarmBeeps;
        // the initial state of the Clock SM. Must be defined
        typedef Displays initial_state;
        // Transition table for Clock
        struct transition_table : mpl::vector<
            //    Start      Event          Next                      Action	Guard
            //  +-----------+-------------+-------------------------+----------+----------------------+
            _row  < Displays  , P1          , AlarmBeeps::direct<AlarmBeeps_::Alarm1Beeps>               >,
            _row  < Displays  , P2          , AlarmBeeps::direct<AlarmBeeps_::Alarm2Beeps>               >,
            _row  < Displays  , P           , AlarmBeeps::direct<AlarmBeeps_::BothBeep>                  >,
            _row  < AlarmBeeps,AnyBtnPressed, Displays                                                   >,
            _row  < AlarmBeeps,AlarmBeeps30s, Displays                                                   >
            //  +-----------+-------------+--------------------------+----------+----------------------+
        > {};
    };
    typedef msm::back::state_machine<Clock_> Clock;
}

void test()
{
    Clock sm;
    sm.start();
    std::cout << "Sending P1" << std::endl;
    sm.process_event(P1());
    std::cout << "Sending AnyBtnPressed" << std::endl;
    sm.process_event(AnyBtnPressed());
    std::cout << "Sending P2" << std::endl;
    sm.process_event(P2());
    std::cout << "Sending AnyBtnPressed" << std::endl;
    sm.process_event(AnyBtnPressed());
    std::cout << "Sending P" << std::endl;
    sm.process_event(P());

}
int main()
{
    test();
    return 0;
}


