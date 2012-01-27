
#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/vector.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#define BOOST_TEST_MODULE TestWorldSeq
#include <boost/test/unit_test.hpp>
#include <vector>

struct person; BOOST_TYPEOF_REGISTER_TYPE(person)
struct person {};

struct world; BOOST_TYPEOF_REGISTER_TYPE(world)
struct world {
    void add_person(person const& a_person);
    std::vector<person> persons_;
};

//[world_seq
void world::add_person(person const& a_person) {
    bool commit = false;

    persons_.push_back(a_person);
    BOOST_SCOPE_EXIT( (&commit) (&persons_) ) {
        if(!commit) persons_.pop_back();
    } BOOST_SCOPE_EXIT_END

    // ...

    commit = true;
}
//]

BOOST_AUTO_TEST_CASE( test_world_seq ) {
    world w;
    person p;
    w.add_person(p);
    BOOST_CHECK( w.persons_.size() == 1 );
}

