/****************************************************************************
**
**
****************************************************************************/

#pragma once

//std
#include <cstddef>
//boost
//qt
#include <QSqlQuery.h>

//concepts
#include "data/concept/SelectorTraits.h"


// Data access sql, xml, file etc. lives in namespace data
namespace data
{

class QSqlSelector
{
public:
    typedef QSqlSelector      type;
    typedef std::size_t       size_type;
    typedef QVector<QVariant> tResultSet;
    typedef tResultSet::const_iterator const_iterator;
    typedef QSqlQuery         tQuery;

    const_iterator begin()const{ return m_aResultSet.begin(); }
    const_iterator end()  const{ return m_aResultSet.end();   }
    size_type select(const tQuery&);

private:
    tResultSet m_aResultSet;
};


//==============================================================================
//= Concept: data::Selector Specialisation: QSqlSelector
//==============================================================================
template<>
struct SelectorTraits<QSqlSelector, QSqlQuery>
{
    typedef std::size_t size_type;
    typedef QSqlSelector::const_iterator const_iterator;

    static const_iterator begin(const QSqlSelector& accessor){ return accessor.begin(); }
    static const_iterator end  (const QSqlSelector& accessor){ return accessor.end();   };
    static size_type select(const QSqlQuery&);
};

} // namespace data
