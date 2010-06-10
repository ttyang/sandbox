//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_BITFIELD_TUPLE_HPP
#define BOOST_BITFIELD_TUPLE_HPP
#include <boost/integer/details/storage.hpp>

#include <boost/integer/details/member.hpp>
#include <boost/integer/bit_width.hpp>
#include <cstddef>
#include <boost/mpl/void.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/map.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>


// TODO: Remove me.
#include <iostream>
#include <boost/mpl/empty.hpp>

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


template <typename ReturnType, typename Name, typename FieldWidth>
struct parsible_member_elem_ {
    typedef ReturnType return_type;
    typedef Name name_type;
    typedef FieldWidth field_width;
    typedef parsible_member_elem_<ReturnType,Name,FieldWidth> type;
};



/** This is the empty which prevents the user from supply things which are
 *  not enclosed within either a member template or a storage template.
 *  This enforces a domain requirement on the template parameters of
 *  bitfield_tuple.
 */
template <  typename Param,
            typename StoragePolicy,
            typename FieldVector,
            typename Offset
> struct bft_impl_;


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
        typedef bft_impl_<
            NextParam,
            storage_policy,
            field_vector,
            offset
        > type;
    };


    static void debug_info() {
        using namespace std;
        cout << "bft_impl_ <mpl::void_, StoragePolicy, FieldVector, Offset>" << endl;
        cout << "Offset Value: " << Offset::value << endl;
        cout << "offset Value: " << offset::value << endl;
    }
};

/** Specilization for storage type.
 *  Preconditions enforced on this function :
 *      For now its going to be documented but not enforeced.
 *      Do NOT set the storage type more then once!
 */
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
        typedef bft_impl_<
            NextParam,
            storage_policy,
            field_vector,
            offset
        > type;
    };

    static void debug_info() {
        using namespace std;
        cout << "bft_impl_ <storage<StorageType,AllocationPolicy>,StoragePolicy,FieldVector,Offset >" << endl;
        cout << "Offset Value: " << Offset::value << endl;
        cout << "offset Value: " << offset::value << endl;
    }
};

/** Specilization for member.
 *  Documented and enforced preconditions
 *      1. The user must not supply the same name for more then 1 parameter
 *      (This may result in additional overhead during compile time ).
 *      Currently not enforced, will take more time then I have at the moment.
 */

// TODO: Implement Precondition 1 listed above!
template <  typename StoragePolicy,
            typename FieldVector,
            std::size_t FieldWidth,
            typename ReturnType,
            typename NameType,
            typename Offset
>
struct bft_impl_ <
    member <
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
            mpl::size_t<FieldWidth>
        >
    >::type field_vector;

    typedef mpl::size_t< 
        mpl::plus<
            Offset,
            mpl::size_t<FieldWidth>
        >::value
    >                                   offset;

    typedef bft_impl_<param,storage_policy,field_vector,offset> type;

    template <typename NextParam>
    struct process {
        typedef bft_impl_<
            NextParam,
            storage_policy,
            field_vector,
            offset
        > type;
    };

    static void debug_info() {
        using namespace std;
        cout << "bft_impl_ <member<ReturnType,NameType,FieldWidth>,StoragePolicy,FieldVector,Offset >" << endl;
        cout << "Offset Value: " << Offset::value << endl;
        cout << "offset Value: " << offset::value << endl;
        cout << "FieldWidth Value: " << FieldWidth << endl;
        cout << "mpl::size_t<FieldWidth> Value: " << mpl::size_t< FieldWidth >::value << endl;
    }
};

/** This structure is going to be used when an allocator isn't assked for.
 *  This means that the entire class is allocated on the stack.
 */
template <typename T>
struct stack_alloc_base_policy {
    /** Default Constructor. */
    stack_alloc_base_policy()
        :_data()
    { }

    /** Copy constructor. */
    stack_alloc_base_policy( stack_alloc_base_policy<T> const& x )
        :_data( x._data )
    { }
    
    /** Value constructor. */
    stack_alloc_base_policy( T x )
        :_data( x )
    { }
    
    stack_alloc_base_policy<T> const& operator=( stack_alloc_base_policy const& x ) {
        _data  =  x._data;
        return *this;
    }

    /** get_data () this function exists within this class and the 
     *      allocator_base_policy.
     *  Returns a copy of _data.
     */
    //@{
    T const get_data() const { return _data; }
    T get_data() { return _data; }
    //@}

    T _data;
};

/** This isn't implemented yet and shouldn't be used just yet.
 *  This is eventually going to wrap up an pointer to an allocated object which
 *  will be retrievable via a alloc_get function.
 */
template <typename T, typename Alloc>
struct allocator_wraper_base_policy {
    T const get_data() const { return _data; }
    T get_data() { return _data; }
    T _data;
};

// Only used for writing clarity and only used once and then undef'ed when
// before the end of the details namespace/after the end of the
// bitfield_tuple_base



/** Used for fixing member arguments by projecting numbers into the type
 *  system.
 */
template <typename T>
struct fix_args;

template <>
struct fix_args <mpl::void_> {
    typedef mpl::void_ apply;
};

template <typename ReturnType, typename NameType, std::size_t FieldWidth>
struct fix_args <
    member<
        ReturnType,
        NameType, 
        FieldWidth
    > >
{
    typedef parsible_member_elem_<
        ReturnType,
        NameType,
        typename mpl::size_t<FieldWidth>
    > apply;
};

template <typename StorageType, typename AllocType>
struct fix_args <
    storage<
        StorageType,
        AllocType
    > >
{
    typedef storage<StorageType,AllocType> apply;
};


#define BOOST_BFT_ARG_PROCESSING_CLASS      \
        details::bft_impl_<\
            T0, \
            mpl::void_,\
            mpl::vector<>,\
            mpl::size_t<0u>\
        >::\
        template process<T1 >::type::\
        template process<T2>::type::\
        template process<T3>::type::\
        template process<T4>::type::\
        template process<T5>::type::\
        template process<T6>::type::\
        template process<T7>::type::\
        template process<T8>::type::\
        template process<T9>::type 

/** bitfield_tuple base class
 *  This class is responsible for preforming static assertions and dealing with
 *  the parsing of arguments.
 *
 *  Base Class preconditions.
 *
 *  1) Storage policy must not be set to mpl::void_.
 *      (this means that the user didn't specify a stroage policy.)
 *      Enforced, May be removed at a later time when the class is able to 
 *          deduce the ammount of storage space, and set the storage policy to
 *          that.
 *
 *  2) The storage type must be a POD type.
 *      (This may be changed to possibly allow for array types of PODs.)
 *      Enforced, This may be best suited to being part of the unpacking
 *          of the arguments so that it can be caught earlier then inside the 
 *          base class.
 *
 *  3) The bitfields specified must not exceed the bitwidth of the storage type.
 *      Enforced. Not going any where, but may be redefined or altered based
 *          on if I allow the supplied storage type to be an array.
 *
 *
 *
 *
 *
 */
template <  typename T0,
            typename T1,
            typename T2,
            typename T3,
            typename T4,
            typename T5,
            typename T6,
            typename T7,
            typename T8,
            typename T9
>
struct bitfield_tuple_base
    : BOOST_BFT_ARG_PROCESSING_CLASS
{

    
    typedef typename BOOST_BFT_ARG_PROCESSING_CLASS   processed_args;

    // extracting te Arguments from processed_args relating to 
    // the storage policy. Also preforming static assertios 
    // where they can be done.
    typedef typename processed_args::storage_policy     storage_policy;
    typedef typename processed_args::field_vector       field_vector;
    typedef typename processed_args::offset             offset;

    // Precondition:
    //      A storage policy must be supplied.
    BOOST_STATIC_ASSERT((
        !is_same<
            storage_policy,
            typename mpl::void_
        >::value
    ));

    typedef typename storage_policy::storage_type   storage_type;

    // this is only defined if the storage type is a type that is not the
    // storage_policy_stack which makes this class simple use a stack to
    // allocate its storage. This leaves an option for the user to select an
    // allocator. 
    typedef typename mpl::if_<
        is_same<
            typename storage_policy::alloc,
            storage_policy_stack
        >,
        typename mpl::void_,
        storage_policy
        >::type                                     allocator;

    // get the template to be used as base class so that the bitfield_tuple
    // class itself can inherit from it.
    typedef typename mpl::if_<
            is_same<
                allocator,
                mpl::void_
            >,
            stack_alloc_base_policy<storage_type>,
            allocator_wraper_base_policy< storage_type, allocator >
        >::type                                     allocation_base_policy;



    // precondition: the storage type must be a pod type (for now).
    // NOTE: this may become a documented requirement only.
    BOOST_STATIC_ASSERT(( is_pod<storage_type>::value ));

    // Precondition: the offet at the end of everything must be the
    // the same as or less then the bit_width of the storage type.
    BOOST_STATIC_ASSERT((
        offset::value
            <=
        bit_width< storage_type >::value + 1
    ));

    /** Meta-calculations used for enabling and disabling functionality based
     *  on the allocation policy, number of members etc...
     *  The main reason for creating a class such as this is that it makes 
     *  the readability of bitfield_tupe higher.
     *  This will also allow me to quickly deduce whether or not two bft types
     *  are equivilant based on a simple set of concepts about the type itself.
     *
     */
    typedef typename is_same<
        allocator,
        mpl::void_
    >::type                                 is_allocator_allocated;

    typedef typename is_same<
        typename storage_policy::alloc,
        storage_policy_stack
    >::type                                 is_stack_allocated;

#if 1
    void display_debug_info() {
        using namespace std;

        typedef typename details::bft_impl_<T0, mpl::void_,mpl::vector<>,mpl::size_t<0u> >::type step_1;
        cout << step_1::offset::value << endl;
        step_1::debug_info();

        typedef typename step_1::template process<T1 >::type step_2;
        // cout << step_2::offset::value << endl;
        step_2::debug_info();

        typedef typename step_2::template process<T2>::type step_3;
        // cout << step_3::offset::value << endl;
        step_3::debug_info();

        typedef typename step_3::template process<T3>::type step_4;
        // cout << step_4::offset::value << endl;
        step_4::debug_info();

        typedef typename step_4::template process<T4>::type step_5;
        // cout << step_5::offset::value << endl;
        step_5::debug_info();

        typedef typename step_5::template process<T5>::type step_6;
        // cout << step_6::offset::value << endl;
        step_6::debug_info();

        typedef typename step_6::template process<T6>::type step_7;
        // cout << step_7::offset::value << endl;
        step_7::debug_info();

        typedef typename step_7::template process<T7>::type step_8;
        // cout << step_8::offset::value << endl;
        step_8::debug_info();

        typedef typename step_8::template process<T8>::type step_9;
        // cout << step_9::offset::value << endl;
        step_9::debug_info();

        typedef typename step_9::template process<T9>::type step_10;
        // cout << step_10::offset::value << endl;
        step_10::debug_info();

    }
#endif
};

#undef BOOST_BFT_ARG_PROCESSING_CLASS

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
    : protected details::bitfield_tuple_base<
        T0,T1,T2,T3,T4,T5,T6,T7,T8,T9
    >,
    details::bitfield_tuple_base<
        T0,T1,T2,T3,T4,T5,T6,T7,T8,T9
    >::allocation_base_policy
{
private:
    typedef details::bitfield_tuple_base<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> _base;
    typedef typename _base::allocation_base_policy  _alloc_base;
    typedef bitfield_tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>  _self;

public:
    typedef typename _base::is_stack_allocated      is_stack_allocated;
    typedef typename _base::is_allocator_allocated  is_allocator_allocated;
    typedef typename _base::processed_args          processed_args;
    typedef typename _base::field_vector            members;
    typedef typename _base::storage_type            storage_type;




    /** Value constructor.
     *  This sets the initial value of the internal data to x.
     *  Also functions as the default constructor.
     */
    bitfield_tuple(storage_type x = 0)
        :_alloc_base(x)
    { }

    /** Copy constructor. */
    bitfield_tuple(_self const& x)
        :_alloc_base( x.data() )
    { }

    /** "Identical members" copy constructor.
     *  Basically this is used to get the data within a structure whose 
     *  bitfields are the same (in the same order) but the storage is 
     *  specified in a different place within the template arguments.
     *
     *  XXX 
     *      TODO: The signature of this will need to change possibly to
     *      use enable_if or some form of internal dispatching.
     *  XXX
     */
    template <typename T>
    bitfield_tuple(T const& x);

    // TODO: look into the creation of a member wise constructor.
    
    /** Interface: Stack Allocated.
     *  Retuns a copy of the internally stored type.
     */
    //@{
    storage_type const data( ) const {
         return this->get_data();
    }

    storage_type data( ) {
         return this->get_data();
    }
    //@}

    void debug() {
        this->display_debug_info();
    }
    
};  



} // end boost

#endif
