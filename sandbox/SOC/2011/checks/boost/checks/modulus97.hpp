//  Boost checks/modulus97.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file modulus97.hpp
    \brief This file provides tools to compute and validate classic modulus 97 checksum. It provides function for convenience with the mod97-10 algorithm (ISO/IEC 7064:2003).
*/

#ifndef BOOST_CHECKS_MOD97_HPP
#define BOOST_CHECKS_MOD97_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/preprocessor/repetition.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/checks/translation_exception.hpp>
#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/weighted_sum.hpp>

namespace boost{
  namespace checks{

/*! \class modulus97_algorithm
    \brief This class can be used to compute or validate checksum with a basic modulus 97.

    \tparam mod97_weight must meet the weight concept requirements.
    \tparam iteration_sense must meet the iteration_sense concept requirements.
    \tparam number_of_virtual_value_skipped Help functions to provide same behavior on sequence with and without check digits. No "real" value in the sequence will be skipped.

    \remarks This algorithm use two check digits.
*/
template <typename mod97_weight, typename iteration_sense, unsigned int number_of_virtual_value_skipped = 0>
struct modulus97_algorithm : boost::checks::weighted_sum_algorithm<mod97_weight, iteration_sense, number_of_virtual_value_skipped>
{
  /*!
    \brief Validate a checksum with a simple modulus 97.

    \param checksum is the checksum to validate.

    \returns true if the checksum is correct, false otherwise.
  */
  static bool validate_checksum(int checksum)
  {
    return checksum % 97 == 1 ;
  }

  /*!
    \brief Compute the two check digits with a simple modulus 97.

    \pre checkdigits should have enough reserved place to store the two check digits.
    \post The two check digits are stored into checkdigits.

    \tparam checkdigits_iter must meet the OutputIterator requirements.
    \param checksum is the checksum used to extract the check digit.
    \param checkdigits is the output iterator in which the two check digits will be written.
    
    \throws boost::checks::translation_exception if the check digits cannot be translated into the check digits_iter type.
    
    \returns An iterator initialized at one pass the end of the two check digits.
  */
  template <typename checkdigits_iter>
  static typename checkdigits_iter compute_multicheckdigit( int checksum, checkdigits_iter checkdigits )
  {
    unsigned int mod97_checkdigits = 98 - (checksum % 97) ;

    try{
      *checkdigits = boost::lexical_cast<checkdigits_iter::value_type>(mod97_checkdigits / 10) ; 
      ++checkdigits;
      *checkdigits = boost::lexical_cast<checkdigits_iter::value_type>(mod97_checkdigits % 10) ; 
      ++checkdigits;
    }
    catch( boost::bad_lexical_cast ){
      throw boost::checks::translation_exception() ;
    }
    return checkdigits;
  }
};

/*! \class make_mod97_weight
    \brief This class is used to pre-computed the weight of the mod97-10 algorithm (a = 1; a = a * 10 % 97 ;).

    \tparam weight_value is the weight value stored by make_mod97_weight.

    \remarks The last value is 68, so we specialize make_mod97_weight to terminate the template recursion.
*/
template <unsigned int weight_value>
struct make_mod97_weight
{
  static const unsigned int value = weight_value ;
  typedef make_mod97_weight<weight_value * 10 % 97> next ;
};
template<>
struct make_mod97_weight<68>
{
  static const unsigned int value = 68 ;
  typedef make_mod97_weight type ;
};

/*!
  \brief This is the initial weight for the mod97-10 weights serie.
*/
typedef make_mod97_weight<1> initial_mod97_weight ;


/*!
  \brief This macro is used to access the next type.
*/
#define NEXT(z,n,unused) next::

/*!
  \brief This macro is used to access to n-th value of initial_mod97_weight. (By using make_mod97_weight).
*/
#define MOD97_weight_maker(z, n ,unused) initial_mod97_weight::BOOST_PP_REPEAT(n, NEXT, ~)value

/*!
  \brief This is weight of the mod97-10 algorithm.
*/
typedef boost::checks::weight< BOOST_PP_ENUM(96, MOD97_weight_maker, ~) > mod97_10_weight ;

/*!
  \brief The iteration sense of the sequence. From right to left.
*/
typedef boost::checks::rightmost mod97_10_sense ;

/*!
  \brief This is the type of the modulus 97-10 algorithm for validating a check digit.
*/
typedef modulus97_algorithm< mod97_10_weight, mod97_10_sense, 0 > mod97_10_check_algorithm ;
/*!
  \brief This is the type of the modulus 97-10 algorithm for computing a check digit.
*/
typedef modulus97_algorithm< mod97_10_weight, mod97_10_sense, 2 > mod97_10_compute_algorithm ;

/*! 
    \brief Validate a sequence according to the mod97_10_check_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).

    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns True if the two check digits are correct, false otherwise.
*/
template <size_t size_expected, typename check_range>
bool check_mod97_10 (const check_range& check_seq)
{
  return boost::checks::check_sequence<mod97_10_check_algorithm, size_expected> ( check_seq ) ;
}

/*! 
    \brief Validate a sequence according to the mod97_10_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns True if the two check digits are correct, false otherwise.
*/
template <typename check_range>
bool check_mod97_10 (const check_range& check_seq)
{
  return boost::checks::check_sequence<mod97_10_check_algorithm> ( check_seq ) ;
}

/*! 
    \brief Calculate the check digits of a sequence according to the mod97_10_compute_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).\n mod97_checkdigits should have enough reserved place to store the two check digits.
    
    \tparam size_expected is the number of valid value expected in the sequence. (So the check digits are not included.)
    \tparam check_range is a valid range type.
    \tparam checkdigits_iter must meet the OutputIterator requirements.
    \param check_seq is the sequence of value to check.
    \param mod97_checkdigits is the OutputIterator in which the two check digits will be stored.
    
    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.
    \throws boost::checks::translation_exception if the check digits cannot be translated into the checkdigits_iter type.

    \returns The check digits are stored into mod97_checkdigits. The range of these is [0..9][0..9].
*/
template <size_t size_expected, typename check_range, typename checkdigits_iter>
typename checkdigits_iter compute_mod97_10 (const check_range& check_seq, checkdigits_iter mod97_checkdigits)
{
  return boost::checks::compute_multicheckdigit<mod97_10_compute_algorithm, size_expected> ( check_seq, mod97_checkdigits ) ;
}

/*! 
    \brief Calculate the check digits of a sequence according to the mod97_10_compute_algorithm type.

    \pre check_seq is a valid range.\n mod97_checkdigits should have enough reserved place to store the two check digits.
    
    \tparam check_range is a valid range type.
    \tparam checkdigits_iter must meet the OutputIterator requirements.
    \param check_seq is the sequence of value to check.
    \param mod97_checkdigits is the OutputIterator in which the two check digits will be stored.
    
    \throws std::invalid_argument if check_seq contains no valid value.
    \throws boost::checks::translation_exception if the check digits cannot be translated into the checkdigits_iter type.

    \returns The check digits are stored into mod97_checkdigits. The range of these is [0..9][0..9].
*/
template <typename check_range, typename checkdigits_iter>
typename checkdigits_iter compute_mod97_10 (const check_range& check_seq, checkdigits_iter mod97_checkdigits)
{
  return boost::checks::compute_multicheckdigit<mod97_10_compute_algorithm> ( check_seq, mod97_checkdigits ) ;
}


}}
#endif //BOOST_CHECKS_MOD97_HPP