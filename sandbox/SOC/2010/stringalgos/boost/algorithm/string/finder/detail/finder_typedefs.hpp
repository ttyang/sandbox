#ifndef BOOST_ALGORITHM_FINDER_TYPEDEFS_HPP
#define BOOST_ALGORITHM_FINDER_TYPEDEFS_HPP

#include <boost/range/iterator_range.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/category.hpp>

#include <boost/iterator/iterator_traits.hpp>

namespace boost { namespace algorithm { namespace detail {

    template <class Range1T, class Range2T, class ComparatorT, class AllocatorT>
    struct finder_typedefs
    {
        //! The type of the substring
        typedef Range1T substring_type;
        //! The type of the string
        typedef Range2T string_type;
        //! The type of the comparator
        typedef ComparatorT comparator_type;
        //! The type of the allocator
        typedef AllocatorT allocator_type;
        //! The type of the substring's iterator
        typedef typename boost::range_const_iterator<substring_type>::type
            substring_iterator_type;
        //! The type of the string's iterator
        typedef typename boost::range_iterator<string_type>::type
            string_iterator_type;
        //! The character type of the substring
        typedef typename boost::iterator_value<substring_iterator_type>::type
            substring_char_type;
        //! The character type of the string
        typedef typename boost::iterator_value<string_iterator_type>::type
            string_char_type;
        //! The range type of the substring (pattern)
        typedef typename boost::iterator_range<substring_iterator_type>
            substring_range_type;
        //! The range type of the text
        typedef typename boost::iterator_range<string_iterator_type>
            string_range_type;
        //! A type capable of holding the difference between two iterators of the text
        typedef typename boost::iterator_difference<string_iterator_type>::type
            string_difference_type;
    protected:
        typedef typename boost::range_category<substring_type>::type substring_iterator_category;
        typedef typename boost::range_category<string_type>::type string_iterator_category;

        typedef typename boost::reverse_iterator<substring_iterator_type> substring_reverse_iterator_type;
        typedef typename boost::reverse_iterator<string_iterator_type> string_reverse_iterator_type;
        typedef typename boost::iterator_range<substring_reverse_iterator_type> substring_reverse_range_type;
        typedef typename boost::iterator_range<string_reverse_iterator_type> string_reverse_range_type;
    };

} } }

#endif // BOOST_ALGORITHM_FINDER_TYPEDEFS_HPP