//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/*!
 \file
 \brief
 Include this file when using conversions between @c boost::optional<> of convertible types.
 */

//[OPTIONAL_HPP
#ifndef BOOST_CONVERSION_OPTIONAL_HPP
#define BOOST_CONVERSION_OPTIONAL_HPP

#include <boost/optional.hpp>
#include <boost/none.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  namespace conversion {
    namespace detail {
      template <typename T>
      struct is_optional : mpl::false_ {};
      template <typename T>
      struct is_optional< ::boost::optional<T> > : mpl::true_ {};

    }
  }
#endif

  namespace conversion { 
    namespace overload_workaround {
      /**
       * Partial specialization of @c convert_to for boost::optional
       */
      template < class Target, class Source>
      struct convert_to< optional<Target>, optional<Source> >
      {
        //! @Returns If the optional source is initialized @c boost::optional<Target> initialized to the conversion of the optional value.
        //! Uninitialized  @c boost::optional<Target otherwise.
        inline static optional<Target> apply(optional<Source> const & from)
        {
          return (from?optional<Target>(boost::conversion::convert_to<Target>(from.get())):optional<Target>());
        }
      };
      
      template < class Target, class Source>
      struct convert_to< optional<Target>, Source > 
      {
        inline static optional<Target> apply(Source const & from)
        {
          try
          {
            return optional<Target>(boost::conversion::convert_to<Target>(from));
          } 
          catch (...) 
          {
            return optional<Target>();
          }
        }
      };

    }
  }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  //! @brief @c assign_to overloading for source and target been @c boost::optional.
  //!
  //! @Effects As if <c>to = boost::conversion::convert_to<optional<Target> >(from)</c>.
  //! @Returns The @c to parameter reference.
  template < class Target, class Source>
  inline optional<Target>& assign_to(optional<Target>& to, const optional<Source>& from
  )
  {
    to = boost::conversion::convert_to<optional<Target> >(from);
    return to;
  }
#endif

}

#endif

//]
