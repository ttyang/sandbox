//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERT_TO_PAIR__HPP
#define BOOST_CONVERT_TO_PAIR__HPP

#include <string>
#include <boost/conversion/convert_to.hpp>
#include <boost/convert/convert.hpp>

namespace boost {

    namespace partial_specialization_workaround {

        template<typename T, typename CharT, typename Traits, typename Alloc>
        struct convert_to< std::basic_string<CharT,Traits,Alloc>, T > {
            inline static std::basic_string<CharT,Traits,Alloc> apply(T const & from)
            {
                return convert<std::basic_string<CharT,Traits,Alloc> >::from(from);
            }
        }
        template<typename T, typename CharT, typename Traits, typename Alloc>
        struct assign_to< std::basic_string<CharT,Traits,Alloc>, T > {
            inline static std::basic_string<CharT,Traits,Alloc>& apply(const T& from, std::basic_string<CharT,Traits,Alloc>& to)
            {
                to = convert<std::basic_string<CharT,Traits,Alloc> >::from(from);
                return to;
            }
        };
        template<typename T, typename CharT, typename Traits, typename Alloc>
        struct convert_to< T, std::basic_string<CharT,Traits,Alloc>> {
            inline static T apply(std::basic_string<CharT,Traits,Alloc> const & from)
            {
                return convert<T>::from(from);
            }
        };
        template<typename T, typename CharT, typename Traits, typename Alloc>
        struct assign_to< T, std::basic_string<CharT,Traits,Alloc>> {
            inline static void apply(const std::basic_string<CharT,Traits,Alloc>& from, T& to)
            {
                to = convert<T>::from(from);
                return to;
            }
        };

    }
}

#endif

