
#ifndef ADDABLE_HPP_
#define ADDABLE_HPP_

#include <boost/concept_check.hpp>

template<typename T>
struct Addable { // User-defined concept.
    BOOST_CONCEPT_USAGE(Addable) {
        return_type(x + y); // Check addition `T operator+(T x, T y)`.
    }
private:
    T x;
    T y;
    void return_type(T const&); // Used to check addition returns type `T`.
};

#endif // #include guard

