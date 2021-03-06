/* Copyright Joaqu�n M L�pez Mu�oz 2003-2004. Use, modification, and distribution
 * are subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/indexed_set for library home page.
 */

#ifndef BOOST_INDEXED_SETS_INDEX_LIST_HPP
#define BOOST_INDEXED_SETS_INDEX_LIST_HPP

#include <boost/config.hpp> /* keep it first to prevent some nasty warnings in MSVC */
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/facilities/intercept.hpp> 
#include <boost/preprocessor/repetition/enum_binary_params.hpp> 
#include <boost/preprocessor/repetition/enum_params.hpp> 
#include <boost/type_traits/is_base_and_derived.hpp>

/* An alias to mpl::vector used to hide MPL from the user.
 * index_list contains the index traits types for instantiation
 * of a indexed_set.
 */

/* This user_definable macro limits the number of elements of an index list; useful
 * for shortening resulting symbol names (MSVC++ 6.0, for instance, has problems
 * coping with very long symbol names.)
 */

#if !defined(BOOST_INDEXED_SET_LIMIT_INDEX_LIST_SIZE)
#if defined(BOOST_MSVC)&&(BOOST_MSVC<1300)
#define BOOST_INDEXED_SET_LIMIT_INDEX_LIST_SIZE 5
#else
#define BOOST_INDEXED_SET_LIMIT_INDEX_LIST_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif
#endif

#if BOOST_INDEXED_SET_LIMIT_INDEX_LIST_SIZE<BOOST_MPL_LIMIT_VECTOR_SIZE
#define BOOST_INDEXED_SET_INDEX_LIST_SIZE BOOST_INDEXED_SET_LIMIT_INDEX_LIST_SIZE
#else
#define BOOST_INDEXED_SET_INDEX_LIST_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

namespace boost{

namespace indexed_sets{

namespace detail{

struct index_list_marker{};

template<typename T>
struct is_index_list
{
  BOOST_STATIC_CONSTANT(bool,value=(is_base_and_derived<index_list_marker,T>::value));
};

} /* namespace indexed_sets::detail */

template<
  BOOST_PP_ENUM_BINARY_PARAMS(
    BOOST_INDEXED_SET_INDEX_LIST_SIZE,
    typename T,
    =mpl::void_ BOOST_PP_INTERCEPT) 
>
struct index_list:private detail::index_list_marker
{
  typedef mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_INDEXED_SET_INDEX_LIST_SIZE,T)> type;
};

/* MPL-friendly variant of index_list for metaprogramming purposes */

template<typename MplFwdSequence>
struct mpl_index_list:private detail::index_list_marker
{
  typedef MplFwdSequence type;
};

} /* namespace indexed_sets */

} /* namespace boost */

#undef BOOST_INDEXED_SET_INDEX_LIST_SIZE

#endif
