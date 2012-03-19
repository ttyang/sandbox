/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_OVERLOAD_GET_SIGNATURE_HPP_
#define _BOOST_OVERLOAD_GET_SIGNATURE_HPP_


#include <boost/type_traits/remove_pointer.hpp>
#include <boost/typeof/typeof.hpp>

#include "member_function_trait.hpp"
#include "get_function_tag.hpp"


namespace boost{ namespace overloads{ namespace detail{


template< typename Functor,
          typename function_tag
                = typename get_function_tag<Functor>::type
>
struct get_signature
{
};

template< typename FunctionPtr>
struct get_signature<FunctionPtr, function_ptr_tag>
{
      typedef typename remove_pointer<FunctionPtr>::type type;
};

template< typename MemberPtr>
struct get_signature<MemberPtr, member_ptr_tag>
{
    typedef
        typename memb_func_trait<MemberPtr>::binded_type
        binded_type;
    typedef
        typename memb_func_trait<MemberPtr>::const_binded_type
        const_binded_type;
    BOOST_STATIC_CONSTANT( bool, const_qualified
        = (memb_func_trait<MemberPtr>::const_qualified) );

    typedef typename if_c<const_qualified, const_binded_type, binded_type>::type
            type;
};

template< typename FunctionObj >
struct get_signature<FunctionObj, function_obj_tag>
{
    typedef BOOST_TYPEOF_TPL(&FunctionObj::operator()) call_op_ptr;
    typedef typename memb_func_trait<call_op_ptr>::sig_type type;
};

template< typename FunctionObj >
struct get_signature<boost::reference_wrapper<FunctionObj>, function_obj_ref_tag>
{
    typedef typename get_signature<FunctionObj>::type type;
};

template< typename Signature >
struct get_signature<boost::function<Signature>, function_obj_tag>
{
    typedef Signature type;
};


} } } // end namespaces


#endif // _BOOST_OVERLOAD_GET_SIGNATURE_HPP_
