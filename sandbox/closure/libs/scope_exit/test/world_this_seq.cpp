
#include <boost/scope_exit.hpp>
#include <boost/config.hpp>
#define BOOST_TEST_MODULE TestWorldCommitThis
#include <boost/test/unit_test.hpp>
#include <vector>

struct person {};

struct world {
    void add_person(person const& a_person);
    std::vector<person> persons_;
};

void world::add_person(person const& a_person) {
    bool commit = false;

    persons_.push_back(a_person);
#ifdef BOOST_NO_LAMBDAS
    //[test_world_commit_this_
    BOOST_SCOPE_EXIT( (&commit) (this_) ) { // Capture object `this_`.
        if(!commit) this_->persons_.pop_back();
    } BOOST_SCOPE_EXIT_END
    //]
#else
    //[test_world_commit_this
    BOOST_SCOPE_EXIT( (&commit) (this) ) { // Use `this` (C++11).
        if(!commit) this->persons_.pop_back();
    }; // Use `;` instead of `BOOST_SCOPE_EXIT_END` (C++11).
    //]
#endif

    // ...

    commit = true;
}

BOOST_AUTO_TEST_CASE( test_world_commit_this ) {
    world w;
    person p;
    w.add_person(p);
    BOOST_CHECK( w.persons_.size() == 1 );
}

