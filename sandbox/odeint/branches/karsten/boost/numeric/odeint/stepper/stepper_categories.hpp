/*
   boost header: numeric/odeint/stepper_categories.hpp

   Copyright 2009 Karsten Ahnert
   Copyright 2009 Mario Mulansky

   Distributed under the Boost Software License, Version 1.0.
   (See accompanying file LICENSE_1_0.txt or
   copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_CATEGORIES_HPP_
#define BOOST_NUMERIC_ODEINT_STEPPER_CATEGORIES_HPP_

namespace boost {
namespace numeric {
namespace odeint {


/*
 * Tags to specify stepper types
 *
 * These tags are used by integrate() to choose which integration method is used
 */

struct stepper_tag {};
//struct explicit_stepper_tag : stepper_tag {};
//struct implicit_stepper_tag : stepper_tag {};


struct error_stepper_tag {};
struct explicit_error_stepper_tag : error_stepper_tag {};
struct explicit_error_stepper_fsal_tag : error_stepper_tag {};

struct controlled_stepper_tag {};

struct dense_output_stepper_tag {};



} // odeint
} // numeric
} // boost


#endif /* BOOST_NUMERIC_ODEINT_STEPPER_CATEGORIES_HPP_ */
