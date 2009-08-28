/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef 
#define 

namespace example
{
    struct example_struct_iterator_tag;

    template<typename Struct, int Pos>
    struct example_struct_iterator;
}

namespace boost { namespace fusion {

    namespace extension
    {
        template<typename>
        struct prior_impl;

        template<>
        struct prior_impl<example::example_struct_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::struct_type struct_type;
                typedef typename Iterator::index index;
                typedef example::example_struct_iterator<struct_type, index::value - 1> type;

                static type
                call(Iterator const& i)
                {
                    return type(i.struct_);
                }
            };
        };
    }
}}

#endif
