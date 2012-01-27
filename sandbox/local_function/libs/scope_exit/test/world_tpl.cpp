
#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/vector.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#define BOOST_TEST_MODULE TestWorldTpl
#include <boost/test/unit_test.hpp>
#include <vector>

struct person; BOOST_TYPEOF_REGISTER_TYPE(peron)
struct person {};

template<typename Person> struct world; BOOST_TYPEOF_REGISTER_TEMPLATE(world, 1)
template<typename Person>
struct world {
    void add_person(Person const& a_person);
    std::vector<Person> persons_;
};

//[world_tpl
template<typename Person>
void world<Person>::add_person(Person const& a_person) {
    bool commit = false;
    persons_.push_back(a_person);

    BOOST_SCOPE_EXIT_TPL(&commit, this_) { // Use `_TPL` postfix.
        if(!commit) this_->persons_.pop_back();
    } BOOST_SCOPE_EXIT_END

    // ...

    commit = true;
}
//]

BOOST_AUTO_TEST_CASE( test_world_tpl ) {
    world<person> w;
    person p;
    w.add_person(p);
    BOOST_CHECK( w.persons_.size() == 1 );
}

