//  (C) Copyright 2009-2011 Frederic Bron.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "check_integral_constant.hpp"

#include <boost/type_traits/can_call.hpp>
#include "can_call_binary_classes.hpp"

TT_TEST_BEGIN(BOOST_TT_TRAIT_NAME)
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C465 volatile, C465 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C465 &, C465 volatile, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C465 const &, C465 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C466 const, C466 volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C466 volatile, C466 const &, ret const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C466 const volatile, C466 const, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C466 const &, C466 volatile, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C467 const volatile &, C467 const volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C468 volatile, C468 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C468 const &, C468 const, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C468 const volatile &, C468, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C469 &, C469 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C469 &, C469 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C469 const volatile &, C469 volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C470 volatile, C470 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C470 volatile, C470 const volatile &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C470 const volatile, C470 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C470 &, C470, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C470 &, C470 const, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C470 &, C470 volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C470 &, C470 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C470 volatile &, C470 volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C471, C471 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C471 volatile, C471 volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C471 const volatile, C471 volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C471 const volatile &, C471 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C471 const volatile &, C471 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C472 &, C472 const volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C472 const &, C472 const &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C472 volatile &, C472 volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C472 volatile &, C472 volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C472 const volatile &, C472 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C473, C473 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C473 volatile, C473, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C473 volatile, C473 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C473 const volatile, C473 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C473 const &, C473 const, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C473 const &, C473 const &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C474, C474, ret const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C474 volatile, C474 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C474 volatile, C474 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C474 &, C474 &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C474 volatile &, C474 const volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C474 volatile &, C474 volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C474 const volatile &, C474 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C475 const volatile, C475 const volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C475 volatile &, C475 const &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C476, C476, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C476 const, C476 const volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C476 const volatile &, C476 const volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C477, C477 volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C477, C477 &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C477 const, C477 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C477 const, C477 volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C477 const, C477 volatile &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C477 volatile, C477 &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C477 const volatile, C477, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C477 &, C477 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C477 const &, C477 volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C478 const, C478 const, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C478 const volatile, C478, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C478 const &, C478 const, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C478 volatile &, C478 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C479 const, C479 const volatile &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C479 const volatile, C479 volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C479 const volatile, C479 const volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C479 &, C479 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C479 &, C479 volatile &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C479 volatile &, C479 volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C479 const volatile &, C479, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C480, C480 const volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C480 const volatile, C480 volatile, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C480 &, C480 volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C480 &, C480 const volatile &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C480 const volatile &, C480 &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C480 const volatile &, C480 volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C481, C481 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C481 const, C481 const volatile &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C481 const volatile, C481, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C481 const volatile, C481 volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C481 const volatile, C481 const volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C481 volatile &, C481 &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C481 const volatile &, C481 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C482, C482, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C482 &, C482 volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C482 volatile &, C482 volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C482 volatile &, C482 const volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C482 const volatile &, C482 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C482 const volatile &, C482 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C483 volatile, C483 volatile, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C483 const volatile, C483 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C483 const &, C483 volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C483 volatile &, C483, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C483 const volatile &, C483 const volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C484 const, C484 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C484 volatile, C484 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C484 const volatile &, C484 &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C485, C485 const volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C485 const volatile, C485 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C485 const &, C485 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C485 const volatile &, C485 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C486, C486, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C486 const, C486 const volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C486 const &, C486 const, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C487, C487 const &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C487 volatile, C487 const volatile &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C487 const volatile, C487 volatile &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C487 &, C487 volatile, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C487 volatile &, C487, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C488 const volatile, C488 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C488 const &, C488, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C488 const &, C488 volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C489, C489 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C489 volatile, C489, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C489 volatile, C489 const volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C489 const volatile &, C489 volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C489 const volatile &, C489 volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C489 const volatile &, C489 const volatile &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C490 const, C490 volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C490 &, C490 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C490 const &, C490 const &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C490 const volatile &, C490 &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C490 const volatile &, C490 const &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C491, C491 volatile, ret const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C491, C491 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C491 &, C491, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C491 const &, C491 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C491 const volatile &, C491 const volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C492, C492 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C492 volatile, C492 const &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C492 const &, C492 const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C492 const volatile &, C492 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 volatile, C493 const volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 const volatile, C493, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 const volatile, C493 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 const volatile, C493 const &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 const volatile, C493 const volatile &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 &, C493, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 &, C493 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 const volatile &, C493 const, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 const volatile &, C493 const volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 const volatile &, C493 &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 const volatile &, C493 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C493 const volatile &, C493 const volatile &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C494, C494 volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C494 volatile, C494, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C494 volatile, C494, ret const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C494 const volatile, C494 const volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C494 const &, C494 const volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C494 volatile &, C494 volatile, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C495, C495, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C495, C495 const volatile &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C495 volatile, C495 const &, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C495 volatile, C495 volatile &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C495 &, C495 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C495 volatile &, C495, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C495 const volatile &, C495 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C496, C496 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C496, C496 volatile &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C496 const volatile, C496 &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C496 volatile &, C496 const volatile &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C497, C497 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C497 volatile, C497, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C497 volatile, C497 &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C497 volatile, C497 const volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C497 volatile &, C497, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C497 volatile &, C497 const volatile, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C498, C498 volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C498, C498 const &, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C498, C498 volatile &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C498, C498 volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C498 volatile, C498 volatile &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C498 const volatile &, C498 volatile &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C499, C499 volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C499, C499 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C499 volatile, C499 const volatile, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C499 &, C499 &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C500 const, C500 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C500 volatile, C500 const volatile, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C500 &, C500 volatile, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C500 const volatile &, C500 volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C501 const, C501, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C501 volatile, C501 const volatile &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C501 &, C501 const, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C502 const, C502, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C502 const, C502 &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C502 volatile, C502 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C502 const volatile, C502 volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C502 volatile &, C502 const volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C502 volatile &, C502 const volatile, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C503 const, C503 volatile, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C503 volatile &, C503 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C504, C504 const &, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C504 volatile, C504 const volatile, ret volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C504 &, C504 &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C504 const &, C504, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C505 volatile, C505 volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C506 volatile, C506 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C506 volatile &, C506 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C506 const volatile &, C506 const volatile &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C507, C507 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C507 volatile, C507 const &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C507 &, C507 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C507 volatile &, C507 const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C508 volatile, C508 volatile &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C508 const volatile, C508 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C508 volatile &, C508 volatile, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C508 const volatile &, C508 volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C509 const volatile, C509 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C509 const volatile, C509 const &, ret const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C510 const, C510 const &, ret const volatile & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C510 const, C510 const volatile &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C510 volatile, C510 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C510 const volatile, C510 volatile, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C510 &, C510 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C511 const volatile, C511 volatile, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C511 &, C511 const &, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C511 const &, C511 const volatile, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C511 const &, C511 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C512 volatile, C512 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C512 const volatile &, C512 &, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C512 const volatile &, C512 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C513, C513 volatile, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C513 volatile, C513, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C513 volatile, C513 const, ret const volatile >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C513 volatile &, C513 const volatile, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C514, C514 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C514 const, C514 volatile, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C514 volatile, C514 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C514 const volatile, C514 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C514 const volatile &, C514 const volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C514 const volatile &, C514 volatile &, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C515 const, C515 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C515 const volatile, C515 volatile, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C515 &, C515 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C515 &, C515 const volatile, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C515 const volatile &, C515, ret volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C516 const, C516 &, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C516 const, C516 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C516 const, C516 const &, ret volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C516 const, C516 const volatile &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C516 const volatile, C516 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C516 const volatile, C516 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C516 volatile &, C516 volatile, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C516 volatile &, C516 const volatile, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C517, C517 const volatile &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C517 const volatile, C517, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C517 &, C517, ret const volatile >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C517 &, C517 const, ret const volatile & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::can_call_addition< C517 const volatile &, C517 &, ret const & >::value), 0);
TT_TEST_END
