
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <contract.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/type_traits/has_plus.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility.hpp>
#include <boost/detail/lightweight_test.hpp>

//[has_oldof_inc
CONTRACT_FUNCTION(
    template( typename T )
    (T&) (inc) ( (T&) value, (T const&) offset )
        postcondition(
            auto old_value = CONTRACT_OLDOF value,      // Skip if no old-of.
            auto result = return,                       // Never skipped.
            value == old_value + offset, requires
                    contract::has_oldof<T>::value and   // Requires old-of.
                    boost::has_plus<T>::value and
                    boost::has_equal_to<T>::value,
            result == value, requires
                    boost::has_equal_to<T>::value
        )
) {
    return value += offset;
}

class num : boost::noncopyable // Non-copyable (for some reason...).
{
    public: explicit num ( int value ) : ptr_(new int(value)) {}
    private: num ( num const& other ) : ptr_(other.ptr_) {} // Private copy.
    public: ~num ( void ) { delete ptr_; }
    
    public: num operator+ ( num const& right ) const
        { return num(*ptr_ + *right.ptr_); }
    public: num& operator+= ( num const& right )
        { *ptr_ += *right.ptr_; return *this; }
    public: bool operator== ( num const& right ) const
        { return *ptr_ == *right.ptr_; }
    
    private: int* ptr_;
};

// Specialization disables old-of for non-copyable `num` (no C++ type trait can
// automatically detect copy constructors).
namespace contract
{
    template< > struct has_oldof < num > : boost::mpl::false_ {};
} // namespace
//]

int main ( void )
{
    //[has_oldof_inc_call
    int i = 1, j = 2;
    BOOST_TEST(inc(i, j) == 3);

    num n(1), m(2);
    BOOST_TEST(inc(n, m) == num(3));
    //]
    return boost::report_errors();
}

