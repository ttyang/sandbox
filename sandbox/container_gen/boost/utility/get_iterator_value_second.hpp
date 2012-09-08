// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UTILITY_GET_ITERATOR_VALUE_SECOND_HPP_INCLUDED
#define BOOST_UTILITY_GET_ITERATOR_VALUE_SECOND_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/ref.hpp>
#include <boost/ptr_container/detail/map_iterator.hpp>
#include <boost/detail/function/get_reference.hpp>

//[reference__get_iterator_value_second_result
namespace boost {

    template <typename IterValue>
    struct get_iterator_value_second_result
    {
        typedef // implementation_defined
                //<-
                typename ::std::tr1::remove_pointer<
                    typename ::boost::unwrap_reference<
                        BOOST_TYPEOF_TPL(
                            ::boost::ref(
                                ::boost::detail::get_reference<
                                    IterValue
                                >().second
                            )
                        )
                    >::type
                >::type&
                //->
                type;
    };
}  // namespace boost
//]

namespace boost { namespace detail {

    template <typename IterValue>
    class get_iterator_value_second_helper
    {
     public:
        typedef IterValue&
                argument_type;
        typedef typename get_iterator_value_second_result<IterValue>::type
                result_type;

        result_type operator()(argument_type itr) const;

     private:
        static result_type _evaluate(argument_type arg, ::boost::mpl::true_);

        static result_type _evaluate(argument_type arg, ::boost::mpl::false_);
    };

    template <typename IterValue>
    inline typename get_iterator_value_second_helper<IterValue>::result_type
        get_iterator_value_second_helper<IterValue>::operator()(
            argument_type arg
        ) const
    {
        typedef typename ::std::tr1::remove_const<IterValue>::type _value_type;

        return _evaluate(
            arg
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

    template <typename IterValue>
    inline typename get_iterator_value_second_helper<IterValue>::result_type
        get_iterator_value_second_helper<IterValue>::_evaluate(
            argument_type arg
          , ::boost::mpl::true_
        )
    {
        return *arg.second;
    }

    template <typename IterValue>
    inline typename get_iterator_value_second_helper<IterValue>::result_type
        get_iterator_value_second_helper<IterValue>::_evaluate(
            argument_type arg
          , ::boost::mpl::false_
        )
    {
        return arg.second;
    }
}}  // namespace boost::detail

//[reference__get_iterator_value_second
namespace boost {

    template <typename IterValue>
    typename get_iterator_value_second_result<IterValue>::type
        get_iterator_value_second(IterValue& value);

    //<-
    template <typename IterValue>
    inline typename get_iterator_value_second_result<IterValue>::type
        get_iterator_value_second(IterValue& value)
    {
        return detail::get_iterator_value_second_helper<IterValue>()(value);
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_UTILITY_GET_ITERATOR_VALUE_SECOND_HPP_INCLUDED

