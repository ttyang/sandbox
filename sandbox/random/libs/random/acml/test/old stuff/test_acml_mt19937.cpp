#include <boost/random/acml/engine.hpp>

#define BOOST_RANDOM_URNG boost::random::acml::mt19937

#define BOOST_RANDOM_SEED_WORDS 607*2

#define BOOST_RANDOM_VALIDATION_VALUE 0.039230772001715764
#define BOOST_RANDOM_SEED_SEQ_VALIDATION_VALUE 0.73105942788451372
#define BOOST_RANDOM_ITERATOR_VALIDATION_VALUE 0.72330291632639643

#define BOOST_RANDOM_GENERATE_VALUES { 0x78EB0905U, 0x61766547U, 0xCB507F64U, 0x94FA3EC0U }

//#include "../../test/test_generator.ipp"


#include "../../test/concepts.hpp"
#include <boost/random/seed_seq.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using boost::random::test::RandomNumberEngine;
BOOST_CONCEPT_ASSERT((RandomNumberEngine< BOOST_RANDOM_URNG >));


