/****************************************************************************
**
**
****************************************************************************/

#pragma once

//std
#include <cstddef>
//boost
//qt
#include <QSqlDatabase.h>
#include <QSqlQuery.h>
#include <QSqlRecord.h>

//concepts
#include "data/concept/SelectorTraits.h"

#include "connectionwidget.h"

// Data access sql, xml, file etc. lives in namespace data
namespace data
{

class QSqlSelector
{
public:
    typedef QSqlSelector      type;
    typedef tString           tQuery;
    typedef std::size_t       size_type;
    typedef QSqlRecord        tRecord;
    typedef QVector<tRecord>  tResultSet;
    typedef tResultSet::const_iterator const_iterator;

    const_iterator begin()const{ return m_aResultSet.begin(); }
    const_iterator end()  const{ return m_aResultSet.end();   }

    size_type select(const tQuery& querySql)
    {
        QSqlQuery query = QSqlQuery(querySql, m_aDatabase);
        query.exec();
        while(query.next())
            m_aResultSet.push_back(query.record());

        return m_aResultSet.size();
    }

    template<class KeyMap>
    size_type selectForKeys(const tQuery& querySql, const KeyMap& keyset)
    {
        QSqlQuery query(m_aDatabase);
        query.prepare(querySql);

        for(KeySet::const_iterator it = keys.begin(); it != keys.end(); ++it)
        {
            query.bindValue(querySql, (*it).first);
            query.exec();
            m_aResultSet.push_back(query.record());
        }

        return m_aResultSet.size();
    }

    void setDatabase(const QSqlDatabase& db){ m_aDatabase = db; }

private:
    tResultSet   m_aResultSet;
    QSqlDatabase m_aDatabase;
};


//==============================================================================
//= Concept: data::Selector Specialisation: QSqlSelector
//==============================================================================
template<>
struct SelectorTraits<QSqlSelector>
{
    typedef std::size_t size_type;
    typedef QSqlSelector::const_iterator const_iterator;
    typedef QSqlSelector::tQuery tQuery;

    static const_iterator begin(const QSqlSelector& accessor){ return accessor.begin(); }
    static const_iterator end  (const QSqlSelector& accessor){ return accessor.end();   }
    static size_type select(QSqlSelector& accessor, const tString& query){ return accessor.select(query); }
};

} // namespace data
