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

#include <cstddef>
#include <stdexcept>

#include <boost/config.hpp>
#include <boost/swap.hpp>

#include <boost/iterator/reverse_iterator.hpp>
#include <boost/integer.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

#include <boost/utility/addressof.hpp>

namespace boost { namespace container {

// Forward declaration
template <typename Value, std::size_t Capacity, typename StoredSizeType>
class static_vector;

namespace detail { namespace static_vector {

struct error_handling
{
    template <typename V, std::size_t Capacity, typename S>
    static void check_capacity(container::static_vector<V, Capacity, S> const&,
                               typename container::static_vector<V, Capacity, S>::size_type s)
    {
        //BOOST_ASSERT_MSG(s <= Capacity, "size can't exceed the capacity");
        if ( Capacity < s )
            throw std::bad_alloc();
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

        /*BOOST_GEOMETRY_INDEX_ASSERT_UNUSED_PARAM(
            difference_type dist = std::distance(this->begin(), position);
        )
        BOOST_ASSERT_MSG(
            0 <= dist &&
            ( sizeof(dist) <= sizeof(m_size) ?
                (static_cast<size_type>(dist) < m_size) :
                ( dist < static_cast<difference_type>(m_size))
            ), "invalid iterator"
        );*/
    }

    template <typename V, std::size_t C, typename S>
    static void check_iterator_end_eq(container::static_vector<V, C, S> const& v,
                                      typename container::static_vector<V, C, S>::const_iterator position)
    {
        BOOST_ASSERT_MSG(v.begin() <= position && position <= v.end(), "iterator out of bounds");

        /*BOOST_GEOMETRY_INDEX_ASSERT_UNUSED_PARAM(
            difference_type dist = std::distance(this->begin(), position);
        )
        BOOST_ASSERT_MSG(
        0 <= dist &&
            ( sizeof(dist) <= sizeof(m_size) ?
                (static_cast<size_type>(dist) <= m_size) :
                ( dist <= static_cast<difference_type>(m_size))
            ), "invalid iterator"
        );*/
    }
};

}} // namespace detail::static_vector

// TODO

// StoredSizeType needed?

// Should StoredSizeType be typename boost::uint_value_t<Capacity>::least by default?
// It would probably be slower

// Pass error_handling as a template parameter and implement various ones?

template <typename Value, std::size_t Capacity, typename StoredSizeType = std::size_t>
class static_vector
{
    BOOST_MPL_ASSERT_MSG(
        ( boost::is_unsigned<StoredSizeType>::value &&
          sizeof(typename boost::uint_value_t<Capacity>::least) <= sizeof(StoredSizeType) ),
        SIZE_TYPE_IS_TOO_SMALL,
        (static_vector)
    );

    typedef boost::aligned_storage<
        sizeof(Value[Capacity]),
        boost::alignment_of<Value[Capacity]>::value
    > aligned_storage_type;

    typedef detail::static_vector::error_handling errh;

public:
    typedef Value value_type;
    typedef StoredSizeType size_type;
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
    static_vector(static_vector const& other)
        : m_size(other.size())
    {
        this->uninitialized_copy(other.begin(), other.end(), this->begin());        // may throw
    }

    // strong
    template <std::size_t C, typename S>
    static_vector(static_vector<value_type, C, S> const& other)
        : m_size(other.size())
    {
        errh::check_capacity(other.size());                                         // may throw
        
        this->uninitialized_copy(other.begin(), other.end(), this->begin());        // may throw
    }

    // strong
    template <typename Iterator>
    static_vector(Iterator first, Iterator last)
        : m_size(0)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator
        this->assign(first, last);                                                    // may throw
    }

    // basic
    static_vector & operator=(static_vector const& other)
    {
        this->assign(other.begin(), other.end());                                     // may throw

        return *this;
    }

    // basic
    template <std::size_t C, typename S>
    static_vector & operator=(static_vector<value_type, C, S> const& other)
    {
        this->assign(other.begin(), other.end());                                     // may throw

        return *this;
    }

    // nothrow
    ~static_vector()
    {
        this->destroy(this->begin(), this->end());
    }

    // nothrow
    // swap (note: linear complexity)
    void swap(static_vector & other)
    {
//        iterator it = this->begin();
//        iterator other_it = other.begin();

//        if ( this->size() < other.size() )
//        {
//            for (; it != this->end() ; ++it, ++other_it)
//                boost::swap(*it, *other_it);                                         // may throw
//            this->uninitialized_copy(other_it, other.end(), it);                     // may throw
//            this->destroy(other_it, other.end());
//            boost::swap(m_size, other.m_size);
//        }
//        else
//        {
//            for (; other_it != other.end() ; ++it, ++other_it)
//                boost::swap(*it, *other_it);                                         // may throw
//            this->uninitialized_copy(it, this->end(), other_it);                     // may throw
//            this->destroy(it, this->end());
//            boost::swap(m_size, other.m_size);
//        };

        // TODO - this may be too big for stack
        aligned_storage_type temp;
        Value * temp_ptr = reinterpret_cast<Value*>(temp.address());
        ::memcpy(temp_ptr, this->data(), sizeof(Value) * this->size());
        ::memcpy(this->data(), other.data(), sizeof(Value) * other.size());
        ::memcpy(other.data(), temp_ptr, sizeof(Value) * this->size());
        boost::swap(m_size, other.m_size);
    }

    // basic
    // swap (note: linear complexity)
    template <std::size_t C, typename S>
    void swap(static_vector<value_type, C, S> & other)
    {
        errh::check_capacity(*this, other.size());
        errh::check_capacity(other, this->size());

        iterator it = this->begin();
        iterator other_it = other.begin();

        if ( this->size() < other.size() )
        {
            for (; it != this->end() ; ++it, ++other_it)
                boost::swap(*it, *other_it);                                          // may throw
            this->insert(it, other_it, other.end());                                  // may throw
            other.erase(other_it, other.end());
        }
        else
        {
            for (; other_it != other.end() ; ++it, ++other_it)
                boost::swap(*it, *other_it);                                         // may throw
            other.insert(other_it,it,this->end());                                   // may throw
            this->erase(it, this->end());
        }   
    }

    // strong
    void resize(size_type count)
    {
        if ( count < m_size )
        {
            this->destroy(this->begin() + count, this->end());
        }
        else
        {
            errh::check_capacity(*this, count);                                     // may throw

            this->construct(this->end(), this->begin() + count);                    // may throw
        }
        m_size = count; // update end
    }

    // strong
    void resize(size_type count, value_type const& value)
    {
        if ( count < m_size )
        {
            this->destroy(this->begin() + count, this->end());
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
        
        this->uninitialized_fill(this->end(), value);                               // may throw
        ++m_size; // update end
    }

    // nothrow
    void pop_back()
    {
        errh::check_empty(*this);

        //--m_size; // update end
        //this->destroy(this->end());

        // safer and more intuitive version
        this->destroy(this->end() - 1);
        --m_size; // update end
    }

    // basic
    iterator insert(iterator position, value_type const& value)
    {
        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, m_size + 1);                                    // may throw

        if ( position == this->end() )
        {
            this->uninitialized_fill(position, value);                              // may throw
            ++m_size; // update end
        }
        else
        {
            // TODO - should following lines check for exception and revert to the old size?

            this->uninitialized_fill(this->end(), *(this->end() - 1));              // may throw
            ++m_size; // update end
            this->move_backward(position, this->end() - 2, this->end() - 1);        // may throw
            this->fill(position, value);                                            // may throw
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
            difference_type to_move = std::distance(position, this->end());
            
            // TODO - should following lines check for exception and revert to the old size?

            if ( count < static_cast<size_type>(to_move) )
            {
                this->uninitialized_copy(this->end() - count, this->end(), this->end());        // may throw
                m_size += count; // update end
                this->move_backward(position, position + to_move - count, this->end() - count); // may throw
                std::fill_n(position, count, value);                                            // may throw
            }
            else
            {
                std::uninitialized_fill(this->end(), position + count, value);                  // may throw
                m_size += count - to_move; // update end
                this->uninitialized_copy(position, position + to_move, position + count);       // may throw
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
        errh::check_iterator_end_neq(*this, position);

        this->move(position + 1, this->end(), position);                            // may throw
        this->destroy(this->end() - 1);
        --m_size;

        return position;
    }

    // basic
    iterator erase(iterator first, iterator last)
    {
        errh::check_iterator_end_eq(*this, first);
        errh::check_iterator_end_eq(*this, last);
        
        difference_type n = std::distance(first, last);
        //BOOST_ASSERT_MSG(0 <= n, "invalid range");

        this->move(last, this->end(), first);                                       // may throw
        this->destroy(this->end() - n, this->end());
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
            std::fill_n(this->begin(), count, value);
            this->destroy(this->begin() + count, this->end());
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
        this->destroy(this->begin(), this->end());
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

    // insert

    template <typename Iterator>
    void insert_dispatch(iterator position, Iterator first, Iterator last, boost::random_access_traversal_tag const&)
    {
        errh::check_iterator_end_eq(*this, position);
        
        difference_type count = std::distance(first, last);

        errh::check_capacity(*this, m_size + count);                                             // may throw

        if ( position == this->end() )
        {
            this->uninitialized_copy(first, last, position);                                    // may throw
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
            std::pair<bool, size_type> copy_data =
                this->uninitialized_copy_checked(first, last, position, std::distance(position, this->begin() + Capacity)); // may throw
            
            errh::check_capacity(*this, copy_data.first ? m_size + copy_data.second : Capacity + 1);    // may throw

            m_size += copy_data.second;
        }
        else
        {
            difference_type count = std::distance(first, last);
            
            errh::check_capacity(*this, m_size + count);                                                // may throw

            this->insert_in_the_middle(position, first, last, count);                                   // may throw
        }
    }

    template <typename Iterator>
    void insert_in_the_middle(iterator position, Iterator first, Iterator last, difference_type count)
    {
        difference_type to_move = std::distance(position, this->end());

        // TODO - should following lines check for exception and revert to the old size?

        if ( count < to_move )
        {
            this->uninitialized_copy(this->end() - count, this->end(), this->end());            // may throw
            m_size += count; // update end
            this->move_backward(position, position + to_move - count, this->end() - count);     // may throw
            this->copy(first, last, position);                                                  // may throw
        }
        else
        {
            Iterator middle_iter = first;
            std::advance(middle_iter, to_move);

            this->uninitialized_copy(middle_iter, last, this->end());                           // may throw
            m_size += count - to_move; // update end
            this->uninitialized_copy(position, position + to_move, position + count);           // may throw
            m_size += to_move; // update end
            this->copy(first, middle_iter, position) ;                                          // may throw
        }
    }

    // assign

    template <typename Iterator>
    void assign_dispatch(Iterator first, Iterator last, boost::random_access_traversal_tag const& /*not_random_access*/)
    {
        size_type s = std::distance(first, last);

        errh::check_capacity(*this, s);                                              // may throw

        if ( m_size <= s )
        {
            this->copy(first, first + m_size, this->begin());                        // may throw
            // TODO - perform uninitialized_copy first?
            this->uninitialized_copy(first + m_size, last, this->end());             // may throw
        }
        else
        {
            this->copy(first, last, this->begin());                                  // may throw
            this->destroy(this->begin() + s, this->end());
        }
        m_size = s; // update end
    }

    template <typename Iterator, typename Traversal>
    void assign_dispatch(Iterator first, Iterator last, Traversal const& /*not_random_access*/)
    {
        size_type s = 0;
        iterator it = this->begin();

        for ( ; it != this->end() && first != last ; ++it, ++first, ++s )
            *it = *first;                                                                                   // may throw

        this->destroy(it, this->end());

        std::pair<bool, size_type> copy_data =
            this->uninitialized_copy_checked(first, last, it, std::distance(it, this->begin() + Capacity)); // may throw
        s += copy_data.second;

        errh::check_capacity(*this, copy_data.first ? s : Capacity + 1);                                    // may throw

        m_size = s; // update end
    }

    // uninitialized_copy_checked

    template <typename Iterator>
    std::pair<bool, size_type> uninitialized_copy_checked(Iterator first, Iterator last, iterator dest, size_type max_count)
    {
        size_type count = 0;
        iterator it = dest;
        try
        {
            for ( ; first != last ; ++it, ++first, ++count )
            {
                if ( max_count <= count )
                    return std::make_pair(false, count);

                this->uninitialized_fill(it, *first);                              // may throw
            }
        }
        catch(...)
        {
            this->destroy(dest, it);
            throw;
        }
        return std::make_pair(true, count);
    }

    // copy

    template <typename Iterator>
    void copy(Iterator first, Iterator last, iterator dst)
    {
        typedef typename
            mpl::and_<
                has_trivial_assign<value_type>,
                mpl::or_<
                    is_same<Iterator, value_type *>,
                    is_same<Iterator, const value_type *>
                >
            >::type
        use_memcpy;
        
        this->copy_dispatch(first, last, dst, use_memcpy());                        // may throw
    }

    void copy_dispatch(const value_type * first, const value_type * last, value_type * dst,
                       boost::mpl::bool_<true> const& /*use_memcpy*/)
    {
        ::memcpy(dst, first, sizeof(value_type) * std::distance(first, last));
    }

    template <typename Iterator>
    void copy_dispatch(Iterator first, Iterator last, value_type * dst,
                       boost::mpl::bool_<false> const& /*use_memcpy*/)
    {
        std::copy(first, last, dst);                                                // may throw
    }

    // uninitialized_copy

    template <typename Iterator>
    void uninitialized_copy(Iterator first, Iterator last, iterator dst)
    {
        typedef typename
            mpl::and_<
                has_trivial_copy<value_type>,
                mpl::or_<
                    is_same<Iterator, value_type *>,
                    is_same<Iterator, const value_type *>
                >
            >::type
        use_memcpy;

        this->uninitialized_copy_dispatch(first, last, dst, use_memcpy());          // may throw
    }

    void uninitialized_copy_dispatch(const value_type * first, const value_type * last, value_type * dst,
                                     boost::mpl::bool_<true> const& /*use_memcpy*/)
    {
        ::memcpy(dst, first, sizeof(value_type) * std::distance(first, last));
    }

    template <typename Iterator>
    void uninitialized_copy_dispatch(Iterator first, Iterator last, value_type * dst,
                                     boost::mpl::bool_<false> const& /*use_memcpy*/)
    {
        std::uninitialized_copy(first, last, dst);                                  // may throw
    }

    // uninitialized_fill

    template <typename V>
    void uninitialized_fill(iterator dst, V const& v)
    {
        typedef typename
            mpl::and_<
                has_trivial_copy<value_type>,
                is_same<Value, value_type>
            >::type
        use_memcpy;

        uninitialized_fill_dispatch(dst, v, use_memcpy());                         // may throw
    }

    void uninitialized_fill_dispatch(value_type * ptr, value_type const& v,
                                     boost::mpl::bool_<true> const& /*use_memcpy*/)
    {
        ::memcpy(ptr, boost::addressof(v), sizeof(value_type));
    }

    template <typename V>
    void uninitialized_fill_dispatch(value_type * ptr, V const& v,
                                     boost::mpl::bool_<false> const& /*use_memcpy*/)
    {
        new (ptr) value_type(v);                                                    // may throw
    }

    // move

    void move(iterator first, iterator last, iterator dst)
    {
        this->move_dispatch(first, last, dst, has_trivial_assign<value_type>());    // may throw
    }

    void move_dispatch(value_type * first, value_type * last, value_type * dst,
        boost::true_type const& /*has_trivial_assign*/)
    {
        ::memmove(dst, first, sizeof(value_type) * std::distance(first, last));
    }

    void move_dispatch(value_type * first, value_type * last, value_type * dst,
        boost::false_type const& /*has_trivial_assign*/)
    {
        std::copy(first, last, dst);                                                // may throw
    }

    // move_backward

    void move_backward(iterator first, iterator last, iterator dst)
    {
        this->move_backward_dispatch(first, last, dst, has_trivial_assign<value_type>());    // may throw
    }

    void move_backward_dispatch(value_type * first, value_type * last, value_type * dst,
                                boost::true_type const& /*has_trivial_assign*/)
    {
        difference_type n = std::distance(first, last);
        ::memmove(dst - n, first, sizeof(value_type) * n);
    }

    void move_backward_dispatch(value_type * first, value_type * last, value_type * dst,
                                boost::false_type const& /*has_trivial_assign*/)
    {
        std::copy_backward(first, last, dst);                                                // may throw
    }

    // uninitialized_fill

    template <typename V>
    void fill(iterator dst, V const& v)
    {
        fill_dispatch(dst, v, has_trivial_assign<value_type>());                            // may throw
    }

    void fill_dispatch(value_type * ptr, value_type const& v,
                       boost::true_type const& /*has_trivial_assign*/)
    {
        ::memcpy(ptr, boost::addressof(v), sizeof(value_type));
    }

    template <typename V>
    void fill_dispatch(value_type * ptr, V const& v,
                       boost::false_type const& /*has_trivial_assign*/)
    {
        *ptr = v;                                                                           // may throw
    }

    // destroy

    void destroy(iterator first, iterator last)
    {
        this->destroy_dispatch(first, last, has_trivial_destructor<value_type>());
    }

    void destroy_dispatch(value_type * /*first*/, value_type * /*last*/,
                          boost::true_type const& /*has_trivial_destructor*/)
    {}

    void destroy_dispatch(value_type * first, value_type * last,
                          boost::false_type const& /*has_trivial_destructor*/)
    {
        for ( ; first != last ; ++first )
            first->~value_type();
    }

    // destroy

    void destroy(iterator it)
    {
        this->destroy_dispatch(it, has_trivial_destructor<value_type>());
    }

    void destroy_dispatch(value_type * /*ptr*/,
                          boost::true_type const& /*has_trivial_destructor*/)
    {}

    void destroy_dispatch(value_type * ptr,
                          boost::false_type const& /*has_trivial_destructor*/)
    {
        ptr->~value_type();
    }

    // construct

    void construct(iterator first, iterator last)
    {
        this->construct_dispatch(first, last, has_trivial_constructor<value_type>());   // may throw
    }

    void construct_dispatch(value_type * /*first*/, value_type * /*last*/,
                            boost::true_type const& /*has_trivial_constructor*/)
    {}

    void construct_dispatch(value_type * first, value_type * last,
                            boost::false_type const& /*has_trivial_constructor*/)
    {
        value_type * it = first;
        try
        {
            for ( ; it != last ; ++it )
                new (it) value_type();                                                  // may throw
        }
        catch(...)
        {
            this->destroy(first, it);
            throw;
        }
    }

    Value * ptr()
    {
        return (reinterpret_cast<Value*>(m_storage.address()));
    }

    const Value * ptr() const
    {
        return (reinterpret_cast<const Value*>(m_storage.address()));
    }

    StoredSizeType m_size;
    aligned_storage_type m_storage;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template<typename Value, typename StoredSizeType>
class static_vector<Value, 0, StoredSizeType>
{
    typedef detail::static_vector::error_handling errh;

public:
    typedef Value value_type;
    typedef std::size_t size_type;
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

#endif // BOOST_CONTAINER_STATIC_VECTOR_HPP
