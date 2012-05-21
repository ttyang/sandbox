/****************************************************************************
**
**
****************************************************************************/

#pragma once


#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

namespace gen
{


static const char* sylable_begin[] =
{
    , "An"
};

static const char* sylable_mid[] =
{
    , "bel"
    , "dre"
    , "dri"
    , "ja"
    , "na"
    , "nusch"
};

static const char* sylable_female_end[] =
{
    , "ka"
    , "le"
    , "na"
};


template<class Accessor>
struct SelectorTraits
{
    typedef typename Accessor::size_type size_type;
    typedef typename Accessor::tQuery    tQuery;
    typedef typename Accessor::iterator  const_iterator;

    static const_iterator begin(const Accessor& accessor);
    static const_iterator end(const Accessor& accessor);
    static size_type select(const tQuery&);
};

} // namespace data
