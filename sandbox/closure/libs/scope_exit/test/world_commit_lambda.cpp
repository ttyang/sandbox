
#include <boost/config.hpp>

#ifndef BOOST_NO_LAMBDAS

#define BOOST_TEST_MODULE TestWorldCommitLambda
#include <boost/test/unit_test.hpp>
#include <vector>

struct person {};

struct world {
    void add_person(person const& a_person);
    std::vector<person> persons_;
};

//[test_world_commit_lambda
#include <functional>

struct scope_exit {
    scope_exit(std::function<void (void)> f) : f_(f) {}
    ~scope_exit(void) { f_(); }
private:
    std::function<void (void)> f_;
};

void world::add_person(person const& a_person) {
    bool commit = false;

    persons_.push_back(a_person);
    scope_exit on_exit1([&commit, &persons_]() { // Use C++11 lambda.
        if(!commit) persons_.pop_back();
    });

    // ...

    commit = true;
}
//]

BOOST_AUTO_TEST_CASE( test_world_commit_lambda ) {
    world w;
    person p;
    w.add_person(p);
    BOOST_CHECK( w.persons_.size() == 1 );
}

#else // No lambdas (trivial test).

int main(void) { return 0; }

#endif

