//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/enums for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_ENUMS_UNDERLYING_TYPE_HPP
#define BOOST_ENUMS_UNDERLYING_TYPE_HPP

#include <boost/enums/config.hpp>
#ifndef BOOST_NO_UNDERLYING_TYPE
  #include <type_traits>
#endif

namespace boost
{
  namespace enums
  {
    //! underlying type metafunction
	  
	//! \c EC must be an enum type or the emulation of a scoped enum.\n\n

	//! The member typedef \c type name the underlying type of \c T. 
	//! When scoped enums are emulated it is defined as \c typename \c EC::underlying_type. 
	//! Otherwise is defined as \c std::underlying_type<EC>::type.
    //! This meta-function must be specialized for the compilers providing scoped enums
    //! but don't providing the \c std::underlying_type meta-function.
    template <typename EC>
    struct underlying_type
    {
#ifdef BOOST_ENUMS_DOXYGEN_INVOKED
		typedef <see below> type;
#else
      #ifdef BOOST_NO_SCOPED_ENUMS
        typedef typename EC::underlying_type type;
      #else
        #ifndef BOOST_NO_UNDERLYING_TYPE
          typedef std::underlying_type<EC>::type type;
        #endif
      #endif
#endif
    };
  }
}

#endif
