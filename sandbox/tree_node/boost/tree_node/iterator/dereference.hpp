// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ITERATOR_DEREFERENCE_HPP
#define BOOST_TREE_NODE_ITERATOR_DEREFERENCE_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/utility/get_iterator_second.hpp>
#include <boost/detail/metafunction/has_first_type.hpp>
#include <boost/detail/metafunction/has_second_type.hpp>

namespace boost { namespace tree_node { namespace _detail {

    template <typename Iterator>
    class deref_iterator_helper
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
    inline typename deref_iterator_helper<Iterator>::result_type
        deref_iterator_helper<Iterator>::operator()(
            argument_type itr
        ) const
    {
        return this->_evaluate(itr, _is_associative());
    }

    template <typename Iterator>
    inline typename deref_iterator_helper<Iterator>::result_type
        deref_iterator_helper<Iterator>::_evaluate(
            Iterator itr
          , ::boost::mpl::true_
        )
    {
        return ::boost::get_iterator_second(itr);
    }

    template <typename Iterator>
    inline typename deref_iterator_helper<Iterator>::result_type
        deref_iterator_helper<Iterator>::_evaluate(
            Iterator itr
          , ::boost::mpl::false_
        )
    {
        return *itr;
    }
}}}  // namespace boost::tree_node::_detail

//[reference__tree_node__result_of__dereference_iterator
namespace boost { namespace tree_node { namespace result_of {

    template <typename Iterator>
    struct dereference_iterator
    {
//<-
#if 0
//->
        typedef unspecified type;
//<-
#endif
        typedef typename ::boost::tree_node::_detail::deref_iterator_helper<
                    Iterator
                >::result_type
                type;

        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,dereference_iterator,(Iterator))
//->
    };
}}}  // namespace boost::tree_node::result_of
//]

//[reference__tree_node__dereference_iterator
namespace boost { namespace tree_node {

    template <typename Iterator>
    typename result_of::dereference_iterator<Iterator>::type
        dereference_iterator(Iterator itr);

    //<-
    template <typename Iterator>
    inline typename result_of::dereference_iterator<Iterator>::type
        dereference_iterator(Iterator itr)
    {
        return _detail::deref_iterator_helper<Iterator>()(itr);
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ITERATOR_DEREFERENCE_HPP

