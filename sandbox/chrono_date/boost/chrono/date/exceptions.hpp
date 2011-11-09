//  exceptions.hpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_EXCEPTIONS_HPP
#define BOOST_CHRONO_DATE_DATE_EXCEPTIONS_HPP


#include <exception>
#include <stdexcept>


namespace boost
{
  namespace chrono
  {


    /**
     * The class @c bad_date is thrown when an exceptional condition is created
     * within the chrono library.
     */
    class bad_date: public std::runtime_error
    {
    public:
      /*
       * @Effects: Constructs an object of class @c bad_date.
       * @Postcondition: <c>what() == s</c>.
       */
      explicit bad_date(const std::string& s) :
      std::runtime_error(s)
      {
      }

      /**
       * @Effects: Constructs an object of class @c bad_date.
       * @Postcondition: <c>strcmp(what(), s) == 0</c>.
       */
      explicit bad_date(const char* s) :
      std::runtime_error(s)
      {
      }
    };



  } // chrono

} // boost

#endif  // header
