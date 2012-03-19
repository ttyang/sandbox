
#ifndef _TEST_METAFUNCTIONS_HPP_
#define _TEST_METAFUNCTIONS_HPP_


namespace metafunction_test_ns {

using namespace boost::overloads;


int foo(long ) { return 1; }
typedef int (*foo_ptr)(long );

struct bar
{
    int operator()(double ) { return -1; }
};


typedef boost::overload<int (int ), int (char ), int (double )>
        overload_type;


BOOST_STATIC_ASSERT(( extent<overload_type>::value == 3 ));

BOOST_STATIC_ASSERT((
        is_same<
            signature<overload_type, 0>::type,
            int (int )
        >::value
));
BOOST_STATIC_ASSERT((
        is_same<
            signature<overload_type, 1>::type,
            int (char )
        >::value
));
BOOST_STATIC_ASSERT((
        is_same<
            signature<overload_type, 2>::type,
            int (double )
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            function<overload_type, 0>::type,
            boost::function<int (int )>
        >::value
));
BOOST_STATIC_ASSERT((
        is_same<
            function<overload_type, 1>::type,
            boost::function<int (char )>
        >::value
));
BOOST_STATIC_ASSERT((
        is_same<
            function<overload_type, 2>::type,
            boost::function<int (double )>
        >::value
));

BOOST_STATIC_ASSERT(( boost::overloads::index_of_signature<overload_type, int (int )>::value == 0 ));
BOOST_STATIC_ASSERT(( boost::overloads::index_of_signature<overload_type, int (char )>::value == 1 ));
BOOST_STATIC_ASSERT(( boost::overloads::index_of_signature<overload_type, int (double )>::value == 2 ));
BOOST_STATIC_ASSERT(( boost::overloads::index_of_signature<overload_type, int (float )>::value == -1 ));

BOOST_STATIC_ASSERT(( has_signature<overload_type, int (int )>::value ));
BOOST_STATIC_ASSERT(( has_signature<overload_type, int (char )>::value ));
BOOST_STATIC_ASSERT(( has_signature<overload_type, int (double )>::value ));
BOOST_STATIC_ASSERT(( !has_signature<overload_type, int (long )>::value ));

BOOST_STATIC_ASSERT(( have_any_shared_signature<overload_type, bar>::value ));
BOOST_STATIC_ASSERT(( !have_any_shared_signature<overload_type, foo_ptr>::value ));




typedef boost::function<int(double)> function_type;


BOOST_STATIC_ASSERT(( extent<function_type>::value == 1 ));

BOOST_STATIC_ASSERT((
        is_same<
            signature<function_type>::type,
            int (double )
        >::value
));

BOOST_STATIC_ASSERT((
        is_same<
            function<function_type>::type,
            boost::function<int (double )>
        >::value
));

BOOST_STATIC_ASSERT(( boost::overloads::index_of_signature<function_type, int (double )>::value == 0 ));
BOOST_STATIC_ASSERT(( boost::overloads::index_of_signature<function_type, int (char )>::value == -1 ));

BOOST_STATIC_ASSERT(( has_signature<function_type, int (double )>::value ));
BOOST_STATIC_ASSERT(( !has_signature<function_type, int (char )>::value ));

BOOST_STATIC_ASSERT(( have_any_shared_signature<function_type, bar>::value ));
BOOST_STATIC_ASSERT(( !have_any_shared_signature<function_type, foo_ptr>::value ));

} // end namespace metafunction_test_ns

#endif /* _TEST_METAFUNCTIONS_HPP_ */
