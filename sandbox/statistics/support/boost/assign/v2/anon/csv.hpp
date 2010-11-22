//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_ANON_CSV_ER_2010_HPP
#define BOOST_ASSIGN_V2_ANON_CSV_ER_2010_HPP
#include <boost/assign/v2/detail/keyword/nil.hpp>
#include <boost/assign/v2/anon/make.hpp>
#include <boost/assign/v2/anon/cont.hpp>
#include <boost/assign/v2/detail/config/enable_cpp0x.hpp>
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
#include <utility>
#else
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/assign/v2/detail/config/limit_csv_arity.hpp>
#endif

namespace boost{
namespace assign{
namespace v2{
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
namespace csv_anon_aux{

	template<typename T,typename R>
    void impl(R& r){}

	template<typename T, typename R,typename...Args>
    void impl(
        R& r,
        T const& t,
        Args&&...args
    )
    {
        r( t );
        csv_anon_aux::impl<T>(r, std::forward<Args>( args )... );
    }

}//csv_anon_aux

	template<typename T,typename... Args>
    typename result_of::anon<T>::type
    // implicit conversion to T desired
    csv_anon(const T& t, Args const& ...  args)
    {
        typedef typename result_of::anon<T>::type result_;
        result_ result = anon<T>( v2::_nil );
        csv_anon_aux::impl<T>(result, t, args...);
        return result;
    }

#else
#define MACRO1(z, i, data) ( BOOST_PP_CAT(_, i) )
#define MACRO2(z, N, data)\
	template<typename T>\
    typename result_of::anon<T>::type\
    csv_anon( BOOST_PP_ENUM_PARAMS(N, T const & _) )\
    {\
        return anon<T>( v2::_nil) BOOST_PP_REPEAT(N, MACRO1, ~ );\
    }\
/**/
BOOST_PP_REPEAT_FROM_TO(
	1,
    BOOST_PP_INC(BOOST_ASSIGN_V2_LIMIT_CSV_ARITY),
    MACRO2,
    ~
)
#undef MACRO1
#undef MACRO2
#endif

}// v2
}// assign
}// boost

#endif
