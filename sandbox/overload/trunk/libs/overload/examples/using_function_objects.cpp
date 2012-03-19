/*=============================================================
    Boost Overload    
    Example 2 - Using function objects
==============================================================*/

//[ using_function_objects_cpp
#include <string>
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>


/* a free function */
int foo(std::string )
{
   return 1;
}
typedef int signature1_t (std::string );

/* a function object type */
struct FuncObj1
{
   int operator() (int, char ) const
   {
           return 2;
   }
};
typedef int signature2_t (int, char );

/* a statefull function object type */
struct FuncObj2
{
   FuncObj2() : calls(0) {}

   int operator() (char )
   {
       ++calls;
       return 3;
   }
  unsigned int calls;
};
typedef int signature3_t (char );


int main()
{
   // an overload object that supports
   // all the above call signatures
   boost::overload<signature1_t, signature2_t, signature3_t> f;

   // set a pointer to foo as target object tied to
   // the first call signature
   f.set(&foo);

   FuncObj1 func_obj_1;
   // func_obj_1 is cloned to an internal function
   // object tied to the matching call signature
   f.set(func_obj_1);

   // if cloning is too expensive (e.g. your function object is
   // statefull) or semantically incorrect you can wrap
   // a function object with boost::ref
   FuncObj2 func_obj_2;
   f.set(boost::ref(func_obj_2));
   // no copy occurs, only a reference to func_obj_2 is kept.

   BOOST_ASSERT( f("hello") == 1 );
   BOOST_ASSERT( f(1, 'x') == 2 );
   BOOST_ASSERT( f('x') == 3 );
   // we keep only a reference
   BOOST_ASSERT( func_obj_2.calls == 1 );

   return boost::report_errors();
}
//]
