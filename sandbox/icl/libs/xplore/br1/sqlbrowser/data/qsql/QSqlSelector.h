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
#include "data/concept/Selector.h"


// Data access sql, xml, file etc. lives in namespace data
namespace data
{

class QSqlSelector
{
public:
    typedef QVector<QVariant> type;
    typedef typename tResultSet::iterator iterator;
    typedef QVector<QVariant> tResultSet;
    typedef QSqlQuery         tQuery;

    iterator begin(){ return m_aResultSet.begin(); }
    iterator end()  { return m_aResultSet.end();   }
    size_type select(const tQuery&);

private:
    tResultSet m_aResultSet;
};


//==============================================================================
//= Concept: DataSelector Spec: QSqlSelector
//==============================================================================
template<>
struct SelectorTraits<QSqlSelector, class QSqlQuery>
{
    typedef std::size_t size_type;
    typedef typename QSqlSelector::iterator iterator;

    static iterator begin(const QSqlSelector& accessor){ return accessor.begin(); }
    static iterator end  (const QSqlSelector& accessor){ return accessor.end();   };
    static size_type select(const QSqlQuery&);
};

} // namespace data
