/* Copyright Joaqu�n M L�pez Mu�oz 2003-2004. Use, modification, and distribution
 * are subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/indexed_set for library home page.
 */

#ifndef BOOST_INDEXED_SET_INDEX_ARGS_HPP
#define BOOST_INDEXED_SET_INDEX_ARGS_HPP

#include <boost/config.hpp> /* keep it first to prevent some nasty warnings in MSVC */
#include <boost/indexed_set/tag.hpp>
#include <boost/mpl/apply_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <functional>

namespace boost{

namespace indexed_sets{

namespace detail{

/* Index specifiers can be instantiated in two forms:
 *
 *   (unique|non_unique)<
 *     KeyFromValue,Compare=std::less<KeyFromValue::result_type> >
 *   (unique|non_unique)<
 *     TagList,KeyFromValue,Compare=std::less<KeyFromValue::result_type> >
 *
 * index_args implements the machinery to accept this argument-dependent polymorphism.
 */

struct null_arg{};

template<typename T>
struct not_is_null_arg
{
  BOOST_STATIC_CONSTANT(bool,value=!(is_same<null_arg,T>::value));
};

template<typename KeyFromValue>
struct index_args_default_compare
{
  typedef std::less<typename KeyFromValue::result_type> type;
};

template<typename Arg1,typename Arg2,typename Arg3>
struct index_args
{
  typedef is_tag<Arg1> full_form;

  typedef typename mpl::if_<
    full_form,
    Arg1,
    tag< > >::type                                   tag_list_type;
  typedef typename mpl::if_<
    full_form,
    Arg2,
    Arg1>::type                                      key_from_value_type;
  typedef typename mpl::if_<
    full_form,
    Arg3,
    Arg2>::type                                      supplied_compare_type;
  typedef typename mpl::apply_if<
    is_same<supplied_compare_type,null_arg>,
    index_args_default_compare<key_from_value_type>,
    mpl::identity<supplied_compare_type>
  >::type                                            compare_type;

  BOOST_STATIC_ASSERT(is_tag<tag_list_type>::value);
  BOOST_STATIC_ASSERT(not_is_null_arg<key_from_value_type>::value);
  BOOST_STATIC_ASSERT(not_is_null_arg<compare_type>::value);
};

} /* namespace indexed_sets::detail */

} /* namespace indexed_sets */

} /* namespace boost */

#endif