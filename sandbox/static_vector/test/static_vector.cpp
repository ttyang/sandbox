// Boost.Container StaticVector
// Unit Test

// Copyright (c) 2012 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2012 Andrew Hundt.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/container/static_vector.hpp>

#ifdef BOOST_SINGLE_HEADER_UTF
#define BOOST_TEST_MODULE static_vector_tests
#include <boost/test/unit_test.hpp>
#else // BOOST_SINGLE_HEADER_UTF
#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/impl/execution_monitor.ipp>
#endif // BOOST_SINGLE_HEADER_UTF

#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>
#include "movable.hpp"

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#include <boost/container/vector.hpp>
#include <boost/container/stable_vector.hpp>
#endif

using namespace boost::container;

class value_ndc
{
public:
    explicit value_ndc(int a) : aa(a) {}
    ~value_ndc() {}
    bool operator==(value_ndc const& v) const { return aa == v.aa; }
private:
    value_ndc(value_ndc const&) {}
    value_ndc & operator=(value_ndc const&) { return *this; }
    int aa;
};

class value_nd
{
public:
    explicit value_nd(int a) : aa(a) {}
    ~value_nd() {}
    bool operator==(value_nd const& v) const { return aa == v.aa; }
private:
    int aa;
};

class value_nc
{
public:
    explicit value_nc(int a = 0) : aa(a) {}
    ~value_nc() {}
    bool operator==(value_nc const& v) const { return aa == v.aa; }
private:
    value_nc(value_nc const&) {}
    value_nc & operator=(value_ndc const&) { return *this; }
    int aa;
};

class counting_value
{
    BOOST_COPYABLE_AND_MOVABLE(counting_value)

public:
    explicit counting_value(int a = 0) : aa(a) { ++c(); }
    counting_value(counting_value const& v) : aa(v.aa) { ++c(); }
    counting_value(BOOST_RV_REF(counting_value) p) : aa(p.aa) { p.aa = 0; ++c(); }                      // Move constructor
    counting_value& operator=(BOOST_RV_REF(counting_value) p) { aa = p.aa; p.aa = 0; return *this; }    // Move assignment
    counting_value& operator=(BOOST_COPY_ASSIGN_REF(counting_value) p) { aa = p.aa; return *this; }     // Copy assignment
    ~counting_value() { --c(); }
    bool operator==(counting_value const& v) const { return aa == v.aa; }
    static size_t count() { return c(); }

private:
    static size_t & c() { static size_t co = 0; return co; }
    int aa;
};

class shptr_value
{
    typedef boost::shared_ptr<int> Ptr;
public:
    explicit shptr_value(int a = 0) : m_ptr(new int(a)) {}
    bool operator==(shptr_value const& v) const { return *m_ptr == *(v.m_ptr); }
private:
    boost::shared_ptr<int> m_ptr;
};

template <class T>
class clone_ptr
{
   private:
   // Mark this class copyable and movable
   BOOST_COPYABLE_AND_MOVABLE(clone_ptr)
   T* ptr;

   public:
   // Construction
   explicit clone_ptr(T* p = 0) : ptr(p) {}

   // Destruction
   ~clone_ptr() { delete ptr; }

   clone_ptr(const clone_ptr& p) // Copy constructor (as usual)
      : ptr(p.ptr ? p.ptr->clone() : 0) {}

   clone_ptr& operator=(BOOST_COPY_ASSIGN_REF(clone_ptr) p) // Copy assignment
   {
      if (this != &p){
         T *tmp_p = p.ptr ? p.ptr->clone() : 0;
         delete ptr;
         ptr = tmp_p;
      }
      return *this;
   }

   //Move semantics...
   clone_ptr(BOOST_RV_REF(clone_ptr) p)            //Move constructor
      : ptr(p.ptr) { p.ptr = 0; }

   clone_ptr& operator=(BOOST_RV_REF(clone_ptr) p) //Move assignment
   {
      if (this != &p){
         delete ptr;
         ptr = p.ptr;
         p.ptr = 0;
      }
      return *this;
   }
   
   bool operator==(const clone_ptr& p){
        return p.ptr == ptr;
   }
};

template <typename T, size_t N>
void test_ctor_ndc()
{
    static_vector<T, N> s;
    BOOST_CHECK_EQUAL(s.size() , 0);
    BOOST_CHECK(s.capacity() == N);
    BOOST_CHECK_THROW( s.at(0), std::out_of_range );
}

template <typename T, size_t N>
void test_ctor_nc(size_t n)
{
    static_vector<T, N> s(n);
    BOOST_CHECK(s.size() == n);
    BOOST_CHECK(s.capacity() == N);
    BOOST_CHECK_THROW( s.at(n), std::out_of_range );
    if ( 1 < n )
    {
        T val10(10);
        s[0] = val10;
        BOOST_CHECK(T(10) == s[0]);
        BOOST_CHECK(T(10) == s.at(0));
        T val20(20);
        s.at(1) = val20;
        BOOST_CHECK(T(20) == s[1]);
        BOOST_CHECK(T(20) == s.at(1));
    }
}

template <typename T, size_t N>
void test_ctor_nd(size_t n, T const& v)
{
    static_vector<T, N> s(n, v);
    BOOST_CHECK(s.size() == n);
    BOOST_CHECK(s.capacity() == N);
    BOOST_CHECK_THROW( s.at(n), std::out_of_range );
    if ( 1 < n )
    {
        BOOST_CHECK(v == s[0]);
        BOOST_CHECK(v == s.at(0));
        BOOST_CHECK(v == s[1]);
        BOOST_CHECK(v == s.at(1));
        s[0] = T(10);
        BOOST_CHECK(T(10) == s[0]);
        BOOST_CHECK(T(10) == s.at(0));
        s.at(1) = T(20);
        BOOST_CHECK(T(20) == s[1]);
        BOOST_CHECK(T(20) == s.at(1));
    }
}

template <typename T, size_t N>
void test_resize_nc(size_t n)
{
    static_vector<T, N> s;

    s.resize(n);
    BOOST_CHECK(s.size() == n);
    BOOST_CHECK(s.capacity() == N);
    BOOST_CHECK_THROW( s.at(n), std::out_of_range );
    if ( 1 < n )
    {
        T val10(10);
        s[0] = val10;
        BOOST_CHECK(T(10) == s[0]);
        BOOST_CHECK(T(10) == s.at(0));
        T val20(20);
        s.at(1) = val20;
        BOOST_CHECK(T(20) == s[1]);
        BOOST_CHECK(T(20) == s.at(1));
    }
}

template <typename T, size_t N>
void test_resize_nd(size_t n, T const& v)
{
    static_vector<T, N> s;

    s.resize(n, v);
    BOOST_CHECK(s.size() == n);
    BOOST_CHECK(s.capacity() == N);
    BOOST_CHECK_THROW( s.at(n), std::out_of_range );
    if ( 1 < n )
    {
        BOOST_CHECK(v == s[0]);
        BOOST_CHECK(v == s.at(0));
        BOOST_CHECK(v == s[1]);
        BOOST_CHECK(v == s.at(1));
        s[0] = T(10);
        BOOST_CHECK(T(10) == s[0]);
        BOOST_CHECK(T(10) == s.at(0));
        s.at(1) = T(20);
        BOOST_CHECK(T(20) == s[1]);
        BOOST_CHECK(T(20) == s.at(1));
    }
}

template <typename T, size_t N>
void test_push_back_nd()
{
    static_vector<T, N> s;

    BOOST_CHECK(s.size() == 0);
    BOOST_CHECK_THROW( s.at(0), std::out_of_range );

    for ( size_t i = 0 ; i < N ; ++i )
    {
        s.push_back(T(i));
        BOOST_CHECK(s.size() == i + 1);
        BOOST_CHECK_THROW( s.at(i + 1), std::out_of_range );
        BOOST_CHECK(T(i) == s.at(i));
        BOOST_CHECK(T(i) == s[i]);
        BOOST_CHECK(T(i) == s.back());
        BOOST_CHECK(T(0) == s.front());
    }
}

template <typename T, size_t N>
void test_pop_back_nd()
{
    static_vector<T, N> s;

    for ( size_t i = 0 ; i < N ; ++i )
        s.push_back(T(i));    

    for ( size_t i = N ; i > 1 ; --i )
    {
        s.pop_back();
        BOOST_CHECK(s.size() == i - 1);
        BOOST_CHECK_THROW( s.at(i - 1), std::out_of_range );
        BOOST_CHECK(T(i - 2) == s.at(i - 2));
        BOOST_CHECK(T(i - 2) == s[i - 2]);
        BOOST_CHECK(T(i - 2) == s.back());
        BOOST_CHECK(T(0) == s.front());
    }
}

template <typename It1, typename It2>
void test_compare_ranges(It1 first1, It1 last1, It2 first2, It2 last2)
{
    BOOST_CHECK(std::distance(first1, last1) == std::distance(first2, last2));
    for ( ; first1 != last1 && first2 != last2 ; ++first1, ++first2 )
        BOOST_CHECK(*first1 == *first2);
}

template <typename T, size_t N, typename C>
void test_copy_and_assign(C const& c)
{
    {
        static_vector<T, N> s(c.begin(), c.end());
        BOOST_CHECK(s.size() == c.size());
        test_compare_ranges(s.begin(), s.end(), c.begin(), c.end());
    }
    {
        static_vector<T, N> s;
        BOOST_CHECK(0 == s.size());
        s.assign(c.begin(), c.end());
        BOOST_CHECK(s.size() == c.size());
        test_compare_ranges(s.begin(), s.end(), c.begin(), c.end());
    }
}

template <typename T, size_t N>
void test_copy_and_assign_nd(T const& val)
{
    static_vector<T, N> s;
    std::vector<T> v;
    std::list<T> l;

    for ( size_t i = 0 ; i < N ; ++i )
    {
        s.push_back(T(i));
        v.push_back(T(i));
        l.push_back(T(i));
    }
    // copy ctor
    {
        static_vector<T, N> s1(s);
        BOOST_CHECK(s.size() == s1.size());
        test_compare_ranges(s.begin(), s.end(), s1.begin(), s1.end());
    }
    // copy assignment
    {
        static_vector<T, N> s1;
        BOOST_CHECK(0 == s1.size());
        s1 = s;
        BOOST_CHECK(s.size() == s1.size());
        test_compare_ranges(s.begin(), s.end(), s1.begin(), s1.end());
    }

    // ctor(Iter, Iter) and assign(Iter, Iter)
    test_copy_and_assign<T, N>(s);
    test_copy_and_assign<T, N>(v);
    test_copy_and_assign<T, N>(l);

    // assign(N, V)
    {
        static_vector<T, N> s1(s);
        test_compare_ranges(s.begin(), s.end(), s1.begin(), s1.end());
        std::vector<T> a(N, val);
        s1.assign(N, val);
        test_compare_ranges(a.begin(), a.end(), s1.begin(), s1.end());
    }

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    stable_vector<T> bsv(s.begin(), s.end());
    vector<T> bv(s.begin(), s.end());
    test_copy_and_assign<T, N>(bsv);
    test_copy_and_assign<T, N>(bv);
#endif
}

template <typename T, size_t N>
void test_iterators_nd()
{
    static_vector<T, N> s;
    std::vector<T> v;

    for ( size_t i = 0 ; i < N ; ++i )
    {
        s.push_back(T(i));
        v.push_back(T(i));
    }

    test_compare_ranges(s.begin(), s.end(), v.begin(), v.end());
    test_compare_ranges(s.rbegin(), s.rend(), v.rbegin(), v.rend());

    s.assign(v.rbegin(), v.rend());

    test_compare_ranges(s.begin(), s.end(), v.rbegin(), v.rend());
    test_compare_ranges(s.rbegin(), s.rend(), v.begin(), v.end());
}

template <typename T, size_t N>
void test_erase_nd()
{
    static_vector<T, N> s;
    typedef typename static_vector<T, N>::iterator It;
    
    for ( size_t i = 0 ; i < N ; ++i )
        s.push_back(T(i));

    // erase(pos)
    {
        for ( size_t i = 0 ; i < N ; ++i )
        {
            static_vector<T, N> s1(s);
            It it = s1.erase(s1.begin() + i);
            BOOST_CHECK(s1.begin() + i == it);
            BOOST_CHECK(s1.size() == N - 1);
            for ( size_t j = 0 ; j < i ; ++j )
                BOOST_CHECK(s1[j] == T(j));
            for ( size_t j = i+1 ; j < N ; ++j )
                BOOST_CHECK(s1[j-1] == T(j));
        }        
    }
    // erase(first, last)
    {
        size_t n = N/3;
        for ( size_t i = 0 ; i <= N ; ++i )
        {
            static_vector<T, N> s1(s);
            size_t removed = i + n < N ? n : N - i;
            It it = s1.erase(s1.begin() + i, s1.begin() + i + removed);
            BOOST_CHECK(s1.begin() + i == it);
            BOOST_CHECK(s1.size() == N - removed);
            for ( size_t j = 0 ; j < i ; ++j )
                BOOST_CHECK(s1[j] == T(j));
            for ( size_t j = i+n ; j < N ; ++j )
                BOOST_CHECK(s1[j-n] == T(j));
        }        
    }
}

template <typename T, size_t N, typename SV, typename C>
void test_insert(SV const& s, C const& c)
{
    size_t h = N/2;
    size_t n = size_t(h/1.5f);

    for ( size_t i = 0 ; i <= h ; ++i )
    {
        static_vector<T, N> s1(s);

        typename C::const_iterator it = c.begin();
        std::advance(it, n);
        typename static_vector<T, N>::iterator
            it1 = s1.insert(s1.begin() + i, c.begin(), it);

        BOOST_CHECK(s1.begin() + i == it1);
        BOOST_CHECK(s1.size() == h+n);
        for ( size_t j = 0 ; j < i ; ++j )
            BOOST_CHECK(s1[j] == T(j));
        for ( size_t j = 0 ; j < n ; ++j )
            BOOST_CHECK(s1[j+i] == T(100 + j));
        for ( size_t j = 0 ; j < h-i ; ++j )
            BOOST_CHECK(s1[j+i+n] == T(j+i));
    }
}

template <typename T, size_t N>
void test_insert_nd(T const& val)
{
    size_t h = N/2;

    static_vector<T, N> s, ss;
    std::vector<T> v;
    std::list<T> l;

    typedef typename static_vector<T, N>::iterator It;

    for ( size_t i = 0 ; i < h ; ++i )
    {
        s.push_back(T(i));
        ss.push_back(T(100 + i));
        v.push_back(T(100 + i));
        l.push_back(T(100 + i));
    }

    // insert(pos, val)
    {
        for ( size_t i = 0 ; i <= h ; ++i )
        {
            static_vector<T, N> s1(s);
            It it = s1.insert(s1.begin() + i, val);
            BOOST_CHECK(s1.begin() + i == it);
            BOOST_CHECK(s1.size() == h+1);
            for ( size_t j = 0 ; j < i ; ++j )
                BOOST_CHECK(s1[j] == T(j));
            BOOST_CHECK(s1[i] == val);
            for ( size_t j = 0 ; j < h-i ; ++j )
                BOOST_CHECK(s1[j+i+1] == T(j+i));
        }        
    }
    // insert(pos, n, val)
    {
        size_t n = size_t(h/1.5f);
        for ( size_t i = 0 ; i <= h ; ++i )
        {
            static_vector<T, N> s1(s);
            It it = s1.insert(s1.begin() + i, n, val);
            BOOST_CHECK(s1.begin() + i == it);
            BOOST_CHECK(s1.size() == h+n);
            for ( size_t j = 0 ; j < i ; ++j )
                BOOST_CHECK(s1[j] == T(j));
            for ( size_t j = 0 ; j < n ; ++j )
                BOOST_CHECK(s1[j+i] == val);
            for ( size_t j = 0 ; j < h-i ; ++j )
                BOOST_CHECK(s1[j+i+n] == T(j+i));
        }        
    }
    // insert(pos, first, last)
    test_insert<T, N>(s, ss);
    test_insert<T, N>(s, v);
    test_insert<T, N>(s, l);

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    stable_vector<T> bsv(ss.begin(), ss.end());
    vector<T> bv(ss.begin(), ss.end());
    test_insert<T, N>(s, bv);
    test_insert<T, N>(s, bsv);
#endif
}

struct bad_alloc_strategy : public static_vector_detail::default_strategy<>
{
    template <typename V, std::size_t Capacity, typename S>
    static void check_capacity(static_vector<V, Capacity, S> const&, std::size_t s)
    {
        if ( Capacity < s )
            throw std::bad_alloc();
    }
};

namespace boost { namespace container { namespace static_vector_detail {

template <typename Value, std::size_t Capacity>
struct static_vector_traits<Value, Capacity, bad_alloc_strategy>
{
    typedef std::size_t size_type;
    typedef boost::false_type use_nonthrowing_swap;
    typedef bad_alloc_strategy strategy;
};

}}}

template <typename T>
void test_capacity_0_nd()
{
    static_vector<T, 10> v(5u, T(0));

    static_vector<T, 0, bad_alloc_strategy> s;
    BOOST_CHECK(s.size() == 0);
    BOOST_CHECK(s.capacity() == 0);
    BOOST_CHECK_THROW(s.at(0), std::out_of_range);
    BOOST_CHECK_THROW(s.resize(5u, T(0)), std::bad_alloc);
    BOOST_CHECK_THROW(s.push_back(T(0)), std::bad_alloc);
    BOOST_CHECK_THROW(s.insert(s.end(), T(0)), std::bad_alloc);
    BOOST_CHECK_THROW(s.insert(s.end(), 5u, T(0)), std::bad_alloc);
    BOOST_CHECK_THROW(s.insert(s.end(), v.begin(), v.end()), std::bad_alloc);
    BOOST_CHECK_THROW(s.assign(v.begin(), v.end()), std::bad_alloc);
    BOOST_CHECK_THROW(s.assign(5u, T(0)), std::bad_alloc);
    try{
        static_vector<T, 0, bad_alloc_strategy> s2(v.begin(), v.end());
        BOOST_CHECK(false);
    }catch(std::bad_alloc &){}
    try{
        static_vector<T, 0, bad_alloc_strategy> s1(5u, T(0));
        BOOST_CHECK(false);
    }catch(std::bad_alloc &){}
}

template <typename T, size_t N>
void test_exceptions_nd()
{
    static_vector<T, N> v(N, T(0));
    static_vector<T, N/2, bad_alloc_strategy> s(N/2, T(0));

    BOOST_CHECK_THROW(s.resize(N, T(0)), std::bad_alloc);
    BOOST_CHECK_THROW(s.push_back(T(0)), std::bad_alloc);
    BOOST_CHECK_THROW(s.insert(s.end(), T(0)), std::bad_alloc);
    BOOST_CHECK_THROW(s.insert(s.end(), N, T(0)), std::bad_alloc);
    BOOST_CHECK_THROW(s.insert(s.end(), v.begin(), v.end()), std::bad_alloc);
    BOOST_CHECK_THROW(s.assign(v.begin(), v.end()), std::bad_alloc);
    BOOST_CHECK_THROW(s.assign(N, T(0)), std::bad_alloc);
    try{
        static_vector<T, N/2, bad_alloc_strategy> s2(v.begin(), v.end());
        BOOST_CHECK(false);
    }catch(std::bad_alloc &){}
    try{
        static_vector<T, N/2, bad_alloc_strategy> s1(N, T(0));
        BOOST_CHECK(false);
    }catch(std::bad_alloc &){}
}

template <typename T, size_t N>
void test_swap_and_move_nd()
{
    {
        static_vector<T, N> v1, v2, v3, v4;
        static_vector<T, N> s1, s2;
        static_vector<T, N, bad_alloc_strategy> s4;

        for (size_t i = 0 ; i < N ; ++i )
        {
            v1.push_back(T(i));
            v2.push_back(T(i));
            v3.push_back(T(i));
            v4.push_back(T(i));
        }
        for (size_t i = 0 ; i < N/2 ; ++i )
        {
            s1.push_back(T(100 + i));
            s2.push_back(T(100 + i));
            s4.push_back(T(100 + i));
        }

        s1.swap(v1);
        s2 = boost::move(v2);
        static_vector<T, N> s3(boost::move(v3));
        v4.swap(s4);

        BOOST_CHECK(v1.size() == N/2);
        BOOST_CHECK(s1.size() == N);
        BOOST_CHECK(v2.size() == 0);
        BOOST_CHECK(s2.size() == N);
        BOOST_CHECK(v3.size() == 0);
        BOOST_CHECK(s3.size() == N);
        BOOST_CHECK(v4.size() == N/2);
        BOOST_CHECK(s4.size() == N);
        for (size_t i = 0 ; i < N/2 ; ++i )
        {
            BOOST_CHECK(v1[i] == T(100 + i));
            BOOST_CHECK(v4[i] == T(100 + i));
        }
        for (size_t i = 0 ; i < N ; ++i )
        {
            BOOST_CHECK(s1[i] == T(i));
            BOOST_CHECK(s2[i] == T(i));
            BOOST_CHECK(s3[i] == T(i));
            BOOST_CHECK(s4[i] == T(i));
        }
    }
    {
        static_vector<T, N> v1, v2, v3;
        static_vector<T, N/2> s1, s2;

        for (size_t i = 0 ; i < N/2 ; ++i )
        {
            v1.push_back(T(i));
            v2.push_back(T(i));
            v3.push_back(T(i));
        }
        for (size_t i = 0 ; i < N/3 ; ++i )
        {
            s1.push_back(T(100 + i));
            s2.push_back(T(100 + i));
        }

        s1.swap(v1);
        s2 = boost::move(v2);
        static_vector<T, N/2> s3(boost::move(v3));

        BOOST_CHECK(v1.size() == N/3);
        BOOST_CHECK(s1.size() == N/2);
        BOOST_CHECK(v2.size() == 0);
        BOOST_CHECK(s2.size() == N/2);
        BOOST_CHECK(v3.size() == 0);
        BOOST_CHECK(s3.size() == N/2);
        for (size_t i = 0 ; i < N/3 ; ++i )
            BOOST_CHECK(v1[i] == T(100 + i));
        for (size_t i = 0 ; i < N/2 ; ++i )
        {
            BOOST_CHECK(s1[i] == T(i));
            BOOST_CHECK(s2[i] == T(i));
            BOOST_CHECK(s3[i] == T(i));
        }
    }
    {
        static_vector<T, N> v(N, T(0));
        static_vector<T, N/2, bad_alloc_strategy> s(N/2, T(1));
        BOOST_CHECK_THROW(s.swap(v), std::bad_alloc);
        v.resize(N, T(0));
        BOOST_CHECK_THROW(s = boost::move(v), std::bad_alloc);
        v.resize(N, T(0));
        try {
            static_vector<T, N/2, bad_alloc_strategy> s2(boost::move(v));
            BOOST_CHECK(false);
        } catch (std::bad_alloc &) {}
    }
}

#ifdef BOOST_SINGLE_HEADER_UTF
BOOST_AUTO_TEST_CASE(static_vector_test)
#else // BOOST_SINGLE_HEADER_UTF
int test_main(int, char* [])
#endif // BOOST_SINGLE_HEADER_UTF
{
  
    BOOST_CHECK_EQUAL(counting_value::count(), 0);
    test_ctor_ndc<int, 10>();
    test_ctor_ndc<value_ndc, 10>();
    test_ctor_ndc<counting_value, 10>();
    BOOST_CHECK(counting_value::count() == 0);
    test_ctor_ndc<shptr_value, 10>();
    test_ctor_ndc<copy_movable, 10>();

    test_ctor_nc<int, 10>(5);
    test_ctor_nc<value_nc, 10>(5);
    test_ctor_nc<counting_value, 10>(5);
    BOOST_CHECK(counting_value::count() == 0);
    test_ctor_nc<shptr_value, 10>(5);
    test_ctor_nc<copy_movable, 10>(5);

    test_ctor_nd<int, 10>(5, 1);
    test_ctor_nd<value_nd, 10>(5, value_nd(1));
    test_ctor_nd<counting_value, 10>(5, counting_value(1));
    BOOST_CHECK(counting_value::count() == 0);
    test_ctor_nd<shptr_value, 10>(5, shptr_value(1));
    test_ctor_nd<copy_movable, 10>(5, produce());

    test_resize_nc<int, 10>(5);
    test_resize_nc<value_nc, 10>(5);
    test_resize_nc<counting_value, 10>(5);
    BOOST_CHECK(counting_value::count() == 0);
    test_resize_nc<shptr_value, 10>(5);
    test_resize_nc<copy_movable, 10>(5);

    test_resize_nd<int, 10>(5, 1);
    test_resize_nd<value_nd, 10>(5, value_nd(1));
    test_resize_nd<counting_value, 10>(5, counting_value(1));
    BOOST_CHECK(counting_value::count() == 0);
    test_resize_nd<shptr_value, 10>(5, shptr_value(1));
    test_resize_nd<copy_movable, 10>(5, produce());

    test_push_back_nd<int, 10>();
    test_push_back_nd<value_nd, 10>();
    test_push_back_nd<counting_value, 10>();
    BOOST_CHECK(counting_value::count() == 0);
    test_push_back_nd<shptr_value, 10>();
    test_push_back_nd<copy_movable, 10>();

    test_pop_back_nd<int, 10>();
    test_pop_back_nd<value_nd, 10>();
    test_pop_back_nd<counting_value, 10>();
    BOOST_CHECK(counting_value::count() == 0);
    test_pop_back_nd<shptr_value, 10>();
    test_pop_back_nd<copy_movable, 10>();

    test_copy_and_assign_nd<int, 10>(1);
    test_copy_and_assign_nd<value_nd, 10>(value_nd(1));
    test_copy_and_assign_nd<counting_value, 10>(counting_value(1));
    BOOST_CHECK(counting_value::count() == 0);
    test_copy_and_assign_nd<shptr_value, 10>(shptr_value(1));
    test_copy_and_assign_nd<copy_movable, 10>(produce());

    test_iterators_nd<int, 10>();
    test_iterators_nd<value_nd, 10>();
    test_iterators_nd<counting_value, 10>();
    BOOST_CHECK(counting_value::count() == 0);
    test_iterators_nd<shptr_value, 10>();
    test_iterators_nd<copy_movable, 10>();

    test_erase_nd<int, 10>();
    test_erase_nd<value_nd, 10>();
    test_erase_nd<counting_value, 10>();
    BOOST_CHECK(counting_value::count() == 0);
    test_erase_nd<shptr_value, 10>();
    test_erase_nd<copy_movable, 10>();

    test_insert_nd<int, 10>(50);
    test_insert_nd<value_nd, 10>(value_nd(50));
    test_insert_nd<counting_value, 10>(counting_value(50));
    BOOST_CHECK(counting_value::count() == 0);
    test_insert_nd<shptr_value, 10>(shptr_value(50));
    test_insert_nd<copy_movable, 10>(produce());

    test_capacity_0_nd<int>();
    test_capacity_0_nd<value_nd>();
    test_capacity_0_nd<counting_value>();
    BOOST_CHECK(counting_value::count() == 0);
    test_capacity_0_nd<shptr_value>();
    test_capacity_0_nd<copy_movable>();

    test_exceptions_nd<int, 10>();
    test_exceptions_nd<value_nd, 10>();
    test_exceptions_nd<counting_value, 10>();
    BOOST_CHECK(counting_value::count() == 0);
    test_exceptions_nd<shptr_value, 10>();
    test_exceptions_nd<copy_movable, 10>();

    test_swap_and_move_nd<int, 10>();
    test_swap_and_move_nd<value_nd, 10>();
    test_swap_and_move_nd<counting_value, 10>();
    BOOST_CHECK(counting_value::count() == 0);
    test_swap_and_move_nd<shptr_value, 10>();
    test_swap_and_move_nd<copy_movable, 10>();

#ifndef BOOST_SINGLE_HEADER_UTF
    return 0;
#endif // BOOST_SINGLE_HEADER_UTF
}
