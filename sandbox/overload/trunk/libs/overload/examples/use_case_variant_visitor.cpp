/*==============================================================
    Boost Overload
    Use case - Variant visitor
==============================================================*/

//[ use_case_variant_visitor_cpp
#include <boost/variant.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/overload.hpp>


template<typename Overload, typename R = ::boost::detail::static_visitor_default_return>
struct overloaded_visitor : public Overload
{
    typedef R result_type;
};



int apply_to_int(int )
{
    return 1;
}

int apply_to_string(const std::string &  )
{
    return 2;
}


typedef boost::overload<int (int ), int(const std::string & )> overload_type;

typedef overloaded_visitor<overload_type, int> visitor_type;


int main()
{

    boost::variant< int, std::string > u("hello world");

    visitor_type my_visitor;
    my_visitor.set( &apply_to_int, &apply_to_string );

    int result = boost::apply_visitor( my_visitor, u );
    BOOST_ASSERT( result == 2 );

    return boost::report_errors();
}
//]
