
#include <boost/scope_exit.hpp>
#define BOOST_TEST_MODULE TestWorldTplSeq
#include <boost/test/unit_test.hpp>

struct person {};

template<typename Person>
struct world {
    void add_person(Person const& a_person);
    std::vector<Person> persons_;
};

//[test_world_tpl_seq
template<typename Person>
void world<Person>::add_person(Person const& a_person) {
    bool commit = false;
    persons_.push_back(a_person);

    BOOST_SCOPE_EXIT_TPL( (&commit) (this_) ) {
        if(!commit) this_->persons_.pop_back();
    } BOOST_SCOPE_EXIT_END

    // ...

    commit = true;
}
//]

BOOST_AUTO_TEST_CASE( test_world_tpl_seq ) {
    world<person> w;
    person p;
    w.add_person(p);
    BOOST_CHECK( w.persons_.size() == 1 );
}

