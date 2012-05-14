/****************************************************************************
**
**
****************************************************************************/

#pragma once


namespace data
{

//==============================================================================
//= Concept: data::Creator Traits
//==============================================================================
template<class Object, class Accessor>
struct CreatorTraits
{
    typedef typename Accessor::iterator iterator;
    typedef typename Accessor::tQuery   tQuery;

    static tQuery createQuery();
    static Object create(iterator);
};

} // namespace data
