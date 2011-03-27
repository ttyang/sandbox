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

/**
 * @file
 * Defines helper macros.
 */

#ifndef BOOST_OPAQUE_MACROS_HPP
#define BOOST_OPAQUE_MACROS_HPP

#include <boost/config.hpp>
#include <boost/opaque/private_opaque_type.hpp>
#include <boost/opaque/boolean.hpp>
#include <boost/opaque/public_opaque_type.hpp>
#include <boost/opaque/private_opaque_class.hpp>
#include <boost/opaque/public_opaque_class.hpp>


/** forward the constructors from the new class @c OT to the base class @ BASE

 @Note This macro can be used only inside the public part of a class.

 @Params
 @Param{OT, the class been defined}
 @Param{BASE, the base class}

 @Result
 @code
    OT(){}
    template <typename W>
    explicit OT(W w)
        : BASE(w)
    {}
    OT(OT const& r)
        : BASE(r.val_)
    {}
 @endcode
 */
#define BOOST_OPAQUE_FORWARD_CONSTRUCTORS(OT,BASE) \
    OT(){} \
    template <typename W> \
    explicit OT(W w) \
        : BASE(w) \
    {}\
    OT(OT const& r) \
        : BASE(r.val_) \
    {}


/**
 Specialize inherited_from_underlying for the type @ OT just inheriting the ones from its underlying type.

 @Note This macro can be used only outside a namespace.

 @Params
 @Param{OT, the opaque type}

 @Result
 @code
 namespace boost {
   namespace opaque {
    template <typename Bool>
    struct inherited_from_underlying<OT,Bool>
      : inherited_from_underlying<typename OT::underlying_type,Bool> { };
   }
 }
 @endcode
 */
#define BOOST_OPAQUE_INHERIT_FROM_UNDERLYING(OT) \
namespace boost {\
namespace opaque {\
  template <typename Bool>\
  struct inherited_from_underlying<OT,Bool>\
    : inherited_from_underlying<typename OT::underlying_type,Bool> { };\
} \
}

#if !defined(BOOST_OPAQUE_DOXYGEN_INVOKED)

#define BOOST_OPAQUE_EXT_PUBLIC_TYPEDEF(UT, OT, B) \
  struct BOOST_JOIN(OT, _tag) {};\
  typedef boost::opaque::public_opaque_type<UT, BOOST_JOIN(OT, _tag), B> OT

#endif
/**
 Declares a @c public_opaque_type typedef @c OT defining a specific tag @c OT_tag having @c boost::opaque::boolean as <em>Boolean</em> type.

 @Note This macro must be used inside the @c OT's namespace.

 @Params
 @Param{UT, the underlying type}
 @Param{OT, the opaque type}

 @Result
 @code
 struct OT_tag {};
 typedef boost::opaque::public_opaque_type<UT, OT_tag, boost::opaque::boolean> OT
 @endcode
 */
#define BOOST_OPAQUE_BOOLEAN_PUBLIC_TYPEDEF(UT, OT) \
BOOST_OPAQUE_EXT_PUBLIC_TYPEDEF(UT, OT, boost::opaque::boolean)

/**
 Declares a @c public_opaque_type typedef @c OT defining a specific tag @c OT_tag  having @c bool as <em>Boolean</em> type.

 @Note This macro must be used inside the @c OT's namespace.

 @Params
 @Param{UT, the underlying type}
 @Param{OT, the opaque type}

 @Result
 @code
 struct OT_tag {};
 typedef boost::opaque::public_opaque_type<UT, OT_tag, bool> OT
 @endcode
 */
#define BOOST_OPAQUE_PUBLIC_TYPEDEF(UT, OT) \
BOOST_OPAQUE_EXT_PUBLIC_TYPEDEF(UT, OT, bool)

//////////////////////////
#if !defined(BOOST_OPAQUE_DOXYGEN_INVOKED)

#define BOOST_OPAQUE_EXT_PUBLIC_CLASS(UT, NT1, B) \
  struct NT1 : boost::opaque::public_opaque_class<NT1, UT,B> \
  { \
    BOOST_OPAQUE_FORWARD_CONSTRUCTORS(NT1, (boost::opaque::public_opaque_class<NT1, UT,B>)) \
  }

#endif

/**
 Declares a @c public_opaque_class @c OT having @c boost::opaque::boolean as <em>Boolean</em> type.

 @Note This macro must be used inside the OT's namespace.

 @Params
 @Param{UT, the underlying type}
 @Param{OT, the opaque type}

 @Result
 @code
 struct NT1 : boost::opaque::public_opaque_class<NT1, UT,boost::opaque::boolean>
 {
    typedef boost::opaque::public_opaque_class<NT1, UT,boost::opaque::boolean> base_type;
    OT(){}
    template <typename W>
    explicit OT(W w)
        : base_type(w)
    {}
    OT(OT const& r)
        : base_type(r.val_)
    {}
 }
 @endcode
 */
#define BOOST_OPAQUE_BOOLEAN_PUBLIC_CLASS(UT, OT) \
  BOOST_OPAQUE_EXT_PUBLIC_CLASS(UT, OT, boost::opaque::boolean)


/**
 Declares a @c public_opaque_class @c OT having @c bool as <em>Boolean</em> type.

 @Note This macro must be used inside the OT's namespace.

 @Params
 @Param{UT, the underlying type}
 @Param{OT, the opaque type}

 @Result
 @code
 struct NT1 : boost::opaque::public_opaque_class<NT1, UT, bool>
 {
    typedef boost::opaque::public_opaque_class<NT1, UT,bool> base_type;
    OT(){}
    template <typename W>
    explicit OT(W w)
        : base_type(w)
    {}
    OT(OT const& r)
        : base_type(r.val_)
    {}
 }
 @endcode
 */
#define BOOST_OPAQUE_PUBLIC_CLASS(UT, OT) \
  BOOST_OPAQUE_EXT_PUBLIC_CLASS(UT, OT, bool)

//////////////////////////
#define BOOST_OPAQUE_PRIVATE_FORWARD_CONSTRUCTORS(UT, OT) \
    BOOST_OPAQUE_FORWARD_CONSTRUCTORS(OT,(boost::opaque::private_opaque_class<OT, UT>))

#define BOOST_OPAQUE_PRIVATE_OPERATIONS(UT, OT) \
    BOOST_OPAQUE_PRIVATE_FORWARD_CONSTRUCTORS(UT, OT)

//////////////////////////
#if !defined(BOOST_OPAQUE_DOXYGEN_INVOKED)

#define BOOST_OPAQUE_EXT_PRIVATE_TYPEDEF(UT, OT,B) \
  struct BOOST_JOIN(OT, _tag) {};\
  typedef boost::opaque::private_opaque_type<UT, BOOST_JOIN(OT, _tag),B> OT

#endif

/**
 Declares a @c private_opaque_type typedef @c OT defining a specific tag @c OT_tag  having @c bool as <em>Boolean</em> type.

 @Note This macro must be used inside the OT's namespace.

 @Params
 @Param{UT, the underlying type}
 @Param{OT, the opaque type}

 @Result
 @code
 struct OT_tag {};
 typedef boost::opaque::private_opaque_type<UT, OT_tag, boost::opaque::boolean> OT
 @endcode
 */
#define BOOST_OPAQUE_BOOLEAN_PRIVATE_TYPEDEF(UT, OT) \
  BOOST_OPAQUE_EXT_PRIVATE_TYPEDEF(UT, OT, boost::opaque::boolean)

/**
 Declares a @c private_opaque_type typedef @c OT defining a specific tag @c OT_tag  having @c bool as <em>Boolean</em> type.

 @Note This macro must be used inside the OT's namespace.

 @Params
 @Param{UT, the underlying type}
 @Param{OT, the opaque type}

 @Result
 @code
 struct OT_tag {};
 typedef boost::opaque::private_opaque_type<UT, OT_tag, bool> OT
 @endcode
 */
#define BOOST_OPAQUE_PRIVATE_TYPEDEF(UT, OT) \
  BOOST_OPAQUE_EXT_PRIVATE_TYPEDEF(UT, OT, bool)

#if !defined(BOOST_OPAQUE_DOXYGEN_INVOKED)

#define BOOST_OPAQUE_EXT_PRIVATE_CLASS(UT, NT1, B) \
struct NT1 : boost::opaque::private_opaque_class<NT1, UT,B> \
{ \
    typedef boost::opaque::private_opaque_class<NT1, UT, B> base_type; \
    BOOST_OPAQUE_FORWARD_CONSTRUCTORS(NT1, (boost::opaque::private_opaque_class<NT1, UT,B>)) \
}

#endif

/**
 Declares a @c private_opaque_class @c OT having @c boost::opaque::boolean as <em>Boolean</em> type.

 @Note This macro must be used inside the OT's namespace.

 @Params
 @Param{UT, the underlying type}
 @Param{OT, the opaque type}

 @Result
 @code
 struct NT1 : boost::opaque::private_opaque_class<NT1, UT, boost::opaque::boolean>
 {
    typedef boost::opaque::private_opaque_class<NT1, UT,boost::opaque::boolean> base_type;
    OT(){}
    template <typename W>
    explicit OT(W w)
        : base_type(w)
    {}
    OT(OT const& r)
        : base_type(r.val_)
    {}
 }
 @endcode
 */

#define BOOST_OPAQUE_BOOLEAN_PRIVATE_CLASS(UT, OT) \
  BOOST_OPAQUE_EXT_PRIVATE_CLASS(UT, OT, boost::opaque::boolean)

/**
 Declares a @c private_opaque_class @c OT having @c bool as <em>Boolean</em> type.

 @Note This macro must be used inside the OT's namespace.

 @Params
 @Param{UT, the underlying type}
 @Param{OT, the opaque type}

 @Result
 @code
 struct NT1 : boost::opaque::private_opaque_class<NT1, UT, bool>
 {
    typedef boost::opaque::private_opaque_class<NT1, UT,bool> base_type;
    OT(){}
    template <typename W>
    explicit OT(W w)
        : base_type(w)
    {}
    OT(OT const& r)
        : base_type(r.val_)
    {}
 }
 @endcode
 */
#define BOOST_OPAQUE_PRIVATE_CLASS(UT, OT) \
  BOOST_OPAQUE_EXT_PRIVATE_CLASS(UT, OT, bool)

#endif

