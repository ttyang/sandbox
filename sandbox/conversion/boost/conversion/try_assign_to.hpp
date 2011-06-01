//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/*!
 @file
 @brief
 Defines the free function @c try_assign_to.

The function @c try_assign_to assigns the @c from parameter to the @c to parameter. Return @c true if assignation done and @c false otherwise.
The default implementation applies the the assignment operator of the @c To class.
A user adapting another type could need to specialize the @c try_assign_to free function if the default behavior is not satisfactory ot if it can improve the performances

The user can add the @c try_assign_to overloading on the namespace of the Source or Target classes.
But sometimes as it is the case for the standard classes, we can not add new functions on the std namespace,
so we need a different technique.

The technique consists in partially specialize on the function @c try_assign_to on the @c boost::conversion namespace.
For compilers for which we can not partially specialize a function a trick is used:
instead of calling directly to the @c try_assign_to member function, @c try_assign_to calls to the static operation apply
on a class with the same name in the namespace @c overload_workaround.
Thus the user can specialize partially this class.

 */

#ifndef BOOST_CONVERSION_TRY_ASSIGN_TO_HPP
#define BOOST_CONVERSION_TRY_ASSIGN_TO_HPP

#include <cstddef> //for std::size_t
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {
  namespace conversion {
    //! This struct can be specialized by the user.
    template < typename To, typename From >
    struct try_assigner
    {
      //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
      //! @NoThrow
      //! @Returns the converted value if success or the fallback when conversion fails.
      bool operator()(To& to, const From& from)
      {
        To rollback = to;
        try
        {
          boost::conversion::assign_to<To>(to , from);
          return true;
        }
        catch (...)
        {
          to = rollback;
          return false;
        }
      }
    };
    template < typename To, typename From, std::size_t N  >
    struct try_assigner<To[N],From[N]>
    {
      //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator on each vector element.
      //! @NoThrow
      //! @Returns the converted value if success or the fallback when conversion fails.
      bool operator()(To(&to)[N], const From(& from)[N])
      {
        To rollback[N];
        boost::conversion::assign_to<To>(rollback, to);
        try
        {
          for (std::size_t i = 0; i < N; ++i)
          {
            boost::conversion::assign_to<To>(to[i] , from[i]);
          }
          return true;
        }
        catch (...)
        {
          boost::conversion::assign_to<To>(to, rollback);
          return false;
        }
      }
    };

  }

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  namespace conversion_impl_2 {
    //! @brief Default @c try_assign_to overload, used when ADL fails.
    //!
    //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
    //! @NoThrow
    //! @Returns the converted value if success or the fallback when conversion fails.
    //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
    template < typename To, typename From >
    bool try_assign_to(To& to, const From& from)
    {
      return conversion::try_assigner<To,From>()(to, from);
    }
  }

  namespace conversion_impl {
    template <typename Target, typename Source>
    bool try_assign_to_impl(Target& to, const Source& from)
    {
      using namespace boost::conversion_impl_2;
      //use boost::conversion::try_assign_to if ADL fails
      return try_assign_to(to, from);
    }
  }
#endif
  namespace conversion {

  //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
  //! @NoThrow
  //! @Returns the converted value if success or the fallback when conversion fails.
  //!
  //! This function can be partially specialized on compilers supporting it.
  template <typename Target, typename Source>
  bool try_assign_to(Target& to, const Source& from)
  {
    return conversion_impl::try_assign_to_impl<Target, Source>(to, from);
  }
}
}

#endif

