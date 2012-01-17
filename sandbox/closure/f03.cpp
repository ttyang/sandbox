
#include <boost/functional/overload.hpp>
#include <boost/function.hpp>
#include <boost/function_types/is_function.hpp>
#include <boost/function_types/is_function_pointer.hpp>
#include <boost/function_types/is_function_reference.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <iostream>
#include <string>
#include <typeinfo>

namespace boost { namespace functional {

namespace detail {

template<typename F, int Arity = -1>
struct functor_type {
    typedef typename functor_type<F, F::arity>::type type;
};

template<typename F>
struct functor_type<F, 0> {
    typedef typename F::result_type (type)(
    );
};

template<typename F>
struct functor_type<F, 1> {
    typedef typename F::result_type (type)(
          typename F::arg1_type
    );
};

template<typename F>
struct functor_type<F, 2> {
    typedef typename F::result_type (type)(
          typename F::arg1_type
        , typename F::arg2_type
    );
};

} // namespace detail

template<typename F>
struct function_type {
    typedef
        typename boost::mpl::if_<boost::function_types::is_function<F>,
            boost::mpl::identity<F>
        ,
            typename boost::mpl::if_<boost::function_types::
                    is_function_pointer<F>,
                boost::remove_pointer<F>
            ,
                typename boost::mpl::if_<boost::function_types::
                        is_function_reference<F>,
                    boost::remove_reference<F>
                ,
                    detail::functor_type<F>
                >::type
            >::type
        >::type
    ::type type;
};

template<typename F0, typename F1, typename F2>
boost::functional::overload<
      typename function_type<F0>::type
    , typename function_type<F1>::type
    , typename function_type<F2>::type
>
make_overload(F0 f0, F1 f1, F2 f2) {
    return boost::functional::overload<
          typename function_type<F0>::type
        , typename function_type<F1>::type
        , typename function_type<F2>::type
    >(f0, f1, f2);
}

} } // namespace

void print_s(const std::string& s) { std::cout << s << std::endl; }
void print_i(int i) { std::cout << i << std::endl; }
void print_d(double d) { std::cout << d << std::endl; }

int main(void) {
    boost::function<void (double)> pd = print_d;
    print_s("abc");
    print_i(123);
    pd(1.23);
    std::cout << std::endl;

    boost::functional::overload<
          void (const std::string&)
        , void (int)
        , void (double)
    > print(print_s, print_i, pd);
    print("abc");
    print(123);
    print(1.23);
    std::cout << std::endl;

    BOOST_AUTO(p, boost::functional::make_overload(&print_s, &print_i, pd));
    p("abc");
    p(123);
    p(1.23);
    std::cout << std::endl;

    return 0;
}

