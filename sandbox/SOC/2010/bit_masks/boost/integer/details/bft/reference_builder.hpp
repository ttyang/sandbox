//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_BITFIELD_TUPLE_REFERENCE_BUILDER_HPP
#define BOOST_BITFIELD_TUPLE_REFERENCE_BUILDER_HPP
#include <boost/static_assert.hpp>



/** The meta functions contained within this file are meant to aid in the 
 *  locating the correct value within member and deducing the correct constness
 *  and returning the correct reference type which will allow for only one
 *  reference type class within bitfield_tuple.
 */
namespace boost { namespace detials {



/** Checks to see if a name exists.
 *  returns mpl::true_ or mpl::false_
 */
template <typename BitfieldTuple, typename Name>
struct name_exists {
    typedef typename mpl::not_<
        is_same <
            typename ::boost::mpl::find_if<
                typename BitfieldTuple::members,
                details::match_name<
                    mpl::_1,
                    Name
                >
            >::type,
            typename mpl::end<
                typename BitfieldTuple::members
            >::type
        >
    >::type       type;
};

/** Returns an element by which has a given name. */
template <typename BitfieldTuple, typename Name>
struct find_by_element_name {

    BOOST_STATIC_ASSERT(( name_exists<BitfieldTuple,Name>::type::value ));

    typedef typename mpl::deref<
        typename mpl::find_if<
            typename BitfieldTuple::members,
            details::match_name<
                mpl::_1,
                Name
            >
        >::type
    >::type             type;
};

/** Returns an element from members within bitfield_tuple
 *  at a given index.
 */
template <typename BitfieldTuple, std::size_t Index>
struct find_by_element_index {

    BOOST_STATIC_ASSERT((
        mpl::size<typename BitfieldTuple::members>::value
            >
        Index
    ));

    typedef typename mpl::at_c<
        typename BitfieldTuple::members,
        Index
    >::type             type;
};




/** Used for building the proxy reference types based on a given name.
 *  The CV qualifiers refer to CV qualifiers which are applied to another type
 *  then used by then used for the creation of a reference type that has the 
 *  correct qualifiers. This will take most or all of the guess work out of
 *  creating reference types when needed.
 */
template <typename BitfieldTuple, typename Name, typename CVQualifiers>
struct make_reference_type_by_name {

    typedef typename find_by_element_name<BitfieldTuple,Name>::type bft_element;
    // apply qualifiers from CVQualifiers to the bft_element type
    // this will allow me to pass the qualifiers into the newly created reference
    // type then unpack them and apply them to the rest of the internal types
    // correctly.
    
    typedef typename mpl::if_<
        typename is_const<CVQualifiers>::type,
        typename add_const<bft_element>::type,
        bft_element
    >::type                                 bft_element_c_qualifier_applied;

    typedef typename mpl::if_<
        typename is_volatile<CVQualifiers>::type,
        typename add_volatile<bft_element_c_qualifier_applied>::type,
        bft_element_c_qualifier_applied
    >::type                                 bft_element_v_qualifier_applied;

    // typedef 
    // volatile 
};



}} // end boost::details

#endif
