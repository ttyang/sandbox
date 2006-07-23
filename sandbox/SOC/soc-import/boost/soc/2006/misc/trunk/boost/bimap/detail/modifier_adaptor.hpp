// Boost.bimap
//
// Copyright 2006 Matias Capeletto
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/bimap for library home page.

/// \file detail/modifier_adaptor.hpp
/// \brief A unary functor modifier adaptor.

#ifndef BOOST_BIMAP_DETAIL_MODIFIER_ADAPTOR_HPP
#define BOOST_BIMAP_DETAIL_MODIFIER_ADAPTOR_HPP

#include <functional>

namespace boost {
namespace bimap {
namespace detail {

template< class Modifier, class NewArgument, class FirstExtractor, class SecondExtractor >
struct relation_modifier_adaptor :
    public std::unary_function<NewArgument,bool>
{
    relation_modifier_adaptor( Modifier m ) : mod(m) {}
    relation_modifier_adaptor( Modifier m, FirstExtractor fea, SecondExtractor sea ) :
        mod(m), fe(fea), se(sea) {}

    void operator()( NewArgument & x ) const
    {
        mod( fe( x ), se( x ) );
    }

    private:
    Modifier mod;
    FirstExtractor fe;
    SecondExtractor se;
};

/*
template< class Modifier, class NewArgument, class Extractor >
struct modifier_adaptor :
    public std::unary_function<NewArgument,bool>,
    protected Extractor
{

    modifier_adaptor( Modifier m ) : Modifier(m) {}
    modifier_adaptor( Modifier m, Extractor e ) : Modifier(m), Extractor(e) {}

    void operator()( NewArgument & x ) const
    {
        mod( Extractor::operator()( x ) );
    }

    private:
    Modifier mod;
};
*/

} // namespace detail
} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_MODIFIER_ADAPTOR_HPP
