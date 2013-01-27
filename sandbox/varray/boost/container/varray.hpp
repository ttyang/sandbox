// Boost.Container varray
//
// Copyright (c) 2012-2013 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2011-2013 Andrew Hundt.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTAINER_VARRAY_HPP
#define BOOST_CONTAINER_VARRAY_HPP

#include <boost/container/detail/varray.hpp>

namespace boost { namespace container {

/**
 * @brief A variable-size array container with fixed capacity.
 *
 * varray is a sequence container like boost::container::vector with contiguous storage that can
 * change in size, along with the static allocation, low overhead, and fixed capacity of boost::array.
 *
 * A varray is a sequence that supports random access to elements, constant time insertion and
 * removal of elements at the end, and linear time insertion and removal of elements at the beginning or 
 * in the middle. The number of elements in a varray may vary dynamically up to a fixed capacity
 * because elements are stored within the object itself similarly to an array. However, objects are 
 * initialized as they are inserted into varray unlike C arrays or std::array which must construct
 * all elements on instantiation. The behavior of varray enables the use of statically allocated
 * elements in cases with complex object lifetime requirements that would otherwise not be trivially 
 * possible.
 *
 * @par Error Handling
 *  Insertion beyond the capacity and out of bounds errors result in undefined behavior unless
 *  otherwise specified. In this respect if size() == capacity(), then varray::push_back()
 *  behaves like std::vector pop_front() if size() == empty(). The reason for this difference
 *  is because unlike vectors, varray does not perform allocation.
 *
 * @par Advanced Usage
 *  Error handling behavior can be modified to more closely match std::vector exception behavior
 *  when exceeding bounds by providing an alternate Strategy and varray_traits instantiation.
 *
 * @tparam Value    The type of element that will be stored.
 * @tparam Capacity The maximum number of elements varray can store, fixed at compile time.
 * @tparam Strategy Defines the public typedefs and error handlers,
 *         implements StaticVectorStrategy and has some similarities
 *         to an Allocator.
 */
template <typename Value, std::size_t Capacity>
class varray
    : public container_detail::varray<Value, Capacity>
{
    typedef container_detail::varray<Value, Capacity> base_t;

    BOOST_COPYABLE_AND_MOVABLE(varray)

public:
    typedef typename base_t::value_type value_type;
    typedef typename base_t::size_type size_type;

    varray() : base_t() {}
    explicit varray(size_type count) : base_t(count) {}
    varray(size_type count, value_type const& value) : base_t(count, value) {}
    template <typename Iterator>
    varray(Iterator first, Iterator last) : base_t(first, last) {}

    varray(varray const& other) : base_t(other) {}
    template <std::size_t C>
    varray(varray<value_type, C> const& other) : base_t(other) {}

    varray & operator=(BOOST_COPY_ASSIGN_REF(varray) other) { base_t::operator=(other); return *this; }
    template <std::size_t C>
// TEMPORARY WORKAROUND
#if defined(BOOST_NO_RVALUE_REFERENCES)
    varray & operator=(::boost::rv< varray<value_type, C> > const& other)
#else
    varray & operator=(varray<value_type, C> const& other)
#endif
    { base_t::operator=(other); return *this; }

    varray(BOOST_RV_REF(varray) other) : base_t(boost::move(static_cast<base_t&>(other))) {}
    template <std::size_t C>
    varray(BOOST_RV_REF_2_TEMPL_ARGS(varray, value_type, C) other)
        : base_t(boost::move(static_cast<container_detail::varray<value_type, C>&>(other)))
    {}

    varray & operator=(BOOST_RV_REF(varray) other)
    {
        base_t::operator=(boost::move(static_cast<base_t&>(other)));
        return *this;
    }

    template <std::size_t C>
    varray & operator=(BOOST_RV_REF_2_TEMPL_ARGS(varray, value_type, C) other)
    {
        base_t::operator=(boost::move(static_cast<container_detail::varray<value_type, C>&>(other)));
        return *this;
    }
};

}} // namespace boost::container

#endif // BOOST_CONTAINER_VARRAY_HPP
