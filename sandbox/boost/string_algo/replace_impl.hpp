//  Boost string_algo library replace_impl.hpp header file  ---------------------------//

//  (C) Copyright Pavol Droba 2002. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_STRING_REPLACE_IMPL_HPP
#define BOOST_STRING_REPLACE_IMPL_HPP

#include "traits.hpp"
#include "iterator_range.hpp"
#include "container_traits.hpp"

namespace boost {

    namespace string_algo {

// generic replace  -----------------------------------------------------------------//

        // replace 
        /*
            Create new sequence into output interator as a copy of input sequence,
            but with the match replaced with the formated substitute range. 
            The match is searched using find functor and substitute is formated using
            format functor
        */
        template< 
            typename InputT, 
            typename SearchT,
            typename FormatT,
            typename OutputIteratorT,
            typename FindFT,
            typename FormatFT >
        inline OutputIteratorT replace_copy(
            const InputT& Input,
            const SearchT& Search,
            const FormatT& Format,
            OutputIteratorT Output,
            FindFT FindF,
            FormatFT FormatF )
        {
            typedef typename string_algo::
                search_traits<InputT, SearchT>::const_range_type input_range_type; 
            // Find first match
            input_range_type M=FindF( Input, Search );

            if ( M.empty() )
            {
                // Match not found - return original sequence
                std::copy( Input.begin(), Input.end(), Output );
                return Output;
            }

            // Copy the beginning of the sequence
            std::copy( Input.begin(), M.begin(), Output );
            // Format find result
            typename FormatFT::result_type FResult=FormatF( Format, M );
            // Copy formated result
            std::copy( FResult.begin(), FResult.end(), Output );
            // Copy the rest of the sequence
            std::copy( M.end(), Input.end(), Output );

            return Output;
        }

        // replace iterator version
        template< 
            typename InputIteratorT, 
            typename SearchIteratorT, 
            typename FormatIteratorT,
            typename OutputIteratorT,
            typename FindFT,
            typename FormatFT >
        inline OutputIteratorT replace_copy(
            InputIteratorT Begin,
            InputIteratorT End,
            SearchIteratorT SearchBegin,
            SearchIteratorT SearchEnd,
            FormatIteratorT FormatBegin,
            FormatIteratorT FormatEnd,
            OutputIteratorT Output,
            FindFT FindF,
            FormatFT FormatF )
        {
            return replace_copy(
                string_algo::make_range( Begin, End ),
                string_algo::make_range( SearchBegin, SearchEnd ),
                string_algo::make_range( FormatBegin, FormatEnd ),
                Output,
                FindF,
                FormatF );
        }

        // replace sequence version
        template< 
            typename InputT, 
            typename SearchT,
            typename FormatT,
            typename FindFT,
            typename FormatFT >
        inline InputT replace_copy(
            const InputT& Input,
            const SearchT& Search,
            const FormatT& Format,
            FindFT FindF,
            FormatFT FormatF )
        {
            typedef typename string_algo::
                search_traits<InputT, SearchT>::const_range_type input_range_type; 

			// Instantiate insert functor
			typename string_algo::container_caps_traits<InputT>::insert_type InsertF;

            // Find first match
            input_range_type M=FindF( Input, Search );

            if ( M.empty() )
            {
                // Match not found - return original sequence
                return InputT( Input );
            }

            InputT Output;
            // Copy the beginning of the sequence
            InsertF( Output, Output.end(), Input.begin(), M.begin() );
            // Copy formated result
            InsertF( Output, Output.end(), FormatF( Format, M.begin(), M.end() ) );
            // Copy the rest of the sequence
            InsertF( Output, Output.end(), M.end(), Input.end() );

            return Output;
        }

        // replace in-place sequence version
        template<
            typename InputT,
            typename SearchT,
            typename FormatT,
            typename FindFT,
            typename FormatFT >
        inline InputT& replace( 
            InputT& Input,
            const SearchT& Search,
            const FormatT& Format,
            FindFT FindF,
            FormatFT FormatF )
        {
            typedef typename string_algo::
                search_traits<InputT, SearchT>::range_type input_range_type; 
            
            // Instantiate replace functor
			typename string_algo::container_caps_traits<InputT>::replace_type ReplaceF;

            // Find range for the match
            input_range_type M=FindF( Input, Search );

            if ( M.empty() )
            {
                // Search not found - return original sequence
                return Input;
            }

            // Replace match
            ReplaceF( Input, M.begin(), M.end(), FormatF( Format, M.begin(), M.end() ) );
            
            return Input;
        }


//  replace_all generic ----------------------------------------------------------------//

        // replace_all generic version
        /*
            Create new sequence into output interator as a copy of input sequence,
            but with the all matches replaced with substitute range.
        */
        template< 
            typename InputT, 
            typename SearchT,
            typename FormatT,
            typename OutputIteratorT,
            typename FindFT,
            typename FormatFT >
        inline OutputIteratorT replace_all_copy(
            const InputT& Input,
            const SearchT& Search,
            const FormatT& Format,
            OutputIteratorT Output,
            FindFT FindF,
            FormatFT FormatF )
        {
            typedef typename string_algo::
                search_traits<InputT, SearchT>::const_range_type input_range_type; 
            typedef typename string_algo::
                search_traits<InputT, SearchT>::input_const_iterator_type input_iterator_type; 
        
            input_iterator_type LastMatch=Input.begin();

            // Find first match
            input_range_type M=FindF( Input, Search );

            // Iterate throug all matches
            while( !M.empty() )
            {
                // Copy the beginning of the sequence
                std::copy( LastMatch, M.begin(), Output );
                // Format find result
                typename FormatFT::result_type FResult=FormatF( Format, M );
                // Copy formated result
                std::copy( FResult.begin(), FResult.end(), Output );

                // Proceed to the next match
                LastMatch=M.end();
                M=FindF( Input, Search, LastMatch );
            }

            // Copy the rest of the sequence
            std::copy( LastMatch, Input.end(), Output );

            return Output;
        }

        // replace_all generic version
        template< 
            typename InputIteratorT, 
            typename SearchIteratorT, 
            typename FormatIteratorT,
            typename OutputIteratorT,
            typename FindFT,
            typename FormatFT >
        inline OutputIteratorT replace_all_copy(
            InputIteratorT Begin,
            InputIteratorT End,
            SearchIteratorT SearchBegin,
            SearchIteratorT SearchEnd,
            FormatIteratorT FormatBegin,
            FormatIteratorT FormatEnd,
            OutputIteratorT Output,
            FindFT FindF,
            FormatFT FormatF )
        {
            return replace_all_copy(
                string_algo::make_range( Begin, End ),
                string_algo::make_range( SearchBegin, SearchEnd ),
                string_algo::make_range( FormatBegin, FormatEnd ),
                Output,
                FindF,
                FormatF );
        }

        // replace_all sequence version
        template< 
            typename InputT, 
            typename SearchT,
            typename FormatT,
            typename FindFT,
            typename FormatFT >
        inline InputT replace_all_copy(
            const InputT& Input,
            const SearchT& Search,
            const FormatT& Format,
            FindFT FindF,
            FormatFT FormatF )
        {
            typedef typename string_algo::
                search_traits<InputT, SearchT>::input_const_iterator_type input_iterator_type; 
            typedef typename string_algo::
                search_traits<InputT, SearchT>::const_range_type input_range_type; 

            // Instantiate insert functor
			typename string_algo::container_caps_traits<InputT>::insert_type InsertF;

			// Initialize last match
            input_iterator_type LastMatch=Input.begin();
            // Find first match
            input_range_type M=FindF( Input, Search );

			// Output temporary
            InputT Output;

            // Iterate throug all matches
            while( !M.empty() )
            {
                // Copy the beginning of the sequence
                InsertF( Output, Output.end(), LastMatch, M.begin() );
                // Copy formated result
                InsertF( Output, Output.end(), FormatF( Format, M.begin(), M.end() ) );

                // Proceed to the next match
                LastMatch=M.end();
                M=FindF( Input, Search, LastMatch );
            }

            // Copy the rest of the sequence
            InsertF( Output, Output.end(), LastMatch, Input.end() );

            return Output;
        }

        // replace_all in-place sequence version
        template<
            typename InputT,
            typename SearchT,
            typename FormatT,
            typename FindFT,
            typename FormatFT >
        inline InputT& replace_all( 
            InputT& Input,
            const SearchT& Search,
            const FormatT& Format,
            FindFT FindF,
            FormatFT FormatF )
        {
            typedef typename string_algo::
                search_traits<InputT, SearchT>::input_iterator_type input_iterator_type; 
            typedef typename string_algo::
                search_traits<InputT, SearchT>::range_type input_range_type; 
            
            // Instantiate replace functor
			typename string_algo::container_caps_traits<InputT>::replace_iter_type ReplaceF;

			// Find range for the match
            input_range_type M=FindF( Input, Search );

            while ( !M.empty() )
            {
                // Replace match
                input_iterator_type It=
                    ReplaceF( Input, M.begin(), M.end(), FormatF( Format, M.begin(), M.end() ) );

                M=FindF( Input, Search, It );
            }

            return Input;
        }

    } // namespace string_algo
    
} // namespace boost


#endif  // BOOST_REPLACE_IMPL_HPP
