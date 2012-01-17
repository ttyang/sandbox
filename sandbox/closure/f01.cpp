
#include <boost/functional/overload.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <iostream>
#include <string>
#include <typeinfo>

template<typename F, int Arity> struct compose_arity {};
template<typename F> struct compose_arity<F, 0> {
    typedef typename F::result_type (type)(
    );
};
template<typename F> struct compose_arity<F, 1> {
    typedef typename F::result_type (type)(
          typename F::arg1_type
    );
};
template<typename F> struct compose_arity<F, 2> {
    typedef typename F::result_type (type)(
          typename F::arg1_type
        , typename F::arg2_type
    );
};

template<typename F>
struct compose {
    typedef typename compose_arity<F, F::arity>::type type;
};

// Precondition: F is not ptr or ref to function.
template<typename F>
struct dispatch {
    typedef
        typename boost::mpl::if_<boost::is_function<F>,
            boost::mpl::identity<F>
        ,
            compose<F>  
        >::type::type
    type;
};

template<typename F>
struct function_type {
    typedef
        typename dispatch<
        typename boost::remove_pointer<
        typename boost::remove_reference<
            F
        >::type>::type>::type
    type;
};

template<typename F0, typename F1, typename F2>
boost::functional::overload<
      typename function_type<F0>::type
    , typename function_type<F1>::type
    , typename function_type<F2>::type
>
make_overload(F0 f0, F1 f1, F2 f2) {
/*    std::cout << "xx\n";
    std::cout << typeid(typename function_type<F0>::type).name() << std::endl;
    std::cout << typeid(typename function_type<F1>::type).name() << std::endl;
    std::cout << typeid(typename function_type<F2>::type).name() << std::endl;
    std::cout << "yy\n";*/
    return boost::functional::overload<
          typename function_type<F0>::type
        , typename function_type<F1>::type
        , typename function_type<F2>::type
    >(f0, f1, f2);
}


void print_s(const std::string& s) { std::cout << s << std::endl; }
void print_i(int i) { std::cout << i << std::endl; }
void print_d(double d) { std::cout << d << std::endl; }

int main(void) {
    boost::function<void (double)> pd = print_d;
    print_s("abc");
    print_i(123);
    pd(1.23);

    boost::functional::overload<
          void (const std::string&)
        , void (int)
        , void (double)
    > print(print_s, print_i, pd);
    print("abc");
    print(123);
    print(1.23);

    make_overload(&print_s, &print_i, pd);

    return 0;
}

