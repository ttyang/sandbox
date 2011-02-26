//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2010-2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/opaque for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_OPAQUE_MACROS_HPP
#define BOOST_OPAQUE_MACROS_HPP

#include <boost/config.hpp>
#include <boost/opaque/private_opaque_type.hpp>
#include <boost/opaque/boolean.hpp>
#include <boost/opaque/public_opaque_type.hpp>
#include <boost/opaque/private_opaque_class.hpp>
#include <boost/opaque/public_opaque_class.hpp>

#define BOOST_OPAQUE_PUBLIC_FORWARD_CONSTRUCTORS(UT, OT) \
    OT(){} \
    template <typename W> \
    explicit OT(W w) \
        : boost::opaque::public_opaque_class<OT, UT>(w) \
    {}\
    OT(OT const& r) \
        : boost::opaque::public_opaque_class<OT, UT>(r) \
    {}

#define BOOST_OPAQUE_PUBLIC_OPERATIONS(UT, OT) \
    BOOST_OPAQUE_PUBLIC_FORWARD_CONSTRUCTORS(UT,OT)\

//////////////////////////
#define BOOST_OPAQUE_EXT_PUBLIC_TYPEDEF(UT, OT, B) \
struct BOOST_JOIN(OT, _tag) {};\
typedef boost::opaque::public_opaque_type<UT, BOOST_JOIN(OT, _tag), B> OT

#define BOOST_OPAQUE_BOOLEAN_PUBLIC_TYPEDEF(UT, OT) \
BOOST_OPAQUE_EXT_PUBLIC_TYPEDEF(UT, OT, boost::opaque::boolean)

#define BOOST_OPAQUE_PUBLIC_TYPEDEF(UT, OT) \
BOOST_OPAQUE_EXT_PUBLIC_TYPEDEF(UT, OT, bool)

//////////////////////////
#define BOOST_OPAQUE_EXT_PUBLIC_CLASS(UT, NT1, B) \
struct NT1 : boost::opaque::public_opaque_class<NT1, UT,B> \
{ \
    typedef \
    boost::opaque::public_opaque_class<NT1, UT,B> \
    base_type; \
    \
    NT1(){} \
    explicit NT1(UT v) : base_type(v) {} \
    template <typename W>  \
    explicit NT1(W w)  \
        : base_type(w)  \
    {} \
    NT1(NT1 const& r) \
        : base_type(r.val_) \
    {} \
}

#define BOOST_OPAQUE_BOOLEAN_PUBLIC_CLASS(UT, OT) \
  BOOST_OPAQUE_EXT_PUBLIC_CLASS(UT, OT, boost::opaque::boolean)

#define BOOST_OPAQUE_PUBLIC_TYPEDEF(UT, OT) \
  BOOST_OPAQUE_EXT_PUBLIC_CLASS(UT, OT, bool)

//////////////////////////
#define BOOST_OPAQUE_PRIVATE_FORWARD_CONSTRUCTORS(UT, OT) \
    OT(){}\
    template <typename W> \
    explicit OT(W w) \
        : boost::opaque::private_opaque_class<OT, UT>(w) \
    {}\
    OT(OT const& r) \
        : boost::opaque::private_opaque_class<OT, UT>(r) \
    {}

#define BOOST_OPAQUE_PRIVATE_OPERATIONS(UT, OT) \
    BOOST_OPAQUE_PRIVATE_FORWARD_CONSTRUCTORS(UT, OT)


//////////////////////////
#define BOOST_OPAQUE_EXT_PRIVATE_TYPEDEF(UT, OT,B) \
struct BOOST_JOIN(OT, _tag) {};\
typedef boost::opaque::private_opaque_type<UT, BOOST_JOIN(OT, _tag),B> OT

#define BOOST_OPAQUE_BOOLEAN_PRIVATE_TYPEDEF(UT, OT) \
  BOOST_OPAQUE_EXT_PRIVATE_TYPEDEF(UT, OT, boost::opaque::boolean)

#define BOOST_OPAQUE_PRIVATE_TYPEDEF(UT, OT) \
  BOOST_OPAQUE_EXT_PRIVATE_TYPEDEF(UT, OT, bool)

#endif

