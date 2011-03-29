/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SUPPORT_TAG_OF_FWD_HPP
#define BOOST_FUSION_SUPPORT_TAG_OF_FWD_HPP

#include <boost/fusion/support/internal/base.hpp>

namespace boost
{
    namespace fusion { namespace traits
    {
        template<typename Seq, typename Enable=void>
        struct tag_of;
    }}

    namespace mpl
    {
        template<typename>
        struct sequence_tag;
    }
}

#endif