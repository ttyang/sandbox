/****************************************************************************
**
**
****************************************************************************/

#pragma once

#include <QSqlRecord.h>
#include <QSqlField.h>

#include "Dag/DbType.h"
#include "data/concept/CreatorTraits.h"
#include "data/concept/GetCreator.h"
#include "data/qsql/QSqlSelector.h"

namespace data
{

typedef dag::db::tString tString;


template<class Object, class Accessor>
class QSqlCreator;

template<>
class QSqlCreator<dag::db::EdgeType, QSqlSelector>
{
public:
    enum { eKey=0, eRefSourceType, eRefRelationType, eRefTargetType, eName };

    typedef QSqlCreator       type;
    typedef dag::db::EdgeType tObject;
    typedef QSqlSelector      tAccessor;

    typedef tAccessor::tResultSet     tResultSet;
    typedef tAccessor::const_iterator const_iterator;

    static tString createQuery()
    {
        return
            "select EdgeType.key, EdgeType.refSourceType, EdgeType.refRelationType, EdgeType.refTargetType from EdgeType ";
    }

    static tObject create(const_iterator it)
    {
        return dag::db::EdgeType( (*it).field(eKey).value().toInt()
                                 ,(*it).field(eRefSourceType).value().toInt()
                                 ,(*it).field(eRefRelationType).value().toInt()
                                 ,(*it).field(eRefTargetType).value().toInt()
                                 ,(*it).field(eName).value().toString()
                                );
    }
};


template<>
class QSqlCreator<dag::db::ObjectType, QSqlSelector>
{
public:
    enum { eKey=0, eTraits, eName };

    typedef QSqlCreator         type;
    typedef dag::db::ObjectType tObject;
    typedef QSqlSelector        tAccessor;

    typedef tAccessor::tResultSet     tResultSet;
    typedef tAccessor::const_iterator const_iterator;

    static tString createQuery()
    {
        return
            "select ObjectType.key, ObjectType.Traits, ObjectType.Name from ObjectType where ObjectType.key = ? ";
    }

    static tObject create(const_iterator it)
    {
        return dag::db::ObjectType( (*it).field(eKey).value().toInt()
                                   ,(*it).field(eTraits).value().toUInt()
                                   ,(*it).field(eName).value().toString()
                                  );
    }
};


template<class Object>
struct GetCreator<Object, QSqlSelector>
{
    typedef QSqlCreator<Object, QSqlSelector> type;
};




//==============================================================================
//= Concept: data::Creator Partial Specialisation: QSqlCreator
//==============================================================================

template<class Object, class Accessor>
struct CreatorTraits<Object, QSqlCreator<Object, Accessor> >
{
    typedef QSqlCreator<Object,Accessor> tCreator;
    typedef typename Accessor::const_iterator const_iterator;

    static tString createQuery(){ return tCreator::createQuery(); }
    static Object create(const_iterator it){ return tCreator::create(it); }
};


} // namespace data
