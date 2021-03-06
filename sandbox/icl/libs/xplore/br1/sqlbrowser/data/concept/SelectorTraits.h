/****************************************************************************
**
**
****************************************************************************/

#pragma once

//std
#include <cstddef>


// Data access sql, xml, file etc. lives in namespace data
namespace data
{

//==============================================================================
//= Concept: DataSelector Traits
//==============================================================================
template<class Accessor>
struct SelectorTraits
{
    typedef typename Accessor::size_type size_type;
    typedef typename Accessor::tQuery    tQuery;
    typedef typename Accessor::iterator  const_iterator;

    static const_iterator begin(const Accessor& accessor);
    static const_iterator end(const Accessor& accessor);
    static size_type select(Accessor& accessor, const tQuery&);
};

} // namespace data
