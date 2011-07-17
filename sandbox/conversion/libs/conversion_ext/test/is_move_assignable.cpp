//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/conversion/type_traits/is_move_assignable.hpp>



class Empty
{
};

class NotEmpty
{
public:
    virtual ~NotEmpty();
};

union Union {};

struct bit_zero
{
    int :  0;
};

struct A
{
    A();
};

#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)

namespace boost {
  // these specialization are needed because the compiler doesn't support SFINAE on expression
  template <> struct is_assignable< Empty&, Empty const& > : true_type  {};
  template <> struct is_assignable< NotEmpty&, NotEmpty const& > : true_type  {};
  template <> struct is_assignable< Union&, Union const& > : true_type  {};
  template <> struct is_assignable< bit_zero&, bit_zero const& > : true_type  {};
  template <> struct is_assignable< A&, A const& > : true_type  {};
}

#endif

int main()
{
  BOOST_STATIC_ASSERT(( boost::is_move_assignable<int>::value));
  BOOST_STATIC_ASSERT((!boost::is_move_assignable<const int>::value));
  BOOST_STATIC_ASSERT((!boost::is_move_assignable<int[]>::value));
  BOOST_STATIC_ASSERT((!boost::is_move_assignable<int[3]>::value));
  BOOST_STATIC_ASSERT(( boost::is_move_assignable<int&>::value));
  BOOST_STATIC_ASSERT(( boost::is_move_assignable<A>::value));
  BOOST_STATIC_ASSERT(( boost::is_move_assignable<bit_zero>::value));
  BOOST_STATIC_ASSERT(( boost::is_move_assignable<Union>::value));
  BOOST_STATIC_ASSERT(( boost::is_move_assignable<NotEmpty>::value));
  BOOST_STATIC_ASSERT(( boost::is_move_assignable<Empty>::value));
}





