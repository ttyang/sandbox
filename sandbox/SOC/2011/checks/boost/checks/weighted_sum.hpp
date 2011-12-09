//  Boost checks/weighted_sum.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute weighted sum.
*/

#ifndef BOOST_CHECKS_WEIGHTED_SUM_HPP
#define BOOST_CHECKS_WEIGHTED_SUM_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/basic_check_algorithm.hpp>

namespace boost{
  namespace checks{

/*!
    \brief This class permits to add to the current checksum the weight multiplied by the current value.

    \tparam weight must meet the weight concept requirements.
    \tparam iteration_sense must meet the iteration_sense concept requirements.
    \tparam number_of_virtual_value_skipped Helper function to provide same behavior on sequence with and without checkdigits. No "real" value in the sequence will be skipped.
*/
template <typename weight, typename iteration_sense, unsigned int number_of_virtual_value_skipped = 0>
struct weighted_sum_algorithm : boost::checks::basic_check_algorithm< iteration_sense >
{
  /*!
    \brief Compute an operation on the checksum with the current valid value.

    \post The current weight multiplied by the current value is added to the checksum.

    \param current_valid_value is the current valid value analysed.
    \param valid_value_counter is the number of valid values already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).
    \param checksum is the current checksum.
  */
  static void operate_on_valid_value( const int current_valid_value, const unsigned int valid_value_counter, int &checksum )
  {
    int current_weight = weight::weight_associated_with_pos( valid_value_counter + number_of_virtual_value_skipped ) ;
    checksum += current_valid_value * current_weight ;
  }
};

}}// namespace boost   namespace checks

#endif //BOOST_CHECKS_MOD10_HPP
