/*==============================================================================
    Copyright (c) 2005 Joel de Guzman
    Copyright (c) 2009-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_LIST_LIST_FWD_HPP
#define BOOST_FUSION_CONTAINER_LIST_LIST_FWD_HPP

#include <boost/fusion/support/internal/base.hpp>
#include <boost/fusion/container/list/limits.hpp>
#include <boost/fusion/support/internal/template.hpp>

namespace boost { namespace fusion
{
    struct list_tag;
    struct cons_tag;

    VARIADIC_TEMPLATE_WITH_DEFAULT(FUSION_MAX_LIST_SIZE)
    struct list;

    struct nil;

    template<typename Car, typename Cdr=nil>
    struct cons;
}}

#endif
