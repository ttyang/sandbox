/****************************************************************************
**
**
****************************************************************************/

#pragma once

//std
#include <cstddef>

#include <QString.h>
#include <boost/range.hpp>

namespace data
{

typedef QString tString;

//==============================================================================
//= Concept: Query Traits
//==============================================================================
//! The only resposibility of a Query object is to encapsulate all information
//! needed to execute the Query
template<class Query>
struct QueryTraits
{
    typedef tString tRepr;
};

class SqlQuery
{
public:
    typedef tString tRepr;
};

template<class Iterator>
class KeyBinding_SqlQuery
{
public:
    typedef tString tRepr;
    typedef typename boost::iterator_range<Iterator> tIteratorRange;

    KeyBinding_SqlQuery(const tIteratorRange& keyRange)
        : m_keyRange(keyRange)
    {}

private:
    tIteratorRange m_keyRange;
};


} // namespace data
