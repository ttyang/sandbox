// MISC Multi Index Specialized Containers
//
// Copyright 2006 Matias Capeletto
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/misc for library home page.

/// \file detail/config/template_class_friend.hpp
/// \brief Macro to cope with friend declaration of template classes.

#ifndef BOOST_BIMAP_DETAIL_CONFIG_TEMPLATE_CLASS_FRIEND_HPP
#define BOOST_BIMAP_DETAIL_CONFIG_TEMPLATE_CLASS_FRIEND_HPP

#include <boost/config.hpp>

#if defined(BOOST_MSVC)
/********************************************************************************/
#define A_BOOST_BIMAP_TEMPLATE_CLASS_FRIEND(TYPE)                                  \
    typedef TYPE template_class_friend;                                          \
    friend class template_class_friend;
/********************************************************************************/
#else
/********************************************************************************/
#define A_BOOST_BIMAP_TEMPLATE_CLASS_FRIEND(TYPE)                                  \
    friend class TYPE;
/********************************************************************************/
#endif

#endif // BOOST_BIMAP_DETAIL_CONFIG_TEMPLATE_CLASS_FRIEND_HPP
