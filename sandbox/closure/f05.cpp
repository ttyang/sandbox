
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

namespace detail { namespace overload {

// Transform a function F into a functor type.
// Precondition: F is a function type, a function pointer, a function
// reference, or already a functor.
template<typename F>
class functor_wrap {
    template<typename MetaF>
    struct functor {
        typedef typename boost::function< typename MetaF::type > type;
    };
public:
    typedef
        typename boost::mpl::if_< boost::function_types::is_function<F>,
            functor< boost::mpl::identity<F> >
        ,
            typename boost::mpl::if_< boost::function_types::
                    is_function_pointer< F >,
                functor< boost::remove_pointer< F > >
            ,
                typename boost::mpl::if_< boost::function_types::
                        is_function_reference< F >,
                    functor< boost::remove_reference< F > >
                , // Requires: It's already a functor.
                    boost::mpl::identity< F >
                >::type
            >::type
        >::type
    ::type type;
};

// Transform a functor F into a function type.
template<typename F>
struct functor_unwrap {
    typedef
        typename boost::function_types::function_type<
            typename boost::mpl::push_front<
                  typename boost::mpl::pop_front< // Remove functor type (1st).
                    typename boost::function_types::parameter_types<F>::type
                  >::type
                , typename boost::function_types::result_type<F>::type
            >::type
        >::type
    type;
};
    
template<typename F0, typename F1, typename F2>
struct deduce_type {
    typedef boost::functional::overload<
          typename functor_unwrap<
            BOOST_TYPEOF_TPL(&(functor_wrap<F0>::type::operator()))
          >::type
        , typename functor_unwrap<
            BOOST_TYPEOF_TPL(&(functor_wrap<F1>::type::operator()))
          >::type
        , typename functor_unwrap<
            BOOST_TYPEOF_TPL(&(functor_wrap<F2>::type::operator()))
          >::type
    > type;
};

} }  // namespace detail::overload

template<typename F0, typename F1, typename F2>
typename detail::overload::deduce_type<F0, F1, F2>::type
make_overload(F0 f0, F1 f1, F2 f2) {
    return typename detail::overload::deduce_type<F0, F1, F2>::type(f0, f1, f2);
}

} } // namespace boost::functional

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

