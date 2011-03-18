//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_VALUE_DEQUE_CSV_DEQUE_ER_2010_HPP
#define BOOST_ASSIGN_V2_VALUE_DEQUE_CSV_DEQUE_ER_2010_HPP
#include <boost/assign/v2/detail/config/enable_cpp0x.hpp>
#include <boost/assign/v2/detail/pp/ignore.hpp>
#include <boost/assign/v2/value/deque/deque.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
#include <utility>
#endif

namespace boost{
namespace assign{
namespace v2{
namespace value_aux{

    template<typename T>
    struct csv_deque_value : boost::decay<
        typename boost::remove_cv<T>::type
    >{};

namespace result_of{

    template<typename T>
    struct csv_deque: result_of::deque<
        typename csv_deque_value<T>::type
    >{};

}// result_of
}// value_aux
//[syntax_put_deque_csv_deque

    template<typename T>
    struct csv_deque_value/*<-*/
        : value_aux::csv_deque_value<T>
    {}/*->*/;

namespace result_of{

    template<typename T>
    struct csv_deque/*<-*/
        : value_aux::result_of::csv_deque<T>
    {}/*->*/;

}// result_of
//<-
#if BOOST_ASSIGN_V2_ENABLE_CPP0X
namespace value_aux{

    template<typename T, typename R>
    void csv_deque_impl(R& r){}

    template<typename T, typename R, typename...Args>
    void csv_deque_impl(R& r, T const& t, Args&&...args)
    {
        r( t );
        csv_deque_impl<T>(r, std::forward<Args>( args )... );
    }
//->

    template<typename T, typename... Args>
    typename result_of::csv_deque<T>::type
    csv_deque(const T& t, Args const& ...  args)/*<-*/
    {
        typename result_of::csv_deque<T>::type result;
        csv_deque_impl<T>(result, t, args...);
        return result;
    }BOOST_ASSIGN_V2_IGNORE(/*->*/;/*<-*/)/*->*/

//]
}// value_aux

using value_aux::csv_deque;

#endif // BOOST_ASSIGN_V2_ENABLE_CPP0X

}// v2
}// assign
}// boost

#if !BOOST_ASSIGN_V2_ENABLE_CPP0X
#include <boost/assign/v2/value/deque/cpp03/csv_deque.hpp>
#endif


#endif // BOOST_ASSIGN_V2_VALUE_DEQUE_CSV_DEQUE_ER_2010_HPP