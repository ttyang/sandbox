//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_ASSIGN_V2_DETAIL_TRAITS_CONTAINER_ER_2010_HPP
#define BOOST_ASSIGN_V2_DETAIL_TRAITS_CONTAINER_ER_2010_HPP
#include <boost/assign/v2/detail/traits/aux_/fwd_container.hpp>
#include <boost/assign/v2/detail/traits/aux_/ptr_container.hpp>
#include <boost/assign/v2/detail/traits/aux_/value_container.hpp>
#include <boost/config.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost{
namespace assign{
namespace v2{
namespace container_aux{

// HELPER

    template<template<typename > class F, typename C>
    struct through_value_container
        : F<
            typename to_value_container<C>::type
        >
    {};

// DATA-MEMBER

    template<typename C>
    struct key : through_value_container<value_key, C>{};

    template<typename C>
    struct mapped : through_value_container<value_mapped, C>{};

    template<typename C>
    struct value : through_value_container<value_value, C>{};

// STORAGE

    template<typename C>
    struct is_ptr_container : ::boost::mpl::not_<
        boost::is_same<C, typename to_value_container<C>::type>
    >{};

// MEMBERS

    template<typename C>
    struct has_push_deduced_value
        : through_value_container<value_has_push_deduced_value, C>
    {};

// CATEGORY

    template<typename C> struct is_array
        : through_value_container<value_is_array, C>
    {};

    template<typename C>
    struct is_associative 
        : through_value_container<value_is_associative, C>
    {};

    template<typename C>
    struct is_fifo 
        : through_value_container<value_is_fifo, C>
    {};
    
    template<typename C>
    struct is_lifo 
        : through_value_container<value_is_lifo, C>
    {};
            
    template<typename C> struct is_map 
        : through_value_container<value_is_map, C>
    {};
    
    template<typename C>
    struct is_sorted 
        : through_value_container<value_is_sorted, C>
    {};

}// container_aux

    template<typename C>
    struct value_container_value/*<-*/
        : container_aux::value<C>{}
    /*->*/;

}// v2
}// assign
}// boost


#endif // BOOST_ASSIGN_V2_DETAIL_TRAITS_CONTAINER_ER_2010_HPP
