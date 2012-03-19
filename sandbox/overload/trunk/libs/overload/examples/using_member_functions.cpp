/*=============================================================
    Boost Overload
    Example 4 - Using member functions
==============================================================*/

//[ using_member_functions_cpp
#include <string>
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>


/* a free function */
int foo(std::string )
{
   return 1;
}
typedef int signature1_t (std::string );

/* a member function */
class Alpha
{
  public:
    Alpha(int _offset) : offset(_offset) {}

    int code(char c)
    {
        if( c < 'a' || c > 'z' )
            return -1;
        return ( (c - 'a') + offset ) % 26;
    }

  private:
    int offset;
};
// member function explicit non-const signature
typedef int signature2_t (Alpha*, char );


int main()
{
    Alpha alpha(3);

    boost::overload<signature1_t, signature2_t> f;

    f.set(&foo);
    // we pass a pointer to the member fuction Alpha::code
    f.set(&Alpha::code);

    BOOST_ASSERT( f("hello") == 1 );
    // invokes alpha.code('x')
    BOOST_ASSERT( f(&alpha, 'x') == 0 );

    return boost::report_errors();
}
//]
