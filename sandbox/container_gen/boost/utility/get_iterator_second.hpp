// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UTILITY_GET_ITERATOR_SECOND_HPP_INCLUDED
#define BOOST_UTILITY_GET_ITERATOR_SECOND_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/ref.hpp>
#include <boost/ptr_container/detail/map_iterator.hpp>

//[reference__get_iterator_second_result
namespace boost {

    template <typename Iterator>
    struct get_iterator_second_result
    {
        typedef typename ::std::tr1::remove_pointer<
                    typename ::boost::unwrap_reference<
                        BOOST_TYPEOF_TPL(::boost::ref(Iterator()->second))
                    >::type
                >::type&
                type;
    };
}  // namespace boost
//]

namespace boost { namespace detail {

    template <typename Iterator>
    class get_iterator_second_helper
    {
     public:
        typedef Iterator
                argument_type;
        typedef typename get_iterator_second_result<Iterator>::type
                result_type;

        result_type operator()(argument_type itr) const;

     private:
        static result_type _evaluate(Iterator itr, ::boost::mpl::true_);

        static result_type _evaluate(Iterator itr, ::boost::mpl::false_);
    };

    template <typename Iterator>
    inline typename get_iterator_second_helper<Iterator>::result_type
        get_iterator_second_helper<Iterator>::operator()(
            argument_type itr
        ) const
    {
        typedef typename ::boost::iterator_value<Iterator>::type _value_type;

        return _evaluate(
            itr
          , typename ::boost::mpl::if_<
                ::std::tr1::is_same<
                    ::boost::ptr_container_detail::ref_pair<
                        typename _value_type::first_type
                      , typename _value_type::second_type
                    >
                  , _value_type
                >
              , ::boost::mpl::true_
              , ::boost::mpl::false_
            >::type()
        );
    }

    template <typename Iterator>
    inline typename get_iterator_second_helper<Iterator>::result_type
        get_iterator_second_helper<Iterator>::_evaluate(
            Iterator itr
          , ::boost::mpl::true_
        )
    {
        return *itr->second;
    }

    template <typename Iterator>
    inline typename get_iterator_second_helper<Iterator>::result_type
        get_iterator_second_helper<Iterator>::_evaluate(
            Iterator itr
          , ::boost::mpl::false_
        )
    {
        return itr->second;
    }
}}  // namespace boost::detail

//[reference__get_iterator_second
namespace boost {

    template <typename Iterator>
    typename get_iterator_second_result<Iterator>::type
        get_iterator_second(Iterator itr);

    //<-
    template <typename Iterator>
    inline typename get_iterator_second_result<Iterator>::type
        get_iterator_second(Iterator itr)
    {
        return detail::get_iterator_second_helper<Iterator>()(itr);
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_UTILITY_GET_ITERATOR_SECOND_HPP_INCLUDED

