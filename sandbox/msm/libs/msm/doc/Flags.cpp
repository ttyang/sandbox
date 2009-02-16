#include <iostream>
#include <vector>
#include "boost/mpl/vector/vector50.hpp"
#include <boost/msm/state_machine.hpp>

using namespace boost::msm;

namespace  // Concrete FSM implementation
{
    // events
    struct play {};
    struct end_pause {};
    struct stop {};
    struct pause {};
    struct open_close {};
    struct NextSong {};
    struct PreviousSong {};

    // Flags. Allow information about a property of the current state
    struct PlayingPaused{};
    struct CDLoaded {};
    struct FirstSongPlaying {};

    // A "complicated" event type that carries some data.
    // forward
    struct player;
    struct cd_detected
    {
        cd_detected(std::string name,player& p)
            : name(name)
            , m_player(p)
        {}

        std::string name;
        player& m_player;
    };

    // Concrete FSM implementation 
    struct player : public state_machine<player>
    {
        // The list of FSM states
        struct Empty : public state<> 
        {
            // every (optional) entry/exit methods get the event passed.
            template <class Event>
            void on_entry(Event const& ) {std::cout << "entering: Empty" << std::endl;}
            template <class Event>
            void on_exit(Event const& ) {std::cout << "leaving: Empty" << std::endl;}
        };
        struct Open : public state<> 
        {	 
            typedef mpl::vector1<CDLoaded>		flag_list;
            template <class Event>
            void on_entry(Event const& ) {std::cout << "entering: Open" << std::endl;}
            template <class Event>
            void on_exit(Event const& ) {std::cout << "leaving: Open" << std::endl;}
        };

        struct Stopped : public state<> 
        {	 
            // when stopped, the CD is loaded
            typedef mpl::vector1<CDLoaded>		flag_list;
            template <class Event>
            void on_entry(Event const& ) {std::cout << "entering: Stopped" << std::endl;}
            template <class Event>
            void on_exit(Event const& ) {std::cout << "leaving: Stopped" << std::endl;}
        };

        // the player state machine contains a state which is himself a state machine
        // as you see, no need to declare it anywhere so Playing can be developed separately
        // by another team in another module. For simplicity I just declare it inside player
        struct Playing : public state_machine<Playing>
        {
            // when playing, the CD is loaded and we are in either pause or playing (duh)
            typedef mpl::vector2<PlayingPaused,CDLoaded>		flag_list;

            template <class Event>
            void on_entry(Event const& ) {std::cout << "entering: Playing" << std::endl;}
            template <class Event>
            void on_exit(Event const& ) {std::cout << "leaving: Playing" << std::endl;}

            // The list of FSM states
            struct Song1 : public state<>
            {
                typedef mpl::vector1<FirstSongPlaying>		flag_list;
                template <class Event>
                void on_entry(Event const& ) {std::cout << "starting: First song" << std::endl;}
                template <class Event>
                void on_exit(Event const& ) {std::cout << "finishing: First Song" << std::endl;}

            };
            struct Song2 : public state<>
            {	 
                template <class Event>
                void on_entry(Event const& ) {std::cout << "starting: Second song" << std::endl;}
                template <class Event>
                void on_exit(Event const& ) {std::cout << "finishing: Second Song" << std::endl;}
            };
            struct Song3 : public state<>
            {	 
                template <class Event>
                void on_entry(Event const& ) {std::cout << "starting: Third song" << std::endl;}
                template <class Event>
                void on_exit(Event const& ) {std::cout << "finishing: Third Song" << std::endl;}
            };
            // the initial state. Must be defined
            typedef Song1 initial_state;
            // transition actions
            void start_next_song(NextSong const&)       { std::cout << "Playing::start_next_song\n"; }
            void start_prev_song(PreviousSong const&)       { std::cout << "Playing::start_prev_song\n"; }
            // guard conditions

            typedef Playing pl; // makes transition table cleaner
            // Transition table for Playing
            struct transition_table : mpl::vector4<
                //    Start     Event         Next      Action				Guard
                //  +---------+-------------+---------+---------------------+----------------------+
                a_row < Song1   , NextSong    , Song2   , &pl::start_next_song                     >,
                a_row < Song2   , PreviousSong, Song1   , &pl::start_prev_song                     >,
                a_row < Song2   , NextSong    , Song3   , &pl::start_next_song                     >,
                a_row < Song3   , PreviousSong, Song2   , &pl::start_prev_song                     >
                //  +---------+-------------+---------+---------------------+----------------------+
            > {};
            // Replaces the default no-transition response.
            template <class Event>
            int no_transition(int state, Event const& e)
            {
                std::cout << "no transition from state " << state
                    << " on event " << typeid(e).name() << std::endl;
                return state;
            }
        };

        // state not defining any entry or exit
        struct Paused : public state<>
        {
            typedef mpl::vector2<PlayingPaused,CDLoaded>		flag_list;
        };

        // the initial state of the player SM. Must be defined
        typedef Empty initial_state;

#ifdef __MWERKS__
    public: // Codewarrior bug workaround.  Tested at 0x3202
#endif 
        // transition actions
        void start_playback(play const&)       { std::cout << "player::start_playback\n"; }
        void open_drawer(open_close const&)    { std::cout << "player::open_drawer\n"; }
        void close_drawer(open_close const&)   { std::cout << "player::close_drawer\n"; }
        void store_cd_info(cd_detected const& cd) 
        { 
            std::cout << "player::store_cd_info\n"; 
            // generate another event to test the queue
            cd.m_player.process_event(play());
        }
        void stop_playback(stop const&)        { std::cout << "player::stop_playback\n"; }
        void pause_playback(pause const&)      { std::cout << "player::pause_playback\n"; }
        void resume_playback(end_pause const&)      { std::cout << "player::resume_playback\n"; }
        void stop_and_open(open_close const&)  { std::cout << "player::stop_and_open\n"; }
        void stopped_again(stop const&)	{std::cout << "player::stopped_again\n";}
        // guard conditions


#ifdef __MWERKS__
    private:
#endif 
        typedef player p; // makes transition table cleaner

        // Transition table for player
        struct transition_table : mpl::vector<
            //    Start     Event         Next      Action				Guard
            //  +---------+-------------+---------+---------------------+----------------------+
            a_row < Stopped , play        , Playing , &p::start_playback                       >,
            a_row < Stopped , open_close  , Open    , &p::open_drawer                          >,
            a_row < Stopped , stop        , Stopped , &p::stopped_again                        >,
            //  +---------+-------------+---------+---------------------+----------------------+
            a_row < Open    , open_close  , Empty   , &p::close_drawer                         >,
            //  +---------+-------------+---------+---------------------+----------------------+
            a_row < Empty   , open_close  , Open    , &p::open_drawer                          >,
            a_row < Empty   , cd_detected , Stopped , &p::store_cd_info                        >,
            //  +---------+-------------+---------+---------------------+----------------------+
            a_row < Playing , stop        , Stopped , &p::stop_playback                        >,
            a_row < Playing , pause       , Paused  , &p::pause_playback                       >,
            a_row < Playing , open_close  , Open    , &p::stop_and_open                        >,
            //  +---------+-------------+---------+---------------------+----------------------+
            a_row < Paused  , end_pause   , Playing , &p::resume_playback                      >,
            a_row < Paused  , stop        , Stopped , &p::stop_playback                        >,
            a_row < Paused  , open_close  , Open    , &p::stop_and_open                        >
            //  +---------+-------------+---------+---------------------+----------------------+
        > {};

        // Replaces the default no-transition response.
        template <class Event>
        int no_transition(int state, Event const& e)
        {
            std::cout << "no transition from state " << state
                << " on event " << typeid(e).name() << std::endl;
            return state;
        }
    };

    //
    // Testing utilities.
    //
    static char const* const state_names[] = { "Stopped", "Open", "Empty", "Playing", "Paused" };

    void pstate(player const& p)
    {
        std::cout << " -> " << state_names[p.current_state()[0]] << std::endl;
    }

    void test()
    {
        player p;

        // needed to start the highest-level SM. This will call on_entry and mark the start of the SM
        p.start(); 
        // tests some flags
        std::cout << "CDLoaded active:" << std::boolalpha << p.is_flag_active<CDLoaded>() << std::endl; //=> false (no CD yet)
        // go to Open, call on_exit on Empty, then action, then on_entry on Open
        p.process_event(open_close()); pstate(p);
        p.process_event(open_close()); pstate(p);
        p.process_event(cd_detected("louie, louie",p));

        // no need to call play() as the previous event does it in its action method

        // at this point, Play is active 
        std::cout << "PlayingPaused active:" << std::boolalpha << p.is_flag_active<PlayingPaused>() << std::endl;//=> true
        std::cout << "FirstSong active:" << std::boolalpha << p.is_flag_active<FirstSongPlaying>() << std::endl;//=> true

        // make transition happen inside it. Player has no idea about this event but it's ok.
        p.process_event(NextSong());pstate(p); //2nd song active
        p.process_event(NextSong());pstate(p);//3rd song active
        p.process_event(PreviousSong());pstate(p);//2nd song active
        std::cout << "FirstSong active:" << std::boolalpha << p.is_flag_active<FirstSongPlaying>() << std::endl;//=> false

        std::cout << "PlayingPaused active:" << std::boolalpha << p.is_flag_active<PlayingPaused>() << std::endl;//=> true
        p.process_event(pause()); pstate(p);
        std::cout << "PlayingPaused active:" << std::boolalpha << p.is_flag_active<PlayingPaused>() << std::endl;//=> true
        // go back to Playing
        // as you see, it starts back from the original state
        p.process_event(end_pause());  pstate(p);
        p.process_event(pause()); pstate(p);
        p.process_event(stop());  pstate(p);
        std::cout << "PlayingPaused active:" << std::boolalpha << p.is_flag_active<PlayingPaused>() << std::endl;//=> false
        std::cout << "CDLoaded active:" << std::boolalpha << p.is_flag_active<CDLoaded>() << std::endl;//=> true

        // event leading to the same state
        p.process_event(stop());  pstate(p);
    }
}

int main()
{
    test();
    return 0;
}
