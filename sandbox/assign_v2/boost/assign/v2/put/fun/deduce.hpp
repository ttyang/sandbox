//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_PUT_FUN_DEDUCE_ER_2010_HPP
#define BOOST_ASSIGN_V2_PUT_FUN_DEDUCE_ER_2010_HPP
#include <boost/assign/v2/detail/traits/container/is_ptr_container.hpp>
#include <boost/assign/v2/detail/traits/container/value.hpp>
#include <boost/assign/v2/detail/functor/constructor.hpp>
#include <boost/assign/v2/detail/functor/new.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost{
namespace assign{
namespace v2{
//[syntax_put_fun_deduce
namespace put_aux{

    template<typename /*<<Pointer-container>>*/C>
    struct /*<<Meta-function mapping the `C`'s pointer-type to a factory thereof>>*/ deduce_fun_pointer/*<-*/
    {
        typedef typename v2::container_traits::value<C>::type value_type;
        typedef functor_aux::new_<value_type> type;
    }/*->*/;

    template<typename /*<<Value-container>>*/C>
    struct /*<<Meta-function mapping `C`'s value-type to a factory thereof>>*/ deduce_fun_value/*<-*/
    {
        typedef typename v2::container_traits::value<C>::type value_type;
        typedef functor_aux::constructor<value_type> type;
    }/*->*/;

    template<typename /*<<Either of a value or pointer-container>>*/C>
    struct /*<<Meta-function mapping `C`s element-type to a factory thereof>>*/deduce_fun/*<-*/
        :  boost::mpl::eval_if<
            container_traits::is_ptr_container<C>,
            deduce_fun_pointer<C>,
            deduce_fun_value<C>
        >
    {}/*->*/;

}// put_aux
//]
}// v2
}// assign
}// boost

#endif // BOOST_ASSIGN_V2_PUT_FUN_DEDUCE_ER_2010_HPP
