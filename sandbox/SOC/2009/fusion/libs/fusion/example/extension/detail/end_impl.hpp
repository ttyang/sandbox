/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef 
#define 

#include "../example_struct_iterator.hpp"

namespace example
{
    struct example_sequence_tag;
}

namespace boost { namespace fusion {
    
    namespace extension
    {
        template<typename>
        struct end_impl;

        template<>
        struct end_impl<example::example_sequence_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef example::example_struct_iterator<Sequence, 2> type;

                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif
