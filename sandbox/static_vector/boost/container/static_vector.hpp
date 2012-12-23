// Boost.Container StaticVector
//
// Copyright (c) 2012 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2011-2012 Andrew Hundt.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTAINER_STATIC_VECTOR_HPP
#define BOOST_CONTAINER_STATIC_VECTOR_HPP

#include <boost/container/detail/static_vector_util.hpp>

#include <stdexcept>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/swap.hpp>
#include <boost/integer.hpp>

#include <boost/mpl/assert.hpp>

#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/aligned_storage.hpp>

// TODO - use std::reverse_iterator and std::iterator_traits
// instead Boost.Iterator to remove dependency?
// or boost/detail/iterator.hpp ?
#include <boost/iterator/reverse_iterator.hpp>

#if defined(BOOST_NO_RVALUE_REFERENCES)

#define BOOST_CONTAINER_STATIC_VECTOR_ASSIGN_REF(V, C, S)   boost::rv< static_vector<V, C, S> > const&
#define BOOST_CONTAINER_STATIC_VECTOR_RV_REF(V, C, S)       boost::rv< static_vector<V, C, S> > &

#define BOOST_CONTAINER_STATIC_VECTOR_COPYABLE_AND_MOVABLE() \
BOOST_COPYABLE_AND_MOVABLE(static_vector) \
public: \
    template <std::size_t C, typename S> \
    static_vector & operator=(static_vector<Value, C, S> & t) \
    { \
        typedef static_vector<Value, C, S> O; \
        this->operator=(static_cast<const ::boost::rv<O> &>(const_cast<const O &>(t))); \
        return *this; \
    } \
private:

#else

#define BOOST_CONTAINER_STATIC_VECTOR_ASSIGN_REF(V, C, S)   static_vector<V, C, S> const&
#define BOOST_CONTAINER_STATIC_VECTOR_RV_REF(V, C, S)       static_vector<V, C, S> &&

#define BOOST_CONTAINER_STATIC_VECTOR_COPYABLE_AND_MOVABLE() \
BOOST_COPYABLE_AND_MOVABLE(static_vector)

#endif

namespace boost { namespace container {

// Forward declaration
template <typename Value, std::size_t Capacity, typename Strategy>
class static_vector;

namespace static_vector_detail {

// TODO - remove size_type from here and allow setting it only in traits?

template <typename SizeType = std::size_t>
struct default_strategy
{
    typedef SizeType size_type;

    template <typename V, std::size_t Capacity, typename S>
    static void check_capacity(container::static_vector<V, Capacity, S> const&, std::size_t s)
    {
        BOOST_ASSERT_MSG(s <= Capacity, "size can't exceed the capacity");
    }

    template <typename V, std::size_t C, typename S>
    static void check_index_throwing(container::static_vector<V, C, S> const& v,
                                     typename container::static_vector<V, C, S>::size_type i)
    {
        if ( v.size() <= i )
            throw std::out_of_range("index out of bounds");
    }

    template <typename V, std::size_t C, typename S>
    static void check_index(container::static_vector<V, C, S> const& v,
                            typename container::static_vector<V, C, S>::size_type i)
    {
        BOOST_ASSERT_MSG(i < v.size(), "index out of bounds");
    }

    template <typename V, std::size_t C, typename S>
    static void check_empty(container::static_vector<V, C, S> const& v)
    {
        BOOST_ASSERT_MSG(0 < v.size(), "the container is empty");
    }

    template <typename V, std::size_t C, typename S>
    static void check_iterator_end_neq(container::static_vector<V, C, S> const& v,
                                       typename container::static_vector<V, C, S>::const_iterator position)
    {
        BOOST_ASSERT_MSG(v.begin() <= position && position < v.end(), "iterator out of bounds");
    }

    template <typename V, std::size_t C, typename S>
    static void check_iterator_end_eq(container::static_vector<V, C, S> const& v,
                                      typename container::static_vector<V, C, S>::const_iterator position)
    {
        BOOST_ASSERT_MSG(v.begin() <= position && position <= v.end(), "iterator out of bounds");
    }
};

template <typename Value, std::size_t Capacity, typename Strategy>
struct static_vector_traits
{
    typedef typename Strategy::size_type size_type;
    typedef boost::false_type use_memop_in_swap_and_move;
    typedef boost::false_type use_optimized_swap;
    typedef Strategy strategy;
};

} // namespace static_vector_detail

template <typename Value, std::size_t Capacity, typename Strategy = static_vector_detail::default_strategy<> >
class static_vector
{
    typedef typename
    static_vector_detail::static_vector_traits<
        Value, Capacity, Strategy
    >::size_type stored_size_type;

    BOOST_MPL_ASSERT_MSG(
        ( boost::is_unsigned<stored_size_type>::value &&
          sizeof(typename boost::uint_value_t<Capacity>::least) <= sizeof(stored_size_type) ),
        SIZE_TYPE_IS_TOO_SMALL,
        (static_vector)
    );

    typedef boost::aligned_storage<
        sizeof(Value[Capacity]),
        boost::alignment_of<Value[Capacity]>::value
    > aligned_storage_type;

    typedef typename
    static_vector_detail::static_vector_traits<
        Value, Capacity, Strategy
    >::strategy errh;

    template <typename V, std::size_t C, typename S>
    friend class static_vector;

    BOOST_CONTAINER_STATIC_VECTOR_COPYABLE_AND_MOVABLE()

public:
    typedef Value value_type;
    typedef stored_size_type size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Value& reference;
    typedef Value const& const_reference;
    typedef Value * pointer;
    typedef const Value* const_pointer;
    typedef Value* iterator;
    typedef const Value * const_iterator;
    typedef boost::reverse_iterator<iterator> reverse_iterator;
    typedef boost::reverse_iterator<const_iterator> const_reverse_iterator;

    // nothrow
    static_vector()
        : m_size(0)
    {}

    // strong
    explicit static_vector(size_type count)
        : m_size(0)
    {
        this->resize(count);                                                        // may throw
    }

    // strong
    static_vector(size_type count, value_type const& value)
        : m_size(0)
    {
        this->resize(count, value);                                                 // may throw
    }

    // strong
    template <typename Iterator>
    static_vector(Iterator first, Iterator last)
        : m_size(0)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator
        this->assign(first, last);                                                    // may throw
    }

    // strong
    static_vector(static_vector const& other)
        : m_size(other.size())
    {
        namespace sv = static_vector_detail;
        sv::uninitialized_copy(other.begin(), other.end(), this->begin());          // may throw
    }

    // strong
    template <std::size_t C, typename S>
    static_vector(static_vector<value_type, C, S> const& other)
        : m_size(other.size())
    {
        errh::check_capacity(*this, other.size());                                  // may throw
        
        namespace sv = static_vector_detail;
        sv::uninitialized_copy(other.begin(), other.end(), this->begin());          // may throw
    }

    // basic
    static_vector & operator=(BOOST_COPY_ASSIGN_REF(static_vector) other)
    {
        this->assign(other.begin(), other.end());                                     // may throw

        return *this;
    }

    // basic
    template <std::size_t C, typename S>
    static_vector & operator=(BOOST_CONTAINER_STATIC_VECTOR_ASSIGN_REF(value_type, C, S) other)
    {
        this->assign(other.begin(), other.end());                                     // may throw

        return *this;
    }

    // nothrow or strong (based on traits, default nothrow)
    // (note: linear complexity)
    static_vector(BOOST_RV_REF(static_vector) other)
    {
        typedef typename
        static_vector_detail::static_vector_traits<
            Value, Capacity, Strategy
        >::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_ctor_dispatch(other, use_memop_in_swap_and_move());
    }

    // nothrow or strong (based on traits, default nothrow)
    // (note: linear complexity)
    template <std::size_t C, typename S>
    static_vector(BOOST_CONTAINER_STATIC_VECTOR_RV_REF(value_type, C, S) other)
        : m_size(other.m_size)
    {
        errh::check_capacity(*this, other.size());                                  // may throw

        typedef typename
        static_vector_detail::static_vector_traits<
            Value, Capacity, Strategy
        >::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_ctor_dispatch(other, use_memop_in_swap_and_move());
    }

    // nothrow or basic (based on traits, default nothrow)
    // (note: linear complexity)
    static_vector & operator=(BOOST_RV_REF(static_vector) other)
    {
        typedef typename
        static_vector_detail::static_vector_traits<
            Value, Capacity, Strategy
        >::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_assign_dispatch(other, use_memop_in_swap_and_move());

        return *this;
    }

    // nothrow or basic (based on traits, default nothrow)
    // (note: linear complexity)
    template <std::size_t C, typename S>
    static_vector & operator=(BOOST_CONTAINER_STATIC_VECTOR_RV_REF(value_type, C, S) other)
    {
        errh::check_capacity(*this, other.size());                                  // may throw

        typedef typename
        static_vector_detail::static_vector_traits<
            Value, Capacity, Strategy
        >::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_assign_dispatch(other, use_memop_in_swap_and_move());

        return *this;
    }

    // nothrow
    ~static_vector()
    {
        namespace sv = static_vector_detail;
        sv::destroy(this->begin(), this->end());
    }

    // nothrow or basic (depends on traits, default nothrow)
    // swap (note: linear complexity)
    void swap(static_vector & other)
    {
        typedef typename
        static_vector_detail::static_vector_traits<
            Value, Capacity, Strategy
        >::use_optimized_swap use_optimized_swap;

        this->swap_dispatch(other, use_optimized_swap());
    }

    // nothrow, strong or basic (depends on traits and strategy)
    // swap (note: linear complexity)
    template <std::size_t C, typename S>
    void swap(static_vector<value_type, C, S> & other)
    {
        errh::check_capacity(*this, other.size());
        errh::check_capacity(other, this->size());

        typedef typename
        static_vector_detail::static_vector_traits<
            Value, Capacity, Strategy
        >::use_optimized_swap use_optimized_swap;

        this->swap_dispatch(other, use_optimized_swap()); 
    }

    // strong
    void resize(size_type count)
    {
        namespace sv = static_vector_detail;

        if ( count < m_size )
        {
            sv::destroy(this->begin() + count, this->end());
        }
        else
        {
            errh::check_capacity(*this, count);                                     // may throw

            sv::construct(this->end(), this->begin() + count);                      // may throw
        }
        m_size = count; // update end
    }

    // strong
    void resize(size_type count, value_type const& value)
    {
        if ( count < m_size )
        {
            namespace sv = static_vector_detail;
            sv::destroy(this->begin() + count, this->end());
        }
        else
        {
            errh::check_capacity(*this, count);                                     // may throw
            
            std::uninitialized_fill(this->end(), this->begin() + count, value);     // may throw
        }
        m_size = count; // update end
    }

    // nothrow
    void reserve(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // strong
    void push_back(value_type const& value)
    {
        errh::check_capacity(*this, m_size + 1);                                    // may throw
        
        namespace sv = static_vector_detail;
        sv::uninitialized_fill(this->end(), value);                                 // may throw
        ++m_size; // update end
    }

    // nothrow
    void pop_back()
    {
        errh::check_empty(*this);

        //--m_size; // update end
        //namespace sv = static_vector_detail;
        //sv::destroy(this->end());

        // safer and more intuitive version
        namespace sv = static_vector_detail;
        sv::destroy(this->end() - 1);
        --m_size; // update end
    }

    // basic
    iterator insert(iterator position, value_type const& value)
    {
        namespace sv = static_vector_detail;

        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, m_size + 1);                                    // may throw

        if ( position == this->end() )
        {
            sv::uninitialized_fill(position, value);                                // may throw
            ++m_size; // update end
        }
        else
        {
            // TODO - should following lines check for exception and revert to the old size?

            sv::uninitialized_fill(this->end(), *(this->end() - 1));                // may throw
            ++m_size; // update end
            sv::move_backward(position, this->end() - 2, this->end() - 1);          // may throw
            sv::fill(position, value);                                              // may throw
        }

        return position;
    }

    // basic
    iterator insert(iterator position, size_type count, value_type const& value)
    {
        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, m_size + count);                                // may throw

        if ( position == this->end() )
        {
            std::uninitialized_fill(position, position + count, value);             // may throw
            m_size += count; // update end
        }
        else
        {
            namespace sv = static_vector_detail;

            difference_type to_move = std::distance(position, this->end());
            
            // TODO - should following lines check for exception and revert to the old size?

            if ( count < static_cast<size_type>(to_move) )
            {
                sv::uninitialized_copy(this->end() - count, this->end(), this->end());          // may throw
                m_size += count; // update end
                sv::move_backward(position, position + to_move - count, this->end() - count);   // may throw
                std::fill_n(position, count, value);                                            // may throw
            }
            else
            {
                std::uninitialized_fill(this->end(), position + count, value);                  // may throw
                m_size += count - to_move; // update end
                sv::uninitialized_copy(position, position + to_move, position + count);         // may throw
                m_size += to_move; // update end
                std::fill_n(position, to_move, value);                                          // may throw
            }
        }

        return position;
    }

    // basic
    template <typename Iterator>
    iterator insert(iterator position, Iterator first, Iterator last)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator

        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        this->insert_dispatch(position, first, last, traversal());

        return position;
    }

    // basic
    iterator erase(iterator position)
    {
        namespace sv = static_vector_detail;

        errh::check_iterator_end_neq(*this, position);

        sv::move(position + 1, this->end(), position);                              // may throw
        sv::destroy(this->end() - 1);
        --m_size;

        return position;
    }

    // basic
    iterator erase(iterator first, iterator last)
    {
        namespace sv = static_vector_detail;

        errh::check_iterator_end_eq(*this, first);
        errh::check_iterator_end_eq(*this, last);
        
        difference_type n = std::distance(first, last);
        //BOOST_ASSERT_MSG(0 <= n, "invalid range");

        sv::move(last, this->end(), first);                                         // may throw
        sv::destroy(this->end() - n, this->end());
        m_size -= n;

        return first;
    }

    // basic
    template <typename Iterator>
    void assign(Iterator first, Iterator last)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator

        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        this->assign_dispatch(first, last, traversal());                            // may throw
    }

    // basic
    void assign(size_type count, value_type const& value)
    {
        if ( count < m_size )
        {
            namespace sv = static_vector_detail;

            std::fill_n(this->begin(), count, value);
            sv::destroy(this->begin() + count, this->end());
        }
        else
        {
            errh::check_capacity(*this, count);                                     // may throw

            std::fill_n(this->begin(), m_size, value);
            std::uninitialized_fill(this->end(), this->begin() + count, value);     // may throw
        }
        m_size = count; // update end
    }

    // nothrow
    void clear()
    {
        namespace sv = static_vector_detail;
        sv::destroy(this->begin(), this->end());
        m_size = 0; // update end
    }

    // strong
    Value & at(size_type i)
    {
        errh::check_index_throwing(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    // strong
    Value const& at(size_type i) const
    {
        errh::check_index_throwing(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    // nothrow
    Value & operator[](size_type i)
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    // nothrow
    Value const& operator[](size_type i) const
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    // nothrow
    Value & front()
    {
        errh::check_empty(*this);
        return *(this->begin());
    }

    // nothrow
    Value const& front() const
    {
        errh::check_empty(*this);
        return *(this->begin());
    }

    // nothrow
    Value & back()
    {
        errh::check_empty(*this);
        return *(this->end() - 1);
    }

    // nothrow
    Value const& back() const
    {
        errh::check_empty(*this);
        return *(this->end() - 1);
    }

    // nothrow
    Value * data() { return this->ptr(); }
    const Value * data() const { return this->ptr(); }

    // nothrow
    iterator begin() { return this->ptr(); }
    const_iterator begin() const { return this->ptr(); }
    const_iterator cbegin() const { return this->ptr(); }
    iterator end() { return this->begin() + m_size; }
    const_iterator end() const { return this->begin() + m_size; }
    const_iterator cend() const { return this->cbegin() + m_size; }
    // nothrow
    reverse_iterator rbegin() { return reverse_iterator(this->end()); }
    const_reverse_iterator rbegin() const { return reverse_iterator(this->end()); }
    const_reverse_iterator crbegin() const { return reverse_iterator(this->end()); }
    reverse_iterator rend() { return reverse_iterator(this->begin()); }
    const_reverse_iterator rend() const { return reverse_iterator(this->begin()); }
    const_reverse_iterator crend() const { return reverse_iterator(this->begin()); }

    // nothrow
    static size_type capacity() { return Capacity; }
    static size_type max_size() { return Capacity; }
    size_type size() const { return m_size; }
    bool empty() const { return 0 == m_size; }
    void shrink_to_fit() {}

private:

    // nothrow
    // linear complexity
    template <std::size_t C, typename S>
    void move_ctor_dispatch(static_vector<value_type, C, S> & other, boost::true_type /*use_memop*/)
    {
        ::memcpy(this->data(), other.data(), sizeof(Value) * other.m_size);
        m_size = other.m_size;
        other.m_size = 0;
    }

    // strong
    // linear complexity
    template <std::size_t C, typename S>
    void move_ctor_dispatch(static_vector<value_type, C, S> & other, boost::false_type /*use_memop*/)
    {
        namespace sv = static_vector_detail;
        sv::uninitialized_move(other.begin(), other.end(), this->begin());
        m_size = other.m_size;
        sv::destroy(other.begin(), other.end());        
        other.m_size = 0;
    }

    // nothrow
    // linear complexity
    template <std::size_t C, typename S>
    void move_assign_dispatch(static_vector<value_type, C, S> & other, boost::true_type /*use_memop*/)
    {
        this->clear();

        ::memcpy(this->data(), other.data(), sizeof(Value) * other.m_size);
        boost::swap(m_size, other.m_size);
    }

    // basic
    // linear complexity
    template <std::size_t C, typename S>
    void move_assign_dispatch(static_vector<value_type, C, S> & other, boost::false_type /*use_memop*/)
    {
        // TODO - use move iterators or implement moving

        this->assign(other.begin(), other.end());
        other.clear();
    }

    // nothrow
    // linear complexity
    template <std::size_t C, typename S>
    void swap_dispatch(static_vector<value_type, C, S> & other, boost::true_type const& /*use_optimized_swap*/)
    {
        typedef typename
        boost::mpl::if_c<
            Capacity < C,
            aligned_storage_type,
            typename static_vector<value_type, C, S>::aligned_storage_type
        >::type
        storage_type;
        
        storage_type temp;
        Value * temp_ptr = reinterpret_cast<Value*>(temp.address());

        ::memcpy(temp_ptr, this->data(), sizeof(Value) * this->size());
        ::memcpy(this->data(), other.data(), sizeof(Value) * other.size());
        ::memcpy(other.data(), temp_ptr, sizeof(Value) * this->size());

        boost::swap(m_size, other.m_size);
    }

    // nothrow or basic
    // linear complexity
    template <std::size_t C, typename S>
    void swap_dispatch(static_vector<value_type, C, S> & other, boost::false_type const& /*use_optimized_swap*/)
    {
        namespace sv = static_vector_detail;

        typedef typename
        static_vector_detail::static_vector_traits<
            Value, Capacity, Strategy
        >::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        if ( this->size() < other.size() )
            swap_dispatch_impl(this->begin(), this->end(), other.begin(), other.end(), use_memop_in_swap_and_move()); // may throw
        else
            swap_dispatch_impl(other.begin(), other.end(), this->begin(), this->end(), use_memop_in_swap_and_move()); // may throw
        boost::swap(m_size, other.m_size);
    }

    // nothrow
    // linear complexity
    void swap_dispatch_impl(iterator first_sm, iterator last_sm, iterator first_la, iterator last_la, boost::true_type const& /*use_memop*/)
    {
        //BOOST_ASSERT_MSG(std::distance(first_sm, last_sm) <= std::distance(first_la, last_la));

        namespace sv = static_vector_detail;
        for (; first_sm != last_sm ; ++first_sm, ++first_la)
        {
            boost::aligned_storage<
                sizeof(value_type),
                boost::alignment_of<value_type>::value
            > temp_storage;
            value_type * temp_ptr = reinterpret_cast<value_type*>(temp_storage.address());

            ::memcpy(temp_ptr, boost::addressof(*first_sm), sizeof(value_type));
            ::memcpy(boost::addressof(*first_sm), boost::addressof(*first_la), sizeof(value_type));
            ::memcpy(boost::addressof(*first_la), temp_ptr, sizeof(value_type));
        }

        ::memcpy(first_sm, first_la, sizeof(value_type) * std::distance(first_la, last_la));
    }

    // basic
    // linear complexity
    void swap_dispatch_impl(iterator first_sm, iterator last_sm, iterator first_la, iterator last_la, boost::false_type const& /*use_memop*/)
    {
        //BOOST_ASSERT_MSG(std::distance(first_sm, last_sm) <= std::distance(first_la, last_la));

        namespace sv = static_vector_detail;
        for (; first_sm != last_sm ; ++first_sm, ++first_la)
        {
            //boost::swap(*first_sm, *first_la);                                    // may throw
            value_type temp(boost::move(*first_sm));                                // may throw
            *first_sm = boost::move(*first_la);                                     // may throw
            *first_la = boost::move(temp);                                          // may throw
        }
        sv::uninitialized_move(first_la, last_la, first_sm);                        // may throw
        sv::destroy(first_la, last_la);
    }

    // insert

    template <typename Iterator>
    void insert_dispatch(iterator position, Iterator first, Iterator last, boost::random_access_traversal_tag const&)
    {
        errh::check_iterator_end_eq(*this, position);
        
        typename boost::iterator_difference<Iterator>::type
            count = std::distance(first, last);

        errh::check_capacity(*this, m_size + count);                                             // may throw

        if ( position == this->end() )
        {
            namespace sv = static_vector_detail;

            sv::uninitialized_copy(first, last, position);                                      // may throw
            m_size += count; // update end
        }
        else
        {
            this->insert_in_the_middle(position, first, last, count);                           // may throw
        }
    }

    template <typename Iterator, typename Traversal>
    void insert_dispatch(iterator position, Iterator first, Iterator last, Traversal const& /*not_random_access*/)
    {
        errh::check_iterator_end_eq(*this, position);

        if ( position == this->end() )
        {
            namespace sv = static_vector_detail;

            std::ptrdiff_t d = std::distance(position, this->begin() + Capacity);
            std::size_t count = sv::uninitialized_copy_s(first, last, position, d);                     // may throw
            
            errh::check_capacity(*this, count <= static_cast<std::size_t>(d) ? m_size + count : Capacity + 1);  // may throw

            m_size += count;
        }
        else
        {
            typename boost::iterator_difference<Iterator>::type
                count = std::distance(first, last);
            
            errh::check_capacity(*this, m_size + count);                                                // may throw

            this->insert_in_the_middle(position, first, last, count);                                   // may throw
        }
    }

    template <typename Iterator>
    void insert_in_the_middle(iterator position, Iterator first, Iterator last, difference_type count)
    {
        namespace sv = static_vector_detail;

        difference_type to_move = std::distance(position, this->end());

        // TODO - should following lines check for exception and revert to the old size?

        if ( count < to_move )
        {
            sv::uninitialized_copy(this->end() - count, this->end(), this->end());              // may throw
            m_size += count; // update end
            sv::move_backward(position, position + to_move - count, this->end() - count);       // may throw
            sv::copy(first, last, position);                                                    // may throw
        }
        else
        {
            Iterator middle_iter = first;
            std::advance(middle_iter, to_move);

            sv::uninitialized_copy(middle_iter, last, this->end());                             // may throw
            m_size += count - to_move; // update end
            sv::uninitialized_copy(position, position + to_move, position + count);             // may throw
            m_size += to_move; // update end
            sv::copy(first, middle_iter, position) ;                                            // may throw
        }
    }

    // assign

    template <typename Iterator>
    void assign_dispatch(Iterator first, Iterator last, boost::random_access_traversal_tag const& /*not_random_access*/)
    {
        namespace sv = static_vector_detail;

        typename boost::iterator_difference<Iterator>::type
            s = std::distance(first, last);

        errh::check_capacity(*this, s);                                                 // may throw

        if ( m_size <= static_cast<size_type>(s) )
        {
            sv::copy(first, first + m_size, this->begin());                             // may throw
            // TODO - perform uninitialized_copy first?
            sv::uninitialized_copy(first + m_size, last, this->end());                  // may throw
        }
        else
        {
            sv::copy(first, last, this->begin());                                       // may throw
            sv::destroy(this->begin() + s, this->end());
        }
        m_size = s; // update end
    }

    template <typename Iterator, typename Traversal>
    void assign_dispatch(Iterator first, Iterator last, Traversal const& /*not_random_access*/)
    {
        namespace sv = static_vector_detail;

        size_type s = 0;
        iterator it = this->begin();

        for ( ; it != this->end() && first != last ; ++it, ++first, ++s )
            *it = *first;                                                                                   // may throw

        sv::destroy(it, this->end());

        std::ptrdiff_t d = std::distance(it, this->begin() + Capacity);
        std::size_t count = sv::uninitialized_copy_s(first, last, it, d);                                   // may throw
        s += count;

        errh::check_capacity(*this, count <= static_cast<std::size_t>(d) ? s : Capacity + 1);               // may throw

        m_size = s; // update end
    }

    Value * ptr()
    {
        return (reinterpret_cast<Value*>(m_storage.address()));
    }

    const Value * ptr() const
    {
        return (reinterpret_cast<const Value*>(m_storage.address()));
    }

    stored_size_type m_size;
    aligned_storage_type m_storage;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<typename Value, typename Strategy>
class static_vector<Value, 0, Strategy>
{
    typedef typename
    static_vector_detail::static_vector_traits<
        Value, 0, Strategy
    >::size_type stored_size_type;

    typedef typename
    static_vector_detail::static_vector_traits<
        Value, 0, Strategy
    >::strategy errh;

public:
    typedef Value value_type;
    typedef stored_size_type size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Value& reference;
    typedef Value const& const_reference;
    typedef Value * pointer;
    typedef const Value* const_pointer;
    typedef Value* iterator;
    typedef const Value * const_iterator;
    typedef boost::reverse_iterator<iterator> reverse_iterator;
    typedef boost::reverse_iterator<const_iterator> const_reverse_iterator;

    // nothrow
    static_vector() {}

    // strong
    explicit static_vector(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // strong
    static_vector(size_type count, value_type const&)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // strong
    static_vector(static_vector const& other)
    {
        //errh::check_capacity(*this, count);
    }

    // strong
    template <size_t C>
    static_vector(static_vector<value_type, C> const& other)
    {
        errh::check_capacity(*this, other.size());                                  // may throw
    }

    // strong
    template <typename Iterator>
    static_vector(Iterator first, Iterator last)
    {
        errh::check_capacity(*this, std::distance(first, last));                    // may throw
    }

    // basic
    static_vector & operator=(static_vector const& other)
    {
        //errh::check_capacity(*this, other.size());
        return *this;
    }

    // basic
    template <size_t C>
    static_vector & operator=(static_vector<value_type, C> const& other)
    {
        errh::check_capacity(*this, other.size());                                  // may throw
        return *this;
    }

    // nothrow
    ~static_vector() {}

    // strong
    void resize(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // strong
    void resize(size_type count, value_type const&)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // nothrow
    void reserve(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    // strong
    void push_back(value_type const&)
    {
        errh::check_capacity(*this, 1);                                             // may throw
    }

    // nothrow
    void pop_back()
    {
        errh::check_empty(*this);
    }

    // basic
    void insert(iterator position, value_type const&)
    {
        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, 1);                                             // may throw
    }

    // basic
    void insert(iterator position, size_type count, value_type const&)
    {
        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, count);                                         // may throw
    }

    // basic
    template <typename Iterator>
    void insert(iterator, Iterator first, Iterator last)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator
        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        errh::check_capacity(*this, std::distance(first, last));                    // may throw
    }

    // basic
    void erase(iterator position)
    {
        errh::check_iterator_end_neq(*this, position);
    }

    // basic
    void erase(iterator first, iterator last)
    {
        errh::check_iterator_end_eq(*this, first);
        errh::check_iterator_end_eq(*this, last);

        //BOOST_ASSERT_MSG(0 <= n, "invalid range");
    }

    // basic
    template <typename Iterator>
    void assign(Iterator first, Iterator last)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator
        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        errh::check_capacity(*this, std::distance(first, last));                    // may throw
    }

    // basic
    void assign(size_type count, value_type const&)
    {
        errh::check_capacity(*this, count);                                     // may throw
    }

    // nothrow
    void clear() {}

    // strong
    Value & at(size_type i)
    {
        errh::check_index_throwing(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    // strong
    Value const& at(size_type i) const
    {
        errh::check_index_throwing(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    // nothrow
    Value & operator[](size_type i)
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    // nothrow
    Value const& operator[](size_type i) const
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    // nothrow
    Value & front()
    {
        errh::check_empty(*this);
        return *(this->begin());
    }

    // nothrow
    Value const& front() const
    {
        errh::check_empty(*this);
        return *(this->begin());
    }

    // nothrow
    Value & back()
    {
        errh::check_empty(*this);
        return *(this->end() - 1);
    }

    // nothrow
    Value const& back() const
    {
        errh::check_empty(*this);
        return *(this->end() - 1);
    }

    // nothrow
    Value * data() { return this->ptr(); }
    const Value * data() const { return this->ptr(); }

    // nothrow
    iterator begin() { return this->ptr(); }
    const_iterator begin() const { return this->ptr(); }
    const_iterator cbegin() const { return this->ptr(); }
    iterator end() { return this->begin(); }
    const_iterator end() const { return this->begin(); }
    const_iterator cend() const { return this->cbegin(); }
    // nothrow
    reverse_iterator rbegin() { return reverse_iterator(this->end()); }
    const_reverse_iterator rbegin() const { return reverse_iterator(this->end()); }
    const_reverse_iterator crbegin() const { return reverse_iterator(this->end()); }
    reverse_iterator rend() { return reverse_iterator(this->begin()); }
    const_reverse_iterator rend() const { return reverse_iterator(this->begin()); }
    const_reverse_iterator crend() const { return reverse_iterator(this->begin()); }

    // nothrow
    size_type capacity() const { return 0; }
    size_type max_size() const { return 0; }
    size_type size() const { return 0; }
    bool empty() const { return true; }

private:

    Value * ptr()
    {
        return (reinterpret_cast<Value*>(this));
    }

    const Value * ptr() const
    {
        return (reinterpret_cast<const Value*>(this));
    }
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// comparisons
template<typename V, std::size_t C, typename S>
bool operator== (static_vector<V, C, S> const& x, static_vector<V, C, S> const& y)
{
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template<typename V, std::size_t C, typename S>
bool operator< (static_vector<V, C, S> const& x, static_vector<V, C, S> const& y)
{
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template<typename V, std::size_t C, typename S>
bool operator!= (static_vector<V, C, S> const& x, static_vector<V, C, S> const& y)
{
    return !(x==y);
}

template<typename V, std::size_t C, typename S>
bool operator> (static_vector<V, C, S> const& x, static_vector<V, C, S> const& y)
{
    return y<x;
}

template<typename V, std::size_t C, typename S>
bool operator<= (static_vector<V, C, S> const& x, static_vector<V, C, S> const& y)
{
    return !(y<x);
}

template<typename V, std::size_t C, typename S>
bool operator>= (static_vector<V, C, S> const& x, static_vector<V, C, S> const& y)
{
    return !(x<y);
}

template<typename V, std::size_t C, typename S>
inline void swap(static_vector<V, C, S> & x, static_vector<V, C, S> & y)
{
    x.swap(y);
}

template<typename V, std::size_t C1, typename S1, std::size_t C2, typename S2>
inline void swap(static_vector<V, C1, S1> & x, static_vector<V, C2, S2> & y)
{
    x.swap(y);
}

}} // namespace boost::container

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
#pragma warning(pop)
#endif

#endif // BOOST_CONTAINER_STATIC_VECTOR_HPP
