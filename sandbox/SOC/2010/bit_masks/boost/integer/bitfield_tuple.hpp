//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_BITFIELD_TUPLE_HPP
#define BOOST_BITFIELD_TUPLE_HPP
#include <boost/integer/details/storage.hpp>
#include <boost/integer/details/member.hpp>
#include <cstddef>
#include <boost/mpl/void.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/map.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>


namespace boost {
namespace details {






/** This is the type which sits inside the mpl vector type.
 *  This has all information for constructing a bitfield.
 */
template <  typename ReturnType,
            typename NameType, 
            typename Offset,
            typename FieldWidth
>
struct bitfield_element_ {
    typedef ReturnType  return_type;
    typedef NameType    name_type;
    typedef Offset      offset;
    typedef FieldWidth  field_width;
    typedef bitfield_element_<return_type, name_type, offset, field_width> type;
};




/** Default case for managing template parameters. */
template <  typename Param,
            typename StoragePolicy,
            typename FieldVector,
            typename Offset
>
struct bft_impl_;
#if 0
{
    typedef Param           param;
    typedef FieldVector     field_vector;
    typedef StoragePolicy   storage_policy;
    typedef Offset          offset;

    typedef bft_impl_<param,storage_policy,field_vector,offset> type;

    template <typename NextParam>
    struct process {
        typedef typename bft_impl_<
            NextParam,
            storage_policy,
            field_vector,
            offset
        >::type type;
    };
};
#endif

/** Specialization over mpl::void_. */
template <  typename StoragePolicy,
            typename FieldVector,
            typename Offset
>
struct bft_impl_ <mpl::void_, StoragePolicy, FieldVector, Offset>{
    typedef mpl::void_           param;
    typedef FieldVector     field_vector;
    typedef StoragePolicy   storage_policy;
    typedef Offset          offset;

    typedef bft_impl_<param,storage_policy,field_vector,offset> type;

    template <typename NextParam>
    struct process {
        typedef typename bft_impl_<
            NextParam,
            storage_policy,
            field_vector,
            offset
        >::type type;
    };
};

/** Specilization for storage type. */
template <  typename StorageType, 
            typename AllocationPolicy,
            typename StoragePolicy,
            typename FieldVector,
            typename Offset
>
struct bft_impl_ <
    storage<
        StorageType,
        AllocationPolicy
    >,
    StoragePolicy,
    FieldVector,
    Offset >
{
    typedef typename storage<
        StorageType,
        AllocationPolicy
    >::type                 param;
    typedef FieldVector     field_vector;
    typedef param           storage_policy;
    typedef Offset          offset;

    typedef bft_impl_<param,storage_policy,field_vector,offset> type;

    template <typename NextParam>
    struct process {
        typedef typename bft_impl_<
            NextParam,
            storage_policy,
            field_vector,
            offset
        >::type type;
    };
};

/** Specilization for member. */
template <  typename StoragePolicy,
            typename FieldVector,
            typename Offset,
            typename ReturnType,
            typename NameType,
            std::size_t FieldWidth
>
struct bft_impl_ <
    member<
        ReturnType,
        NameType,
        FieldWidth
    >,
    StoragePolicy,
    FieldVector,
    Offset >
{
    typedef member< ReturnType, NameType, FieldWidth > param;

    // typedef 
    typedef StoragePolicy   storage_policy;
    typedef typename mpl::push_back<
        FieldVector,
        bitfield_element_<
            ReturnType,
            NameType,
            Offset,
            typename mpl::size_t< FieldWidth >
        >
    >::type field_vector;
    typedef mpl::size_t< Offset::value + FieldWidth > offset;

    typedef bft_impl_<param,storage_policy,field_vector,offset> type;

    template <typename NextParam>
    struct process {
        typedef typename bft_impl_<
            NextParam,
            storage_policy,
            field_vector,
            offset
        >::type type;
    };
};

} // end details


template <  typename T0,
            typename T1 = mpl::void_,
            typename T2 = mpl::void_,
            typename T3 = mpl::void_,
            typename T4 = mpl::void_,
            typename T5 = mpl::void_,
            typename T6 = mpl::void_,
            typename T7 = mpl::void_,
            typename T8 = mpl::void_,
            typename T9 = mpl::void_
>
struct bitfield_tuple
{
    typedef typename details::bft_impl_<T0,
            mpl::void_,
            mpl::vector<>,
            mpl::size_t<0>
        >::
        template process<T1>::type::
        template process<T2>::type::
        template process<T3>::type::
        template process<T4>::type::
        template process<T5>::type::
        template process<T6>::type::
        template process<T7>::type::
        template process<T8>::type::
        template process<T9>::type      processed_args;


};  



} // end boost

#endif
