//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_PUT_DEQUE_MODULO_ER_2010_HPP
#define BOOST_ASSIGN_V2_PUT_DEQUE_MODULO_ER_2010_HPP
#include <boost/assign/v2/put/modulo/fun.hpp>
#include <boost/assign/v2/put/modulo/modifier.hpp>
#include <boost/assign/v2/put/deque/fwd.hpp>

namespace boost{
namespace assign{
namespace v2{
namespace result_of_modulo{

    template<typename T,typename F,typename Tag>
    struct fun<put_deque_aux::cont<T, F, Tag> >
    {
        template<typename F1>
        struct apply{ typedef put_deque_aux::cont<T, F1, Tag> type; };
    };

    template<typename T,typename F, typename Tag>
    struct modifier<put_deque_aux::cont<T, F, Tag> >
    {
        template<typename Tag1>
        struct apply{ typedef put_deque_aux::cont<T, F, Tag1> type; };
    };

}// result_of_modulo
}// v2
}// assign
}// boost

#endif