/****************************************************************************
**
**
****************************************************************************/

#pragma once


#include <boost/icl/interval_set.hpp>

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
    typedef unsigned int  tObjectType;
    typedef unsigned int  tAttribute;
    typedef boost::icl::interval_set<tKey> tKeySet;
    typedef tKeySet::interval_type tInterval;

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

    enum {
        R_artist_composed_title    = 1
      , R_artist_performed_record  = 2
      , R_title_recorded_as_record = 3
      , R_record_located_at_url    = 4
      , R_album_contains_record    = 5
    };

    enum {
        minSyllables = 2
      , maxSyllables = 5
    };

    DbGenerator(const QSqlDatabase& db):
        m_aDb(db), m_aQuery("", m_aDb)
      , m_aSomeName(minSyllables, maxSyllables)
    {
        configure();
    }

    void clear();
    void clearDb();
    bool generate();
    void generateTables();
    void generateTypeData();
    void generateTypeViews();

    void generateObjects();
    void generateRelationships();

    void generateArtists(int);
    void generateTitles(int);

    void generateArtistComposedTitle();

private:
    void configure();
    bool exec(const tString& sql);

    //void generateTypeData();
    void generateTypeTraits();
    void generateObjectTypes();
    void generateEdgeTypes();
    void generateAttributes();

    tKey insertObject();
    void insertVertex(tKey aKey, tObjectType eObjectType);
    void insertVarCharObject(tKey aKey, tAttribute eAttr, const tString& value);
    void insertIntObject(tKey aKey, tAttribute eAttr, int value);
    void insertEdge(tKey aEdgeKey, tKey aEdgeTypeKey, tKey aSrcKey, tKey aTrgKey);

    tKey generateArtist();
    tKey generateTitle();

    void makeComposersRange();
    void assignComposers(tKey aTitle);

private:
    int m_iArtists;
    int m_iTitles;

    QSqlDatabase  m_aDb;
    QSqlQuery     m_aQuery;
    QSqlError     m_aLastError;
    tString       m_aFailingSql;
    NameGenerator m_aSomeName;

    tKeySet       m_aArtists;
    tInterval     m_aComposersRange;
    tKeySet       m_aTitles;
};

} // namespace data
