/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include "Dag/DbType.h"
#include "data/concept/CreatorTraits.h"
#include "data/qsql/QSqlSelector.h"

namespace data
{

typedef dag::db::tString tString;


template<class Object, class Accessor>
class QSqlCreator;
/*
{
public:
    typedef QSqlCreator       type;
    typedef Object            tObject;
    typedef Accessor          tAccessor;

    typedef typename tAccessor::tResultSet     tResultSet;
    typedef typename tAccessor::const_iterator const_iterator;

    static tString createQuery()
    {
        return "...";
    }

    static tObject create(const_iterator it)
    {
        return tObject();
    }
};
*/

template<>
class QSqlCreator<dag::db::EdgeType, QSqlSelector>
{
public:
    typedef QSqlCreator       type;
    typedef dag::db::EdgeType tObject;
    typedef QSqlSelector      tAccessor;

    typedef tAccessor::tResultSet     tResultSet;
    typedef tAccessor::const_iterator const_iterator;

    static tString createQuery()
    {
        return "SELECT ...";
    }

    static tObject create(const_iterator it)
    {
        return dag::db::EdgeType();
    }
};



template<class Object, class Accessor>class QSqlCreator;

//==============================================================================
//= Concept: data::Creator Spec: QSqlCreator
//==============================================================================

template<class Object, class Accessor>
struct CreatorTraits<Object, QSqlCreator<Object, Accessor> >
{
    typedef QSqlCreator<Object,Accessor> tCreator;
    typedef typename Accessor::const_iterator const_iterator;

    static tString createQuery(){ return tCreator::createQuery(); }
    static Object create(const_iterator it){ return tCreator::create(it); }
};


/*
template<>
struct CreatorTraits<dag::db::EdgeType, QSqlCreator<dag::db::EdgeType, data::QSqlSelector> >
{
    typedef dag::db::EdgeType  tObject;
    typedef data::QSqlSelector tAccessor;
    typedef QSqlCreator<dag::db::EdgeType, data::QSqlSelector> tCreator;
    typedef tAccessor::const_iterator const_iterator;

    static tString createQuery(){ tCreator::createQuery(); }
    static tObject create(const_iterator it){ return tCreator::create(it); }
};
*/

} // namespace data
