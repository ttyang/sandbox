/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/no_return_dets.hpp>

// ToDo: Add tests for incorrect input

/////////////////////////
// Prepare Test Inputs //
/////////////////////////
#define CONSTRUCTOR_DECL                                                       \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS( ( this(x) )( (int) a ) )

#define EXPLICIT_CONSTRUCTOR_DECL                                              \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS( explicit ( this(x) )( (int) a ) )

#define DESTRUCTOR_DECL                                                        \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS( ( this(x) destroy )() )

#define CONVERSION_DECL                                                        \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS( ( operator X )( (T const&) a ) )

#define EXPLICIT_CONVERSION_DECL                                               \
BOOST_GENERIC_DETAIL_NO_RETURN_DETS( explicit ( operator X )( (T const&) a ) )

//////////// CONSTRUCTOR_DECL
#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_VALID( CONSTRUCTOR_DECL )
#error Constructor declaration not considered valid.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_PARTIAL( CONSTRUCTOR_DECL )
#error Constructor declaration not considered partial.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_EXPLICIT( CONSTRUCTOR_DECL )
#error Constructor declaration considered explicit.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONSTRUCTOR( CONSTRUCTOR_DECL )
#error Constructor declaration not considered a constructor.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_DESTRUCTOR( CONSTRUCTOR_DECL )
#error Constructor declaration considered a destructor.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONVERSION( CONSTRUCTOR_DECL )
#error Constructor declaration considered a conversion.
#endif

//////////// EXPLICIT_CONSTRUCTOR_DECL
#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_VALID( EXPLICIT_CONSTRUCTOR_DECL )
#error Explicit constructor declaration not considered valid.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_PARTIAL( EXPLICIT_CONSTRUCTOR_DECL )
#error Explicit constructor declaration not considered partial.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_EXPLICIT( EXPLICIT_CONSTRUCTOR_DECL )
#error Explicit constructor declaration not considered explicit.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONSTRUCTOR( EXPLICIT_CONSTRUCTOR_DECL )
#error Explicit constructor declaration not considered a constructor.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_DESTRUCTOR( EXPLICIT_CONSTRUCTOR_DECL )
#error Explicit constructor declaration considered a destructor.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONVERSION( EXPLICIT_CONSTRUCTOR_DECL )
#error Explicit constructor declaration considered a conversion.
#endif

//////////// DESTRUCTOR_DECL
#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_VALID( DESTRUCTOR_DECL )
#error Destructor declaration not considered valid.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_PARTIAL( DESTRUCTOR_DECL )
#error Destructor declaration not considered partial.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_EXPLICIT( DESTRUCTOR_DECL )
#error Destructor declaration considered explicit.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONSTRUCTOR( DESTRUCTOR_DECL )
#error Destructor declaration considered a constructor.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_DESTRUCTOR( DESTRUCTOR_DECL )
#error Destructor declaration not considered a destructor.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONVERSION( DESTRUCTOR_DECL )
#error Destructor declaration considered a conversion.
#endif

//////////// CONVERSION_DECL
#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_VALID( CONVERSION_DECL )
#error Conversion declaration not considered valid.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_PARTIAL( CONVERSION_DECL )
#error Conversion declaration not considered partial.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_EXPLICIT( CONVERSION_DECL )
#error Conversion declaration considered explicit.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONSTRUCTOR( CONVERSION_DECL )
#error Conversion declaration considered a constructor.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_DESTRUCTOR( CONVERSION_DECL )
#error Conversion declaration considered a destructor.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONVERSION( CONVERSION_DECL )
#error Conversion declaration not considered a conversion.
#endif

//////////// EXPLICIT_CONVERSION_DECL
#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_VALID( EXPLICIT_CONVERSION_DECL )
#error Explicit conversion declaration not considered valid.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_PARTIAL( EXPLICIT_CONVERSION_DECL )
#error Explicit conversion declaration not considered partial.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_EXPLICIT( EXPLICIT_CONVERSION_DECL )
#error Explicit conversion declaration not considered explicit.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONSTRUCTOR( EXPLICIT_CONVERSION_DECL )
#error Explicit conversion declaration considered a constructor.
#endif

#if BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_DESTRUCTOR( EXPLICIT_CONVERSION_DECL )
#error Explicit conversion declaration considered a destructor.
#endif

#if !BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONVERSION( EXPLICIT_CONVERSION_DECL )
#error Explicit conversion declaration not considered a conversion.
#endif
