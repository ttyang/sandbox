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

    static SqlQuery::tRepr createQuery()
    {
        return
            "select EdgeType.key, EdgeType.refSourceType, EdgeType.refRelationType, EdgeType.refTargetType, EdgeType.Name from EdgeType ";
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


template<class Object, class Accessor, class KeyIterator>
class KeyBinding_QSqlCreator;

template<class KeyIterator>
class KeyBinding_QSqlCreator<dag::db::ObjectType, KeyBinding_QSqlSelector<KeyIterator>, KeyIterator>
{
public:
    enum { eKey=0, eTraits, eName };

    typedef KeyBinding_QSqlCreator type;
    typedef KeyBinding_SqlQuery<KeyIterator>   tQuery;
    typedef boost::iterator_range<KeyIterator> tKeyRange;
    typedef dag::db::ObjectType     tObject;
    typedef KeyBinding_QSqlSelector<KeyIterator> tAccessor;

    typedef typename tAccessor::tResultSet     tResultSet;
    typedef typename tAccessor::const_iterator const_iterator;

    static tQuery createQuery(const tKeyRange& range)
    {
        tQuery query(range);
        query.setSqlStatement(
            "select ObjectType.key, ObjectType.Traits, ObjectType.Name "
            "from ObjectType where ObjectType.key = ? "
            );
        return query;
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


template<class Object, class Iter>
struct GetCreator<Object, KeyBinding_QSqlSelector<Iter> >
{
    typedef KeyBinding_QSqlCreator<Object, KeyBinding_QSqlSelector<Iter>, Iter> type;
};




//==============================================================================
//= Concept: data::Creator Partial Specialisation: QSqlCreator
//==============================================================================

template<class Object, class Accessor>
struct CreatorTraits<Object, QSqlCreator<Object, Accessor> >
{
    typedef QSqlCreator<Object,Accessor> tCreator;
    typedef typename Accessor::const_iterator const_iterator;

    static SqlQuery::tRepr createQuery(){ return tCreator::createQuery(); }
    static Object create(const_iterator it){ return tCreator::create(it); }
};


template<class Object, class Accessor, class KeyIterator>
struct KeyBinding_CreatorTraits<Object, KeyBinding_QSqlCreator<Object, Accessor, KeyIterator>, KeyIterator>
{
    typedef KeyBinding_QSqlCreator<Object,Accessor,KeyIterator> tCreator;
    typedef typename Accessor::const_iterator         const_iterator;
    typedef          KeyBinding_SqlQuery<KeyIterator> tQuery;
    typedef typename tQuery::tIteratorRange           tIteratorRange;

    //! Creates a Query to access domain Objects for a range of Key iterators
    static tQuery createQuery(const tIteratorRange& range){ return tCreator::createQuery(range); }

    //! Creates a domain Object from an Accessor's const_iterator
    static Object create(const_iterator it){ return tCreator::create(it); }
};



} // namespace data
