/****************************************************************************
**
**
****************************************************************************/

#pragma once



#include <QtSql>
#include <QSqlDatabase.h>
#include <QString.h>

#include "Dag/DbType.h"
#include "gen/NameGenerator.h"

namespace gen
{

class DbGenerator
{
public:
    typedef dag::db::tKey tKey;

    enum {
        a_text       =  1
      , a_integer    =  2
      , a_real       =  3
      , a_artist     = 21
      , a_title      = 22
      , a_recording  = 23
      , c_artists    = 24
      , c_genre      = 25
      , r_composed   = 26
      , r_performed  = 27
      , r_recorded   = 28
      , r_located_at = 29
      , c_album      = 30
      , r_contains   = 31
    };

    enum {
        A_Name       =  1
      , A_Duration   =  2
      , A_Year       =  31
      , A_Position   =  32
    };

    DbGenerator(const QSqlDatabase& db):
        m_aDb(db), m_aQuery("", m_aDb){}

    bool generate();
    void clean();
    void generateTables();

    void generateTypeData();

    void generateTypeViews();

private:
    bool exec(const char* sql);

    //void generateTypeData();
    void generateTypeTraits();
    void generateObjectTypes();
    void generateEdgeTypes();
    void generateAttributes();

private:
    QSqlDatabase m_aDb;
    QSqlQuery    m_aQuery;
    QSqlError    m_aLastError;
    tString      m_aFailingSql;
};

} // namespace data
