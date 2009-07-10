/*=============================================================================
    Copyright (c) 2005 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_MAP_FWD_HPP
#define BOOST_FUSION_CONTAINER_MAP_MAP_FWD_HPP

#include <boost/fusion/container/map/limits.hpp>
#include <boost/fusion/support/template.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    VARIADIC_TEMPLATE_WITH_DEFAULT(FUSION_MAX_MAP_SIZE)
    struct map;
}}

#endif
