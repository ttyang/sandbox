/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbType.h"
#include "data/concept/QueryTraits.h"

namespace data
{

typedef dag::db::tString tString;

//==============================================================================
//= Concept: data::Creator Traits
//==============================================================================
//! A creator creates (Domain)Objects for a Given Accessor
//! The Accessor encapsulates the Access to a file or data base.
template<class Object, class Accessor>
struct CreatorTraits
{
    typedef typename Accessor::const_iterator const_iterator;
    typedef SqlQuery::tRepr   tQuery;

    //! Creates a Query to access domain Objects
    static tQuery createQuery();

    //! Creates a domain Object from an Accessor's const_iterator
    static Object create(const_iterator);
};

template<class Object, class Accessor, class KeyIterator>
struct KeyBinding_CreatorTraits
{
    typedef typename Accessor::const_iterator         const_iterator;
    typedef typename KeyBinding_SqlQuery<KeyIterator> tQuery;
    typedef typename tQuery::tIteratorRange           tIteratorRange;

    //! Creates a Query to access domain Objects
    static tQuery createQuery(const tIteratorRange& range);

    //! Creates a domain Object from an Accessor's const_iterator
    static Object create(const_iterator);
};

} // namespace data
