//=======================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_INSERT_RANGE_RESULT_GEN_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_INSERT_RANGE_RESULT_GEN_HPP_INCLUDED

#include <deque>
#include <utility>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/detail/metafunction/is_associative_container.hpp>

//[reference__insert_range_result_gen
namespace boost {

    template <typename Selector, typename T>
    struct insert_range_result_gen
    {
        //<-
     private:
        typedef typename container_gen<Selector,T>::type C;
        typedef typename C::iterator I;

     public:
        typedef typename ::boost::mpl::if_<
                    ::boost::detail::metafunction::is_associative_container<C>
                  , ::std::deque<I>
                  , ::std::pair<I,I>
                >::type
                type;
#if 0
        //->
        typedef ... type;
        //<-
#endif
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            2
          , insert_range_result_gen
          , (Selector, T)
        )
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_CONTAINER_GEN_INSERT_RANGE_RESULT_GEN_HPP_INCLUDED

