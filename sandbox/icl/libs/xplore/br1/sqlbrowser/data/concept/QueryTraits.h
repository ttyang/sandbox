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

    void setSqlStatement(const tRepr& sql){ m_aSqlText = sql; }

    tIteratorRange range()const        { return m_keyRange; }
    tRepr          sqlStatement()const { return m_aSqlText; }

private:
    tRepr          m_aSqlText;
    tIteratorRange m_keyRange;
};


struct SqlStatement
{};

template<class KeyIterator>
class SqlWithVarBinding
{
public:
    // This Method requires a container for the binding of variables
    // in the sql statement. Therefore an iterator type must be
    // available
    typedef KeyIterator iterator;
    typedef boost::iterator_range<KeyIterator> tKeyRange;

private:
    tKeyRange m_keyRange;
};

//! data::Specificator. A Description of the data that allows to
//! to define how a DomainObject can be retrieved.
template<class Method, class DomainObject>
class Specificator
{
};

//! data::Specificator_ModeledMy<ASpecificator>
//! This describes the Specification of data via a given
//! method only
template<class ASpecificator>
struct Specificator_ModeledBy
{
    typedef typename ASpecificator tSpecificator;
    typedef typename tSpecificator::tMethod tMethod;
    typedef typename tSpecificator::tQuery  tQuery;

    static tQuery createQuery(const tSpecificator&);
};

template<>
struct Specificator<SqlStatement, dag::db::EdgeType>
{
};

template<class KeyIterator>
struct Specificator<SqlWithVarBinding<KeyIterator>, dag::db::ObjectType>
{
};

template<class Method, class DomainObject>
struct Specificator_ModeledBy< Specificator<Method, DomainObject> >
{
    typedef Specificator_ModeledBy   tSpecificator;
    typedef typename Method          tMethod;
    typedef typename tMethod::tQuery tQuery;

    static tQuery createQuery(const tSpecificator& spec)
    { spec.createQuery(); }
};




} // namespace data
