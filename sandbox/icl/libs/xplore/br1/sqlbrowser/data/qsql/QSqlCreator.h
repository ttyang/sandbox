/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbType.h"

namespace data
{

typedef dag::db::tString tString;

//==============================================================================
//= Concept: data::Creator Spec: QSqlCreator
//==============================================================================
template<class Object>
struct CreatorTraits<Object, QSqlCreator<Object> >
{
    typedef QSqlCreator<Object> tCreator;
    typedef typename tCreator::iterator iterator;
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

    tObject create(iterator it)
    {
        return dag::db::EdgeType();
    }
};



} // namespace data
