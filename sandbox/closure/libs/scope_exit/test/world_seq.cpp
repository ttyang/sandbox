
#include <boost/scope_exit.hpp>
//#define BOOST_TEST_MODULE TestWorldCommitSeq
//#include <boost/test/unit_test.hpp>
#include <vector>

struct person {};

struct world {
    void add_person(person const& a_person);
    std::vector<person> persons_;
};

//[test_world_commit_seq
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

//BOOST_AUTO_TEST_CASE( test_world_commit_seq ) {
int main() {
    world w;
    person p;
    w.add_person(p);
//    BOOST_CHECK( w.persons_.size() == 1 );
    return 0;
}

