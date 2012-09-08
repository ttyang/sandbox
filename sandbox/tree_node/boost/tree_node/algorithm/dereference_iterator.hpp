// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_DEREFERENCE_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_ALGORITHM_DEREFERENCE_ITERATOR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/utility/get_iterator_second.hpp>
#include <boost/detail/metafunction/has_first_type.hpp>
#include <boost/detail/metafunction/has_second_type.hpp>

namespace boost { namespace tree_node { namespace _detail {

    template <typename Iterator>
    class dereference_iterator_helper
    {
        typedef typename ::boost::iterator_value<Iterator>::type
                _value_type;
        typedef typename ::boost::mpl::and_<
                    typename ::boost::detail::metafunction::has_first_type<
                        _value_type
                    >::type
                  , typename ::boost::detail::metafunction::has_second_type<
                        _value_type
                    >::type
                >::type
                _is_associative;

     public:
        typedef Iterator
                argument_type;
        typedef typename ::boost::mpl::eval_if<
                    _is_associative
                  , ::boost::get_iterator_second_result<Iterator>
                  , ::boost::iterator_reference<Iterator>
                >::type
                result_type;

        result_type operator()(argument_type itr) const;

     private:
        static result_type _evaluate(Iterator itr, ::boost::mpl::true_);

        static result_type _evaluate(Iterator itr, ::boost::mpl::false_);
    };

    template <typename Iterator>
    inline typename dereference_iterator_helper<Iterator>::result_type
        dereference_iterator_helper<Iterator>::operator()(
            argument_type itr
        ) const
    {
        return this->_evaluate(itr, _is_associative());
    }

    template <typename Iterator>
    inline typename dereference_iterator_helper<Iterator>::result_type
        dereference_iterator_helper<Iterator>::_evaluate(
            Iterator itr
          , ::boost::mpl::true_
        )
    {
        return ::boost::get_iterator_second(itr);
    }

    template <typename Iterator>
    inline typename dereference_iterator_helper<Iterator>::result_type
        dereference_iterator_helper<Iterator>::_evaluate(
            Iterator itr
          , ::boost::mpl::false_
        )
    {
        return *itr;
    }
}}}  // namespace boost::tree_node::_detail

//[reference__dereference_iterator
namespace boost { namespace tree_node {

//<-
#if 0
//->
    template <typename Iterator>
    implementation_defined dereference_iterator(Iterator itr);
//<-
#endif
//->

    //<-
    template <typename Iterator>
    inline typename _detail::dereference_iterator_helper<Iterator>::result_type
        dereference_iterator(Iterator itr)
    {
        return _detail::dereference_iterator_helper<Iterator>()(itr);
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ALGORITHM_DEREFERENCE_ITERATOR_HPP_INCLUDED

