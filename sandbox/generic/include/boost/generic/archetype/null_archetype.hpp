/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_ARCHETYPE_NULL_ARCHETYPE_HPP
#define BOOST_GENERIC_ARCHETYPE_NULL_ARCHETYPE_HPP

namespace boost { namespace generic {

struct null_archetype
{
  null_archetype() = delete;
  null_archetype( null_archetype&& ) = delete;
  null_archetype( null_archetype const& ) = delete;
  ~null_archetype() = delete;
  null_archetype& operator =( null_archetype&& ) = delete;
  null_archetype& operator =( null_archetype const& ) = delete;
};

} }

#endif // BOOST_GENERIC_ARCHETYPE_NULL_ARCHETYPE_HPP
