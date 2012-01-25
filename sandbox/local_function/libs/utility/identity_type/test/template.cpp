
#include <boost/utility/identity_type.hpp>
#include <map>
#include <iostream>

//[template_f_decl
#define ARG(type, n) type arg ## n

template<typename T>
void f( // Prefix macro with `typename` in templates.
    ARG( typename BOOST_IDENTITY_TYPE((std::map<int, T>)), 1 )
) {
    std::cout << arg1[0] << std::endl;
}
//]

//[template_g_decl
template<typename T>
void g(
    std::map<int, T> arg1
) {
    std::cout << arg1[0] << std::endl;
}
//]

int main() {
    //[template_f_call
    std::map<int, char> a;
    a[0] = 'a';
    
    f<char>(a); // OK.
    // f(a);    // But error.
    //]

    //[template_g_call
    g<char>(a); // OK.
    g(a);       // Also OK.
    //]
    
    return 0;
}

