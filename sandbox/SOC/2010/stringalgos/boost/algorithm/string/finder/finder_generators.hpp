#ifndef BOOST_ALGORITHM_FINDER_GENERATORS_HPP
#define BOOST_ALGORITHM_FINDER_GENERATORS_HPP

#include <boost/algorithm/string/finder/generated_finders.hpp>
#include <boost/algorithm/string/finder/default_search_algorithm.hpp>
#include <boost/algorithm/string/compare.hpp>
#include <boost/algorithm/string/detail/finder.hpp>

namespace boost { namespace algorithm {
        
   //! "First" finder generator
    /*!
        Constructs a \ref first_finder_t. For backward compatibility, the finder is a
        functor which looks for the \b first occurrence of the string in a given input.
        The result is given as an \c iterator_range delimiting the match.
        \param Search The pattern to look for
        \param Comp A comparator used to match individual characters
        \tparam AlgorithmTagT A tag of the search algorithm that should be used for searching
        \deprecated
    */
    template<typename RangeT,typename PredicateT, typename AlgorithmTagT>
    inline boost::algorithm::first_finder_t<RangeT, typename AlgorithmTagT::type,PredicateT>
    first_finder( 
        const RangeT& Search, PredicateT const& Comp,
        AlgorithmTagT const&)
    {
        return boost::algorithm::first_finder_t<RangeT, typename AlgorithmTagT::type,PredicateT>(&Search, Comp);
    }

    //! \overload
    template<typename RangeT,typename PredicateT>
    inline boost::algorithm::first_finder_t<RangeT,
        boost::algorithm::default_finder_algorithm, PredicateT>
    first_finder( 
        const RangeT& Search, PredicateT const& Comp)
    {
        return boost::algorithm::first_finder(Search,Comp, boost::algorithm::default_finder_algorithm_tag());
    }

    //! \overload
    template<typename RangeT>
    inline boost::algorithm::first_finder_t<RangeT, boost::algorithm::default_finder_algorithm,
        boost::algorithm::is_equal>
    first_finder(
        const RangeT& Search)
    {
        return boost::algorithm::first_finder(Search, 
            boost::algorithm::is_equal(), boost::algorithm::default_finder_algorithm_tag());
    }

    //! "Last" finder generator
    /*!
        Constructs a \ref last_finder_t. For backward compatibility, the finder is a
        functor which looks for the \b last occurrence of the string in a given input.
        The result is given as an \c iterator_range delimiting the match.
        \param Search The pattern to look for
        \param Comp A comparator used to match individual characters
        \tparam AlgorithmTagT A tag of the search algorithm that should be used for searching
        \deprecated
    */
    template<typename RangeT, typename PredicateT, typename AlgorithmTagT>
    inline boost::algorithm::last_finder_t<RangeT, typename AlgorithmTagT::type,PredicateT>
    last_finder( const RangeT& Search, PredicateT const &Comp,
        AlgorithmTagT const&)
    {
        return boost::algorithm::last_finder_t<RangeT, typename AlgorithmTagT::type,PredicateT>(&Search, Comp);
    }

    //!\overload
    template<typename RangeT, typename PredicateT>
    inline boost::algorithm::last_finder_t<RangeT, boost::algorithm::default_finder_algorithm,
        PredicateT>
    last_finder( const RangeT& Search, PredicateT const &Comp)
    {
        return boost::algorithm::last_finder(Search, Comp,
            boost::algorithm::default_finder_algorithm_tag());
    }

    //!\overload
    template<typename RangeT>
    inline boost::algorithm::last_finder_t<RangeT,
        boost::algorithm::default_finder_algorithm, boost::algorithm::is_equal>
    last_finder( const RangeT& Search)
    {
        return boost::algorithm::last_finder(Search,
            boost::algorithm::is_equal(), boost::algorithm::default_finder_algorithm_tag());
    }

    //! "Nth" finder generator
    /*!
        Constructs a \ref nth_finder_t. For backward compatibility, the finder is a
        functor which looks for the \b Nth occurrence of the string in a given input.
        The result is given as an \c iterator_range delimiting the match.
        \param Search The pattern to look for
        \param Comp A comparator used to match individual characters
        \tparam AlgorithmTagT A tag of the search algorithm that should be used for searching
        \deprecated
    */
    template<typename RangeT, typename PredicateT, typename AlgorithmTagT>
    inline boost::algorithm::nth_finder_t<RangeT,
        typename AlgorithmTagT::type,PredicateT>
    nth_finder(const RangeT& Search, int Nth, PredicateT const &Comp, AlgorithmTagT const &)
    {
        return boost::algorithm::nth_finder_t<RangeT,
            typename AlgorithmTagT::type, PredicateT>(&Search, Comp, Nth);
    }

    //!\overload
    template<typename RangeT, typename PredicateT>
    inline boost::algorithm::nth_finder_t<RangeT,
        boost::algorithm::default_finder_algorithm, PredicateT>
    nth_finder(const RangeT& Search, int Nth, PredicateT const &Comp)
    {
        return boost::algorithm::nth_finder(Search, Nth, Comp,
            boost::algorithm::default_finder_algorithm_tag());
    }

    //!\overload
    template<typename RangeT>
    inline boost::algorithm::nth_finder_t<RangeT,
        boost::algorithm::default_finder_algorithm, boost::algorithm::is_equal>
    nth_finder(const RangeT& Search, int Nth)
    {
        return boost::algorithm::nth_finder(Search, Nth, boost::algorithm::is_equal(),
            boost::algorithm::default_finder_algorithm_tag());
    }

    //! "Head" finder
    /*!
        Construct the \c head_finder. The finder returns a head of a given
        input. The head is a prefix of a string up to n elements in
        size. If an input has less then n elements, whole input is 
        considered a head.
        The result is given as an \c iterator_range delimiting the match.

        \param N The size of the head
        \return An instance of the \c head_finder object
        \deprecated
    */
    inline detail::head_finderF
    head_finder( int N )
    {
        return detail::head_finderF(N);
    }
        
    //! "Tail" finder
    /*!
        Construct the \c tail_finder. The finder returns a tail of a given
        input. The tail is a suffix of a string up to n elements in
        size. If an input has less then n elements, whole input is 
        considered a head.
        The result is given as an \c iterator_range delimiting the match.

        \param N The size of the head
        \return An instance of the \c tail_finder object
    */
    inline detail::tail_finderF
    tail_finder( int N )
    {
        return detail::tail_finderF(N);
    }

    //! "Token" finder
    /*!
        Construct the \c token_finder. The finder searches for a token 
        specified by a predicate. It is similar to std::find_if 
        algorithm, with an exception that it return a range of
        instead of a single iterator.

        If "compress token mode" is enabled, adjacent matching tokens are 
        concatenated into one match. Thus the finder can be used to 
        search for continuous segments of characters satisfying the 
        given predicate.

        The result is given as an \c iterator_range delimiting the match.

        \param Pred An element selection predicate
        \param eCompress Compress flag
        \return An instance of the \c token_finder object
    */
    template< typename PredicateT >
    inline detail::token_finderF<PredicateT>
    token_finder( 
        PredicateT Pred, 
        token_compress_mode_type eCompress=token_compress_off )
    {
        return detail::token_finderF<PredicateT>( Pred, eCompress );
    }

    //! "Range" finder
    /*!
        Construct the \c range_finder. The finder does not perform 
        any operation. It simply returns the given range for 
        any input. 

        \param Begin Beginning of the range
        \param End End of the range
        \param Range The range.
        \return An instance of the \c range_finger object
    */
    template< typename ForwardIteratorT >
    inline detail::range_finderF<ForwardIteratorT>
    range_finder(
        ForwardIteratorT Begin,
        ForwardIteratorT End )
    {
        return detail::range_finderF<ForwardIteratorT>( Begin, End );
    }

    //! "Range" finder
    /*!       
        \overload
    */
    template< typename ForwardIteratorT >
    inline detail::range_finderF<ForwardIteratorT>
    range_finder( iterator_range<ForwardIteratorT> Range )
    {
        return detail::range_finderF<ForwardIteratorT>( Range );
    }

} } // namespace algorithm, namespace boost

namespace boost
{
    // pull the names to the boost namespace
    using algorithm::first_finder;
    using algorithm::last_finder;
    using algorithm::nth_finder;
    using algorithm::head_finder;
    using algorithm::tail_finder;
    using algorithm::token_finder;
    using algorithm::range_finder;
} // namespace boost

#endif // BOOST_ALGORITHM_FINDER_GENERATORS_HPP
