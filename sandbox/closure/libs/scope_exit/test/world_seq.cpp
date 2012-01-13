
#include <boost/scope_exit.hpp>
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/vector.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#define BOOST_TEST_MODULE TestWorldSeq
#include <boost/test/unit_test.hpp>
#include <vector>
#include <iostream>
#include <sstream>

class person {
    friend class world;
public:
    typedef unsigned int id_t;
    typedef unsigned int evolution_t;

    person(void) : id_(0), evolution_(0) {}

    friend std::ostream& operator<<(std::ostream& o, person const& p) {
        return o << "person(" << p.id_ << ", " << p.evolution_ << ")";
    }
private:
    id_t id_;
    evolution_t evolution_;
};

BOOST_TYPEOF_REGISTER_TYPE(person)

class world {
public:
    typedef unsigned int id_t;

    world(void) : next_id_(1) {}

    void add_person(person const& a_person);

    friend std::ostream& operator<<(std::ostream& o, world const& w) {
        o << "world(" << w.next_id_ << ", {";
        BOOST_FOREACH(person const& p, w.persons_) {
            o << " " << p << ", ";
        }
        return o << "})";
    }
private:
    id_t next_id_;
    std::vector<person> persons_;
};

BOOST_TYPEOF_REGISTER_TYPE(world)

//[test_world_seq
void world::add_person(person const& a_person) {
    persons_.push_back(a_person);

    // This block must be no-throw.
    person& p = persons_.back();
    person::evolution_t checkpoint = p.evolution_;
    BOOST_SCOPE_EXIT( (checkpoint) (&p) (&persons_) ) { // Sequence, not commas.
        if(checkpoint == p.evolution_) persons_.pop_back();
    } BOOST_SCOPE_EXIT_END

    // ...

    checkpoint = ++p.evolution_;

    // Assign new identifier to the person.
    world::id_t const prev_id = p.id_;
    p.id_ = next_id_++;
    BOOST_SCOPE_EXIT( (checkpoint) (&p) (&next_id_) (prev_id) ) {
        if(checkpoint == p.evolution_) {
            next_id_ = p.id_;
            p.id_ = prev_id;
        }
    } BOOST_SCOPE_EXIT_END

    // ...

    checkpoint = ++p.evolution_;
}
//]

BOOST_AUTO_TEST_CASE( test_world_seq ) {
    person adam, eva;
    std::ostringstream oss;
    oss << adam;
    std::cout << oss.str() << std::endl;
    BOOST_CHECK( oss.str() == "person(0, 0)" );

    oss.str("");
    oss << eva;
    std::cout << oss.str() << std::endl;
    BOOST_CHECK( oss.str() == "person(0, 0)" );

    world w;
    w.add_person(adam);
    w.add_person(eva);
    oss.str("");
    oss << w;
    std::cout << oss.str() << std::endl;
    BOOST_CHECK( oss.str() == "world(3, { person(1, 2),  person(2, 2), })" );
}

