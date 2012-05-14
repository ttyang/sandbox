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
template<class Accessor, class Query>
struct SelectorTraits
{
    typedef typename Accessor::size_type size_type;
    typedef typename Accessor::iterator  iterator;

    static iterator begin(const Accessor& accessor);
    static iterator end(const Accessor& accessor);
    static size_type select(const Query&);
};

} // namespace data
