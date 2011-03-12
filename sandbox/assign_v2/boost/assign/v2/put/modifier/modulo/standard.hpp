//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_ER_2010_HPP
#define BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_ER_2010_HPP
#include <boost/assign/v2/detail/keyword/ignore.hpp>
#include <boost/assign/v2/put/frame/modifier.hpp>
#include <boost/assign/v2/put/modifier/modulo/keyword.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_IMPL_PTR(FUN)\
    template<typename C, typename T>\
    void impl(C& cont, T* t)const{\
    cont.FUN( t );\
}\
/**/
#define BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_IMPL_LVALUE(FUN)\
    template<typename C, typename T>\
    void impl(C& cont, T& t)const{\
    cont.FUN( t );\
}\
/**/

#include <boost/assign/v2/detail/config/enable_cpp0x.hpp>
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
#include <utility>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_reference.hpp>
// disable_if necessary to avoid ambiguity resolution with GCC4.4
#define BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_IMPL_RVALUE(FUN)\
    template<typename C, typename T>\
        typename boost::disable_if<\
        boost::is_reference<T>,\
        void\
    >::type\
    impl(C& cont, T&& t)const{\
        cont.FUN( std::move( t ) );\
    }\
/**/
#define BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_IMPL(FUN)\
BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_IMPL_LVALUE(FUN)\
BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_IMPL_RVALUE(FUN)\
/**/
#else
#define BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_IMPL(FUN)\
BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_IMPL_LVALUE(FUN)\
/**/
#endif // BOOST_ASSIGN_V2_ENABLE_CPP0X

#define BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_TAG(FUN)\
namespace boost{\
namespace assign{\
namespace v2{\
namespace modifier_tag{ struct FUN{}; }\
}\
}\
}\
/**/

// Must be preceded by BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_TAG(FUN)
#define BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD(FUN)\
namespace boost{\
namespace assign{\
namespace v2{\
namespace put_aux{\
\
    template<>\
    class modifier<modifier_tag::FUN>\
    {\
        typedef keyword_aux::ignore ignore_;\
        public:\
        modifier(){}\
        modifier( ignore_, ignore_ ){}\
        BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_IMPL(FUN)\
    };\
\
}\
namespace{\
\
    put_aux::modulo_modifier<put_aux::keyword_modifier, modifier_tag::FUN> const\
        BOOST_PP_CAT(_,FUN) = ( \
        _modifier = modifier_tag::FUN() \
    );\
\
}\
}\
}\
}\
/**/

#endif // BOOST_ASSIGN_V2_PUT_MODIFIER_MODULO_STANDARD_ER_2010_HPP
