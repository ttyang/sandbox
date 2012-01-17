
#include <boost/functional/overload.hpp>
#include <boost/function.hpp>
#include <boost/function_types/is_function.hpp>
#include <boost/function_types/is_function_pointer.hpp>
#include <boost/function_types/is_function_reference.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/typeof/typeof.hpp>
#include <iostream>
#include <string>

namespace boost { namespace functional {

namespace detail {

// Requires: F is a monomorphic functor (i.e., has non-template `operator()`).
template<typename F>
class functor_type {
    typedef BOOST_TYPEOF_TPL(&(F::operator())) call_ptr;
public:
    typedef
        typename boost::function_types::function_type<
            typename boost::mpl::push_front<
                  typename boost::mpl::pop_front< // Remove functor type (1st).
                    typename boost::function_types::parameter_types<
                            call_ptr>::type
                  >::type
                , typename boost::function_types::result_type<call_ptr>::type
            >::type
        >::type
    type;
};

// Requires: F is a function type, pointer, reference, or monomorphic functor.
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
                , // Requires, it's a functor.
                    functor_type<F>
                >::type
            >::type
        >::type
    ::type type;
};

} // namespace detail

// F must be either a function type, pointer, reference, or monomorphic functor.
template<typename F0, typename F1, typename F2>
overload<
      typename detail::function_type<F0>::type
    , typename detail::function_type<F1>::type
    , typename detail::function_type<F2>::type
> make_overload(F0 f0, F1 f1, F2 f2) {
    return overload<
          typename detail::function_type<F0>::type
        , typename detail::function_type<F1>::type
        , typename detail::function_type<F2>::type
    >(f0, f1, f2);
}

} } // namespace boost::functional

template<typename F>
void call(F print) {
    print("abc");
    print(123);
    print(1.23);
}

void print_s(const std::string& s) { std::cout << s << std::endl; }
void print_i(int i) { std::cout << i << std::endl; }
void print_d_impl(double d) { std::cout << d << std::endl; }
boost::function<void (double)> print_d = print_d_impl;

int main(void) {
    print_s("abc");
    print_i(123);
    print_d(1.23);
    std::cout << std::endl;

    boost::functional::overload<
          void (const std::string&)
        , void (int)
        , void (double)
    > print(print_s, print_i, print_d);
    print("abc");
    print(123);
    print(1.23);
    std::cout << std::endl;
    
    BOOST_AUTO(p, boost::functional::make_overload(print_s, print_i, print_d));
    p("abc");
    p(123);
    p(1.23);
    std::cout << std::endl;

    call(boost::functional::make_overload(print_s, print_i, print_d));
    return 0;
}

