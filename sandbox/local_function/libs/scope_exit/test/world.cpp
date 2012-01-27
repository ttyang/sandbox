
#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/vector.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#define BOOST_TEST_MODULE TestWorld
#include <boost/test/unit_test.hpp>
#include <vector>

struct person; BOOST_TYPEOF_REGISTER_TYPE(person)
struct person {};

struct world; BOOST_TYPEOF_REGISTER_TYPE(world)
struct world {
    void add_person(person const& a_person);
    std::vector<person> persons_;
};

//[world
void world::add_person(person const& a_person) {
    bool commit = false;

    persons_.push_back(a_person);           // (1) direct action
    // Following block is executed when the enclosing scope exits.
    BOOST_SCOPE_EXIT(&commit, &persons_) {
        if(!commit) persons_.pop_back();    // (2) rollback action
    } BOOST_SCOPE_EXIT_END

    // ...                                  // (3) other operations

    commit = true;                          // (4) disable rollback actions
}
//]

BOOST_AUTO_TEST_CASE( test_world ) {
    world w;
    person p;
    w.add_person(p);
    BOOST_CHECK( w.persons_.size() == 1 );
}

