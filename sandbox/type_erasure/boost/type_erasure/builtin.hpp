// Boost.TypeErasure library
//
// Copyright 2011 Steven Watanabe
//
// Distributed under the Boost Software License Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// $Id$

#ifndef BOOST_TYPE_ERASURE_BUILTIN_HPP_INCLUDED
#define BOOST_TYPE_ERASURE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/type_erasure/detail/storage.hpp>
#include <boost/type_erasure/placeholder.hpp>
#include <boost/type_erasure/constructible.hpp>
#include <boost/type_erasure/rebind_any.hpp>
#include <typeinfo>

namespace boost {
namespace type_erasure {

/**
 * The @ref destructible concept enables forwarding to
 * the destructor of the contained type.  This is required
 * whenever an @ref any is created by value.
 *
 * \note The @ref destructible concept rarely needs to
 * be specified explicitly, because it is included in
 * the @ref copy_constructible concept.
 */
template<class T = _self>
struct destructible
{
    /** INTERNAL ONLY */
    typedef void (*type)(detail::storage&);
    /** INTERNAL ONLY */
    static void value(detail::storage& arg)
    {
        delete static_cast<T*>(arg.data);
    }
};

/**
 * The @ref copy_constructible concept allows objects to
 * be copied and destroyed.
 *
 * \note This concept is defined to match C++ 2003,
 * [lib.copyconstructible].  It is not equivalent to
 * the concept of the same name in C++11.
 */
template<class T = _self>
struct copy_constructible :
    ::boost::mpl::vector<constructible<T(const T&)>, destructible<T> >
{};

/**
 * Enables assignment of @ref any types.
 */
template<class T = _self, class U = T>
struct assignable
{
    static void apply(T& dst, const U& src) { dst = src; }
};

/** INTERNAL ONLY */
template<class T, class U, class Base>
struct concept_interface<assignable<T, U>, Base, T> : Base
{
    using Base::_boost_type_erasure_deduce_assign;
    assignable<T, U>* _boost_type_erasure_deduce_assign(
        typename ::boost::type_erasure::rebind_any<Base, const U&>::type)
    {
        return 0;
    }
};

/**
 * Enables runtime type information.  This is required
 * if you want to use @ref any_cast or @ref typeid_of.
 */
template<class T = _self>
struct typeid_
{
    /** INTERNAL ONLY */
    typedef const std::type_info& (*type)();
    /** INTERNAL ONLY */
    static const std::type_info& value()
    {
        return typeid(T);
    }
};

}
}

#endif
