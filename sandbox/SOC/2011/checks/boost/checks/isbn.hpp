//  Boost checks/isbn.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate an International Standard Book Number (ISBN) of size 10 or 13.

    \remarks The ISBN-13 is derived from the EAN number, so EAN macro or type are used.
*/

#ifndef BOOST_CHECKS_ISBN_HPP
#define BOOST_CHECKS_ISBN_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/ean.hpp>
#include <boost/checks/modulus11.hpp>
#include <boost/checks/checkdigit.hpp>
#include <boost/checks/checksum.hpp> 

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

/*!
  \brief This macro defines the size of an ISBN-10.
*/
#define ISBN10_SIZE 10

namespace boost {
    namespace checks{

typedef ean13 isbn13;

/*!
    \brief Validate a sequence according to the isbn13_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly EAN13_SIZE digits.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename range>
bool check_isbn13 (const range& x)
{
  return check_sequence<isbn13>(x);
}

bool check_isbn13 (const std::string& x)
{
  return check_sequence<isbn13>(make_precheck<digit>(x));
}

/*!
    \brief Calculate the check digit of a sequence according to the isbn13_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly EAN13_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename range>
size_t compute_isbn13 (const range& x)
{
  return compute_checkdigit<isbn13>(x);
}

size_t compute_isbn13 (const std::string& x)
{
  return compute_checkdigit<isbn13>(make_precheck<digit>(x));
}

typedef features
<
  mod11,
  ISBN10_SIZE
> isbn10;

/*!
    \brief Validate a sequence according to the mod11_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly ISBN10_SIZE digits.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename range>
bool check_isbn10(const range& x)
{
  return check_sequence<isbn10>(x);
}

bool check_isbn10(const std::string& x)
{
  return check_sequence<isbn10>(make_precheck<digitx>(x));
}


/*!
    \brief Calculate the check digit of a sequence according to the mod11_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly ISBN10_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9,X].
*/
template <typename range>
size_t compute_isbn10(const range& x)
{
  return compute_checkdigit<isbn10>(x);
}

size_t compute_isbn10(const std::string& x)
{
  return compute_checkdigit<isbn10>(make_precheck<digitx>(x));
}

}} // namespace boost   namespace checks
#endif // BOOST_CHECKS_ISBN_HPP
