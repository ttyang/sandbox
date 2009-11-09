#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>

namespace msm = boost::msm;

namespace {
    // events
    struct AnyBtnPressed {};
    struct AlarmBeeps30s {};
    struct P 
    {
        P(int id):index(id){}
        // the bit(s) of the corresponding alarm
        int index;
    };
    // Concrete FSM implementation
    struct Clock_ : public msm::front::state_machine_def<Clock_>
    {
        struct Displays : public msm::front::state<> {};
        class AlarmBeeps_ : public msm::front::state_machine_def<AlarmBeeps_>
        {            
        public:
            template <class Event,class FSM>
            void on_entry(Event const& evt,FSM& fsm) 
            {
                // let each orthogonal zone handle the event (can be handled by more than 1)
                fsm.process_event(evt);
            }

            template <int Index>
            struct Alarm_ : public msm::front::state_machine_def<Alarm_<Index> >
            {
                struct NoBeep : public msm::front::state<> 
                {
                    template <class Event,class FSM>
                    void on_entry(Event const&,FSM& ) {std::cout << "Entering NoBeep:"<< Index << std::endl;}
                };
                struct Beeps : public msm::front::state<> 
                {
                    template <class Event,class FSM>
                    void on_entry(Event const&,FSM& ) {std::cout << "Beeping alarm:"<< Index << std::endl;}
                };
                typedef Alarm_<Index> A; // makes transition table cleaner
                // the initial state of the AlarmBeeps SM. Must be defined
                typedef NoBeep initial_state;
                // guard
                bool check_beep(const P& evt)
                {
                    // check if our bit is set in the event
                    return ((evt.index & Index)!=0);
                }
                // Transition table for AlarmBeeps
                struct transition_table : mpl::vector<
                    //    Start     Event         Next      Action				Guard
                    //  +---------+-------------+---------+------------------------+----------------------+
                    g_row  < NoBeep  , P           , Beeps                            ,&A::check_beep        >
                    //  +---------+-------------+---------+------------------------+----------------------+
                > {};
            };
            typedef msm::back::state_machine<Alarm_<1> > Alarm1;
            typedef msm::back::state_machine<Alarm_<2> > Alarm2;
            // the initial state of the AlarmBeeps SM. Must be defined
            typedef mpl::vector<Alarm1,Alarm2 > initial_state;

            // Transition table for AlarmBeeps. Can be empty as no transition defined
            struct transition_table : mpl::vector<> {};
        };
        typedef msm::back::state_machine<AlarmBeeps_> AlarmBeeps;
        // the initial state of the Clock SM. Must be defined
        typedef Displays initial_state;
        // Transition table for Clock
        struct transition_table : mpl::vector<
            //    Start     Event         Next      Action				Guard
            //  +-----------+-------------+------------+------------------------+----------------------+
            _row  < Displays  , P           , AlarmBeeps                                                 >,
            _row  < AlarmBeeps,AnyBtnPressed, Displays                                                   >,
            _row  < AlarmBeeps,AlarmBeeps30s, Displays                                                   >
            //  +-----------+-------------+------------+------------------------+----------------------+
        > {};
    };
    typedef msm::back::state_machine<Clock_> Clock;
}

void test()
{
    Clock sm;
    sm.start();
    std::cout << "Sending P(1)" << std::endl;
    sm.process_event(P(1));
    std::cout << "Sending AnyBtnPressed" << std::endl;
    sm.process_event(AnyBtnPressed());
    std::cout << "Sending P(2)" << std::endl;
    sm.process_event(P(2));
    std::cout << "Sending AnyBtnPressed" << std::endl;
    sm.process_event(AnyBtnPressed());
    std::cout << "Sending P(3)" << std::endl;
    sm.process_event(P(3));

}
int main()
{
    test();
    return 0;
}


