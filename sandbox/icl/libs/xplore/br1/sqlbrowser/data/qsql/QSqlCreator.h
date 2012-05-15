/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbType.h"

namespace data
{

typedef dag::db::tString tString;

template<class Object>class QSqlCreator;

//==============================================================================
//= Concept: data::Creator Spec: QSqlCreator
//==============================================================================
template<class Object>
struct CreatorTraits<Object, QSqlCreator<Object> >
{
    typedef QSqlCreator<Object> tCreator;
    typedef typename tCreator::const_iterator const_iterator;
    typedef typename tCreator::tQuery   tQuery;

    static tQuery createQuery();
    static Object create(iterator);
};

template<>
class QSqlCreator<dag::db::EdgeType>
{
public:
    typedef dag::db::EdgeType tObject;

    tString createQuery()const
    {
        return //JODO generate the query from data
            "SELECT ...";
    }

    tObject create(const_iterator it)
    {
        return dag::db::EdgeType();
    }
};



} // namespace data
