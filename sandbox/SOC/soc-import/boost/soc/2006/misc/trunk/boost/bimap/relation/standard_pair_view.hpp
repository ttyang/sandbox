// Boost.Bimap
//
// Copyright (c) 2006 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/standard_pair_view.hpp
/// \brief Defines the standard_pair_view class.

#ifndef BOOST_BIMAP_RELATION_STANDARD_PAIR_VIEW_HPP
#define BOOST_BIMAP_RELATION_STANDARD_PAIR_VIEW_HPP

#include <boost/bimap/relation/standard_relation_fwd.hpp>

#include <boost/type_traits/remove_const.hpp>

#include <utility>

#include <boost/call_traits.hpp>
#include <boost/operators.hpp>
#include <boost/bimap/relation/pair_layout.hpp>
#include <boost/bimap/relation/symmetrical_base.hpp>
#include <boost/bimap/tags/support/value_type_of.hpp>
#include <boost/bimap/relation/structured_pair.hpp>

#include <boost/bimap/relation/detail/totally_ordered_pair.hpp>

namespace boost {
namespace bimap {
namespace relation {


/// \brief The left side view of a standard relation
/**
See also reference_binder_finder, normal_reference_binder.
                                                                        **/

template< class FirstType, class SecondType >
struct normal_reference_binder :

    public symmetrical_base<FirstType,SecondType>
{
    typedef symmetrical_base<FirstType,SecondType> base_;

    public:

    typedef normal_reference_binder reference_binder_;

    typedef standard_relation<FirstType,SecondType,true > relation_force_mutable;
    typedef standard_relation<FirstType,SecondType,false> relation_not_force_mutable;

    typedef       standard_relation_view<FirstType,SecondType>       relation_view;

    typedef typename base_::left_value_type  first_type;
    typedef typename base_::right_value_type second_type;

    first_type  & first;
    second_type & second;

    normal_reference_binder(relation_force_mutable & r) :
        first(r.left), second(r.right) {}

    normal_reference_binder(relation_not_force_mutable & r) :
        first(r.left), second(r.right) {}

    normal_reference_binder(relation_view & r) :
        first(r.left), second(r.right) {}

    normal_reference_binder(first_type const & f, second_type const & s) :
        first(f), second(s) {}

    typename base_::left_value_type & get_left()
    {
        return first;
    }

    const typename base_::left_value_type & get_left() const
    {
        return first;
    }

    typename base_::right_value_type & get_right()
    {
        return second;
    }

    const typename base_::right_value_type & get_right() const
    {
        return second;
    }
};

/// \brief The right side view of a standard relation
/**
See also reference_binder_finder, mirror_reference_binder.
                                                                        **/
template< class FirstType, class SecondType >
struct mirror_reference_binder :

    public symmetrical_base<SecondType,FirstType>
{

    typedef symmetrical_base<SecondType,FirstType> base_;

    public:

    typedef mirror_reference_binder reference_binder_;

    typedef standard_relation<SecondType,FirstType,true > relation_force_mutable;
    typedef standard_relation<SecondType,FirstType,false> relation_not_force_mutable;

    typedef       standard_relation_view<SecondType,FirstType>       relation_view;

    typedef typename base_::right_value_type first_type;
    typedef typename base_::left_value_type  second_type;

    second_type & second;
    first_type  & first;

    mirror_reference_binder(relation_force_mutable & r) :
        second(r.left), first(r.right) {}

    mirror_reference_binder(relation_not_force_mutable & r) :
        second(r.left), first(r.right) {}

    mirror_reference_binder(relation_view & r) :
        second(r.left), first(r.right) {}

    mirror_reference_binder(first_type const & f, second_type const & s) :
        second(s), first(f) {}

    typename base_::left_value_type & get_left()
    {
        return second;
    }

    const typename base_::left_value_type & get_left() const
    {
        return second;
    }

    typename base_::right_value_type & get_right()
    {
        return first;
    }

    const typename base_::right_value_type & get_right() const
    {
        return first;
    }
};


/** \struct boost::bimap::relation::reference_binder_finder
\brief Obtain the a pair reference binder with the correct layout.

\code
template< class FirstType, class SecondType, class Layout >
struct reference_binder_finder
{
    typedef {normal/mirror}_reference_binder<FirstType,SecondType> type;
};
\endcode

See also normal_reference_binder, mirror_reference_binder.
                                                                        **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class FirstType, class SecondType, class Layout >
struct reference_binder_finder
{
    typedef normal_reference_binder<FirstType,SecondType> type;
};

template< class FirstType, class SecondType >
struct reference_binder_finder<FirstType,SecondType,mirror_layout>
{
    typedef mirror_reference_binder<FirstType,SecondType> type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/// \brief A side view of a relation that is full compliant with the standard.
/**

See also standard_relation, const_standard_pair_view.
                                                                                **/

template< class FirstType, class SecondType, class Layout >
class standard_pair_view :

    public reference_binder_finder<FirstType,SecondType,Layout>::type

{
    typedef typename reference_binder_finder<FirstType,SecondType,Layout>::type base_;

    public:

    explicit standard_pair_view(typename base_::relation_force_mutable & r) :
        base_(r) {}

    explicit standard_pair_view(typename base_::relation_not_force_mutable & r) :
        base_(r) {}

    explicit standard_pair_view(typename base_::relation_view & r) :
        base_(r) {}

    // Interaction with std::pair

    typedef std::pair
    <
        typename ::boost::remove_const< typename base_:: first_type >::type,
        typename ::boost::remove_const< typename base_::second_type >::type

    > std_pair;

    typedef std::pair
    <
        const typename ::boost::remove_const< typename base_:: first_type >::type,
              typename ::boost::remove_const< typename base_::second_type >::type

    > std_map_pair;

    // Interaction with structured pair

    private:

    typedef structured_pair<FirstType,SecondType,Layout> structured_pair_type;

    public:

    operator const structured_pair_type ()
    {
        return structured_pair_type(
            base_::first, base_::second
        );
    }

    BOOST_BIMAP_TOTALLY_ORDERED_PAIR_IMPLEMENTATION(
        base_::first, base_::second,

        standard_pair_view,
        first,second
    );

    BOOST_BIMAP_TOTALLY_ORDERED_PAIR_IMPLEMENTATION(
        base_::first, base_::second,

        std_pair,
        first,second
    );

    BOOST_BIMAP_TOTALLY_ORDERED_PAIR_IMPLEMENTATION(
        base_::first, base_::second,

        std_map_pair,
        first,second
    );

};

} // namespace relation
} // namespace bimap
} // namespace boost

#endif // BOOST_BIMAP_RELATION_STANDARD_PAIR_VIEW_HPP

