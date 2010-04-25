//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2004-2007. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/container/detail/config_begin.hpp>
#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>
#include <functional>

#include <boost/container/vector.hpp>
#include "check_equal_containers.hpp"
#include "movable_int.hpp"
#include "expand_bwd_test_allocator.hpp"
#include "expand_bwd_test_template.hpp"
#include "dummy_test_allocator.hpp"
#include "vector_test.hpp"

using namespace boost::container;

//Explicit instantiation to detect compilation errors
template class boost::container::vector<test::movable_and_copyable_int, 
   test::dummy_test_allocator<test::movable_and_copyable_int> >;

int test_expand_bwd()
{
   //Now test all back insertion possibilities

   //First raw ints
   typedef test::expand_bwd_test_allocator<int>
      int_allocator_type;
   typedef vector<int, int_allocator_type>
      int_vector;

   if(!test::test_all_expand_bwd<int_vector>())
      return 1;

   //Now user defined wrapped int
   typedef test::expand_bwd_test_allocator<test::int_holder>
      int_holder_allocator_type;
   typedef vector<test::int_holder, int_holder_allocator_type>
      int_holder_vector;

   if(!test::test_all_expand_bwd<int_holder_vector>())
      return 1;

   //Now user defined bigger wrapped int
   typedef test::expand_bwd_test_allocator<test::triple_int_holder>
      triple_int_holder_allocator_type;

   typedef vector<test::triple_int_holder, triple_int_holder_allocator_type>
      triple_int_holder_vector;

   if(!test::test_all_expand_bwd<triple_int_holder_vector>())
      return 1;

   return 0;
}

class recursive_vector
{
   public:
   int id_;
   vector<recursive_vector> vector_;
};

void recursive_vector_test()//Test for recursive types
{
   vector<recursive_vector> recursive_vector_vector;
}

enum Test
{
   zero, one, two, three, four, five, six
};


int main()
{
   recursive_vector_test();
   {
      //Now test move semantics
      vector<recursive_vector> original;
      vector<recursive_vector> move_ctor(boost::move(original));
      vector<recursive_vector> move_assign;
      move_assign = boost::move(move_ctor);
      move_assign.swap(original);
   }
   typedef vector<int> MyVector;
   typedef vector<test::movable_int> MyMoveVector;
   typedef vector<test::movable_and_copyable_int> MyCopyMoveVector;
   typedef vector<test::copyable_int> MyCopyVector;
   typedef vector<Test> MyEnumVector;


   if(test::vector_test<MyVector>())
      return 1;
   if(test::vector_test<MyMoveVector>())
      return 1;
   if(test::vector_test<MyCopyMoveVector>())
      return 1;
   if(test::vector_test<MyCopyVector>())
      return 1;
   if(test_expand_bwd())
      return 1;

   MyEnumVector v;
   Test t;
   v.push_back(t);
   v.push_back(::boost::move(t));
   v.push_back(Test());

   const test::EmplaceOptions Options = (test::EmplaceOptions)(test::EMPLACE_BACK | test::EMPLACE_BEFORE);
   if(!boost::container::test::test_emplace
      < vector<test::EmplaceInt>, Options>())
      return 1;

   return 0;
}
#include <boost/container/detail/config_end.hpp>
/*

#include <iostream>
#include <boost/type_traits/is_fundamental.hpp>

enum Test {a, b, c};

template <class _TypeT>
struct __rw_is_enum
{
struct _C_no { };
struct _C_yes { int _C_dummy [2]; };

struct _C_indirect {
// prevent classes with user-defined conversions from matching

// use double to prevent float->int gcc conversion warnings
_C_indirect (double);
};

// nested struct gets rid of bogus gcc errors
struct _C_nest {
// supply first argument to prevent HP aCC warnings
static _C_no _C_is (int, ...);
static _C_yes _C_is (int, _C_indirect);

static _TypeT _C_make_T ();
};

enum {
_C_val = sizeof (_C_yes)
== sizeof (_C_nest::_C_is (0, _C_nest::_C_make_T ()))
&& !::boost::is_fundamental<_TypeT>::value
};

}; 

int main()

{
   std::cout << __rw_is_enum<Test>::_C_val << std::endl;
   return 0;
}



*/