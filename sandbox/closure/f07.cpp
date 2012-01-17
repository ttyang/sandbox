
#include <boost/functional/overload.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <string>

template<typename F>
void call(F print) {
    print("abc");
    print(123);
    print(1.23);
}

void s(const std::string& s) { std::cout << s << std::endl; }
void i(int i) { std::cout << i << std::endl; }
void d_impl(double d) { std::cout << d << std::endl; }
boost::function<void (double)> d = d_impl;

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

