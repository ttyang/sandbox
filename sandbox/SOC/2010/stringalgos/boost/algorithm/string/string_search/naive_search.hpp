#ifndef BOOST_ALGORITHM_NAIVE_SEARCH_HPP
#define BOOST_ALGORITHM_NAIVE_SEARCH_HPP

#include <boost/range/iterator_range.hpp>
#include <boost/call_traits.hpp>
#include <boost/mpl/void.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <string>

#include <boost/algorithm/string/finder/detail/finder_typedefs.hpp>

/*!
    \file
    Implements the naive string search algorithm
*/

namespace boost { namespace algorithm {
    // todo Copyable

    //! An implementation of the naive string search algorithm
	struct naive_search
	{

		template <class Finder, class ForwardRange1T, class ForwardRange2T, class ComparatorT, class AllocatorT>
        struct algorithm
            : public boost::algorithm::detail::finder_typedefs<
                ForwardRange1T,ForwardRange2T,ComparatorT,AllocatorT>
		{
        public:
            std::string get_algorithm_name () const { return "Naive search"; }
		protected:
            algorithm () { }


			string_range_type find(string_iterator_type start)
			{
                /*typedef typename Finder::string_iterator_type string_iterator_type;
                typedef typename Finder::substring_iterator_type substring_iterator_type;
                typedef typename Finder::substring_range_type substring_range_type;
                typedef typename Finder::string_range_type string_range_type;
                typedef typename Finder::comparator_type comparator_type;*/
                string_range_type const &str = static_cast<Finder*>(this)->get_string_range();
                substring_range_type const &substr = static_cast<Finder*>(this)->get_substring_range();
                comparator_type const &comparator = static_cast<Finder*>(this)->get_comparator();


				for (;
					start != boost::end(str); ++start)
				{
					string_iterator_type str_iter(start);
					substring_iterator_type substr_iter;
					for (substr_iter = boost::begin(substr);
						substr_iter != boost::end(substr) && str_iter != boost::end(str);
                        ++substr_iter, ++str_iter)
					{
						if (!comparator(*str_iter, *substr_iter)) break;
					}
					if (substr_iter == boost::end(substr))
						return boost::iterator_range<string_iterator_type>(start, str_iter);
				}
				return boost::iterator_range<string_iterator_type>(
                    boost::end(str),boost::end(str));
			}
            //! It is guaranteed that each of these two functions will get called at least once before find()
            //! is used.
            //No precomputation to be done on the substring
            inline void on_substring_change()
            {
            }
            //No precomputation to be done on the string
            inline void on_string_change()
            {
            }
		};

	};
    //! Instances of this type can be passed to find functions to require them to
    //!     use the Boyer-Moore algorithm.
    struct naive_search_tag { typedef boost::algorithm::naive_search type; };
} }
	
namespace boost
{
    using boost::algorithm::naive_search;
}

#endif