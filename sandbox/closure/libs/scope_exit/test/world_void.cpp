
#include <boost/scope_exit.hpp>
#define BOOST_TEST_MODULE TestWorldVoid
#include <boost/test/unit_test.hpp>
#include <vector>

struct person {};

//[test_world_void
struct world_t {
    std::vector<person> persons;
    bool commit;
} world; // Global variable.

void add_person(person const& a_person) {
    world.commit = false;
    world.persons.push_back(a_person);

    BOOST_SCOPE_EXIT(void) { // No captures.
        if(!world.commit) world.persons.pop_back();
    } BOOST_SCOPE_EXIT_END

    // ...

    world.commit = true;
}
//]

BOOST_AUTO_TEST_CASE( test_world_void ) {
    person p;
    add_person(p);
    BOOST_CHECK( world.persons.size() == 1 );
}

