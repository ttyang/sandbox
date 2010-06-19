//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_BITFIELD_TUPLE_bft_arg_parse_implHPP
#define BOOST_BITFIELD_TUPLE_bft_arg_parse_implHPP
#include <boost/mpl/vector.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/integer/details/bft/name_lookup.hpp>


namespace boost { namespace details {



/** This is the empty which prevents the user from supply things which are
 *  not enclosed within either a member template or a storage template.
 *  This enforces a domain requirement on the template parameters of
 *  bitfield_tuple.
 */
template <  typename Param,
            typename StoragePolicy,
            typename FieldVector,
            typename Offset
> struct bft_arg_parse_impl;


/** Specialization over mpl::void_. */
template <  typename StoragePolicy,
            typename FieldVector,
            typename Offset
>
struct bft_arg_parse_impl <mpl::void_, StoragePolicy, FieldVector, Offset>{
    typedef mpl::void_           param;
    typedef FieldVector     field_vector;
    typedef StoragePolicy   storage_policy;
    typedef Offset          offset;

    typedef bft_arg_parse_impl<param,storage_policy,field_vector,offset> type;

    template <typename NextParam>
    struct process {
        typedef bft_arg_parse_impl<
            NextParam,
            storage_policy,
            field_vector,
            offset
        > type;
    };
};

/** Specilization for storage type.
 *  Preconditions enforced on this function :
 *      For now its going to be documented but not enforeced.
 *      Do NOT set the storage type more then once!
 */
template <  typename StorageType, 

            typename StoragePolicy,
            typename FieldVector,
            typename Offset
>
struct bft_arg_parse_impl <
    storage<StorageType>,
    StoragePolicy,
    FieldVector,
    Offset >
{
    // make sure that the storage type is not specifed twice
    BOOST_STATIC_ASSERT(( is_same<StoragePolicy,mpl::void_>::value ));

    typedef typename storage<
        StorageType
    >::type                 param;
    typedef FieldVector     field_vector;
    typedef param           storage_policy;
    typedef Offset          offset;

    typedef bft_arg_parse_impl<param,storage_policy,field_vector,offset> type;

    template <typename NextParam>
    struct process {
        typedef bft_arg_parse_impl<
            NextParam,
            storage_policy,
            field_vector,
            offset
        > type;
    };
};

/** Specilization for member.
 *  Documented and enforced preconditions
 *      1. The user must not supply the same name for more then 1 parameter
 *      (This may result in additional overhead during compile time ).
 */
template <  typename StoragePolicy,
            typename FieldVector,
            std::size_t FieldWidth,
            typename ReturnType,
            typename NameType,
            typename Offset
>
struct bft_arg_parse_impl <
    member <
        ReturnType,
        NameType,
        FieldWidth
    >,
    StoragePolicy,
    FieldVector,
    Offset >
{

    BOOST_STATIC_ASSERT((
        is_same<
            typename mpl::find_if<
                FieldVector,
                details::match_name<
                    typename mpl::_1,
                    NameType
                >
            >::type,
            typename mpl::end<
                FieldVector
            >::type
        >::value            
    ));


    typedef member< ReturnType, NameType, FieldWidth > param;

    // typedef 
    typedef StoragePolicy   storage_policy;
    typedef typename mpl::push_back<
        FieldVector,
        bitfield_element<
            ReturnType,
            NameType,
            Offset,
            mpl::size_t<FieldWidth>
        >
    >::type field_vector;

    typedef mpl::size_t< 
        mpl::plus<
            Offset,
            mpl::size_t<FieldWidth>
        >::value
    >                                   offset;

    typedef bft_arg_parse_impl<param,storage_policy,field_vector,offset> type;

    template <typename NextParam>
    struct process {
        typedef bft_arg_parse_impl<
            NextParam,
            storage_policy,
            field_vector,
            offset
        > type;
    };
};

}} // end boost::details

#endif
