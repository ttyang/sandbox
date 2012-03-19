/*=============================================================
    Boost Overload
    Example 3 - Using Boost.Function
==============================================================*/

//[ using_boost_function_cpp
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
struct FuncObj
{
   int operator() (int, char ) const
   {
           return 2;
   }
};
typedef int signature2_t (int, char );


int main()
{
   // boost::function object that set foo as object target
   boost::function<signature1_t> foo_wrapper(&foo);

   // instance of FuncObj
   FuncObj func_obj;


   // overload object
   boost::overload<signature1_t, signature2_t> f;

   // a copy of the object target held by foo_wrapper
   // is created and tied to the first call signature
   f.set(foo_wrapper);

   // set a copy of func_obj as object target
   // for the second call signature
   f.set(func_obj);

   BOOST_ASSERT( f("hello") == 1 );
   BOOST_ASSERT( f(1, 'x') == 2 );

   return boost::report_errors();
}
//]
