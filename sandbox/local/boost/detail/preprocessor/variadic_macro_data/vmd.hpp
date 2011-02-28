
// The VMD library was written by Edward Diener and proposed for Boost addition.
// I have just added some boost-detail prefixed to the macro names.

#if !defined(VARIADIC_MACRO_DATA_HPP)
#define VARIADIC_MACRO_DATA_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_VARIADIC_MACROS)

#include <boost/preprocessor/array/data.hpp>
#include <boost/preprocessor/list/to_tuple.hpp>
#include <boost/preprocessor/seq/to_tuple.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include "detail/vmd_detail.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Expands to the number of comma-separated variadic macro data arguments.
/**

    ... = variadic macro data.

    returns = the number of comma-separated variadic macro data
              arguments being passed to it.
    
    The value returned can be between 1 and 64.
    
*/
#define BOODT_DETAIL_PP_VMD_DATA_SIZE(...) \
  BOOST_DETAIL_PP_VMD_DETAIL_DATA_SIZE(__VA_ARGS__) \
/**/

/// Expands to a particular variadic macro data argument.
/**

    n   = number of the variadic macro data argument.
          The number starts from 0 to the number of
          variadic macro data arguments - 1. The maximum
          number for n is 63.
          
    ... = variadic macro data.

    returns = the particular macro data argument as specified
              by n. The argument returned can be any valid
              preprocessing token.
              
*/
#define BOODT_DETAIL_PP_VMD_DATA_ELEM(n,...) \
  BOOST_DETAIL_PP_VMD_DETAIL_DATA_ELEM(n,__VA_ARGS__) \
/**/

/// Expand to a Boost PP tuple data type.
/**

    ... = variadic macro data.

    returns = a Boost PP library tuple data type.
    
    You can use the result of this macro whenever 
    you need to pass a Boost PP library tuple as 
    data to a Boost PP library macro.
    
*/
#define BOODT_DETAIL_PP_VMD_DATA_TO_PP_TUPLE(...) \
  BOOST_DETAIL_PP_VMD_DETAIL_DATA_TO_PP_TUPLE(__VA_ARGS__) \
/**/

/// Expand to a Boost PP array data type.
/**

    ... = variadic macro data.

    returns = a Boost PP library array data type.
    
    You can use the result of this macro whenever 
    you need to pass a Boost PP library array as 
    data to a Boost PP library macro.
    
*/
#define BOODT_DETAIL_PP_VMD_DATA_TO_PP_ARRAY(...) \
  BOOST_DETAIL_PP_VMD_DETAIL_DATA_TO_PP_ARRAY(__VA_ARGS__) \
/**/

/// Expand to a Boost PP list data type.
/**

    ... = variadic macro data.

    returns = a Boost PP library list data type.
    
    You can use the result of this macro whenever
    you need to pass a Boost PP library list as
    data to a Boost PP library macro.
    
*/
#define BOODT_DETAIL_PP_VMD_DATA_TO_PP_LIST(...) \
  BOOST_DETAIL_PP_VMD_DETAIL_DATA_TO_PP_LIST(__VA_ARGS__) \
/**/

/// Expand to a Boost PP sequence data type.
/**

    ... = variadic macro data.

    returns = a Boost PP library sequence data type.
    
    You can use the result of this macro whenever
    you need to pass a Boost PP library sequence as
    data to a Boost PP library macro.
    
*/
#define BOODT_DETAIL_PP_VMD_DATA_TO_PP_SEQ(...) \
  BOOST_DETAIL_PP_VMD_DETAIL_DATA_TO_PP_SEQ(__VA_ARGS__) \
/**/

/// Expands to the number of elements in a tuple.
/**

    tuple = a Boost PP library tuple data type.

    returns = the number of elements in the tuple,
              commonly referred to as the tuple size.
              
    In the Boost PP library there is no way to calculate
    the size of a tuple, so that the size must be known
    in order to be used by Boost PP library tuple macros.
    With variadic macros the size of a tuple can be
    calculated from the tuple itself.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_TUPLE_SIZE(tuple) \
  BOOST_DETAIL_PP_VMD_DETAIL_PP_TUPLE_SIZE(tuple) \
/**/

/// Expands to a particular tuple element.
/**

    n   = number of the tuple element.
          The number starts from 0 to the size of
          the tuple - 1.
          
    tuple = a Boost PP library tuple data type.

    returns = the particular tuple element as specified
              by n.
              
    In the Boost PP library there is no way to calculate 
    the size of a tuple, so that the size must be known 
    in order to be used by Boost PP library tuple macros.
    With variadic macros the size of a tuple can be 
    calculated from the tuple itself.
    
    Therefore this macro is a replacement for the BOOST_PP_TUPLE_ELEM
    macro without the necessity of having to pass a size.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_TUPLE_ELEM(n,tuple) \
  BOOST_DETAIL_PP_VMD_DETAIL_PP_TUPLE_ELEM(BOODT_DETAIL_PP_VMD_PP_TUPLE_SIZE(tuple),n,tuple) \
/**/

/// Expands to a series of tokens which are equivalent to removing the parentheses from a tuple.
/**

    tuple = a Boost PP library tuple data type.

    returns = a series of comma-separated tokens equivalent to removing the parentheses from a tuple.
    
              This result is actually equivalent to the form of variadic macro data
              and can be used as an alternative to BOODT_DETAIL_PP_VMD_PP_TUPLE_TO_DATA to convert
              the tuple to variadic macro data.
              
    In the Boost PP library there is no way to calculate 
    the size of a tuple, so that the size must be known 
    in order to be used by Boost PP library tuple macros.
    With variadic macros the size of a tuple can be 
    calculated from the tuple itself.
    
    Therefore this macro is a replacement for the BOOST_PP_TUPLE_REM_CTOR
    macro without the necessity of having to pass a size.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_TUPLE_REM_CTOR(tuple) \
  BOOST_DETAIL_PP_VMD_DETAIL_PP_TUPLE_REM_CTOR(BOODT_DETAIL_PP_VMD_PP_TUPLE_SIZE(tuple),tuple) \
/**/

/// Expands to a tuple whose elements are in reversed order.
/**

    tuple = a Boost PP library tuple data type.

    returns = a tuple whose elements are in reversed order
              from the original tuple.
              
    In the Boost PP library there is no way to calculate 
    the size of a tuple, so that the size must be known 
    in order to be used by Boost PP library tuple macros.
    With variadic macros the size of a tuple can be 
    calculated from the tuple itself.
    
    Therefore this macro is a replacement for the BOOST_PP_TUPLE_REVERSE
    macro without the necessity of having to pass a size.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_TUPLE_REVERSE(tuple) \
  BOOST_DETAIL_PP_VMD_DETAIL_PP_TUPLE_REVERSE(BOODT_DETAIL_PP_VMD_PP_TUPLE_SIZE(tuple),tuple) \
/**/

/// Expands to a list whose elements are the same as a tuple.
/**

    tuple = a Boost PP library tuple data type.

    returns = a list whose elements are the same as the tuple
              that is inputted.
              
    In the Boost PP library there is no way to calculate 
    the size of a tuple, so that the size must be known 
    in order to be used by Boost PP library tuple macros.
    With variadic macros the size of a tuple can be 
    calculated from the tuple itself.
    
    Therefore this macro is a replacement for the BOOST_PP_TUPLE_TO_LIST
    macro without the necessity of having to pass a size.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_TUPLE_TO_LIST(tuple) \
  BOOST_DETAIL_PP_VMD_DETAIL_PP_TUPLE_TO_LIST(BOODT_DETAIL_PP_VMD_PP_TUPLE_SIZE(tuple),tuple) \
/**/

/// Expands to a sequence whose elements are the same as a tuple.
/**

    tuple = a Boost PP library tuple data type.

    returns = a sequence whose elements are the same as the tuple
              that is inputted.
              
    In the Boost PP library there is no way to calculate 
    the size of a tuple, so that the size must be known 
    in order to be used by Boost PP library tuple macros.
    With variadic macros the size of a tuple can be 
    calculated from the tuple itself.
    
    Therefore this macro is a replacement for the BOOST_PP_TUPLE_TO_SEQ
    macro without the necessity of having to pass a size.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_TUPLE_TO_SEQ(tuple) \
  BOOST_DETAIL_PP_VMD_DETAIL_PP_TUPLE_TO_SEQ(BOODT_DETAIL_PP_VMD_PP_TUPLE_SIZE(tuple),tuple) \
/**/

/// Expands to variadic macro data whose arguments are the same as a tuple's elements.
/**

    tuple = a Boost PP library tuple data type.

    returns = variadic macro data whose arguments are the same as the
              elements of a tuple that is inputted.
              
    The variadic macro data that is returned is in the form of
    of comma separated arguments. The variadic macro data can be
    passed to any macro which takes variadic macro data in the form
    of a final variadic macro data '...' macro parameter.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_TUPLE_TO_DATA(tuple) \
  BOOST_DETAIL_PP_VMD_DETAIL_PP_TUPLE_TO_DATA(tuple) \
/**/

/// Expands to variadic macro data whose arguments are the same as an array's elements.
/**

    array = a Boost PP library array data type.

    returns = variadic macro data whose arguments are the same as the
              elements of an array that is inputted.
              
    The variadic macro data that is returned is in the form of
    of comma separated arguments. The variadic macro data can be
    passed to any macro which takes variadic macro data in the form
    of a final variadic macro data '...' macro parameter.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_ARRAY_TO_DATA(array) \
  BOODT_DETAIL_PP_VMD_PP_TUPLE_TO_DATA(BOOST_PP_ARRAY_DATA(array)) \
/**/

/// Expands to variadic macro data whose arguments are the same as a list's elements.
/**

    list = a Boost PP library list data type.

    returns = variadic macro data whose arguments are the same as the
              elements of a list that is inputted.
              
    The variadic macro data that is returned is in the form of
    of comma separated arguments. The variadic macro data can be
    passed to any macro which takes variadic macro data in the form
    of a final variadic macro data '...' macro parameter.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_LIST_TO_DATA(list) \
  BOODT_DETAIL_PP_VMD_PP_TUPLE_TO_DATA(BOOST_PP_LIST_TO_TUPLE(list)) \
/**/

/// Expands to variadic macro data whose arguments are the same as a sequence's elements.
/**

    seq = a Boost PP library sequence data type.

    returns = variadic macro data whose arguments are the same as the
              elements of a sequence that is inputted.
              
    The variadic macro data that is returned is in the form of
    of comma separated arguments. The variadic macro data can be
    passed to any macro which takes variadic macro data in the form
    of a final variadic macro data '...' macro parameter.
    
*/
#define BOODT_DETAIL_PP_VMD_PP_SEQ_TO_DATA(seq) \
  BOODT_DETAIL_PP_VMD_PP_TUPLE_TO_DATA(BOOST_PP_SEQ_TO_TUPLE(seq)) \
/**/

#endif // BOOST_NO_VARIADIC_MACROS
#endif // VARIADIC_MACRO_DATA_HPP
