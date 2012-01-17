
#include <boost/preprocessor.hpp>

#define SCOPE_EXIT_THIS(unused) (~)

#define IS_THIS_(tokens) \
    BOOST_PP_IS_UNARY( tokens (~) )

IS_THIS_( & ) // 0
IS_THIS_( = ) // 0
IS_THIS_( &r ) // 0
IS_THIS_( v ) // 0
IS_THIS_( SCOPE_EXIT_THIS ) // 1

