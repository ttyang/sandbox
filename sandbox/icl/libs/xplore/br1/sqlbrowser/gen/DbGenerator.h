/****************************************************************************
**
**
****************************************************************************/

#pragma once


#include <boost/icl/map.hpp>
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
    typedef std::set<tKey>                 tKeySet;
    typedef boost::icl::map<tKey, tKeySet> tKey2Keys;
    typedef boost::icl::map<tKey, tString> tKey2Name;

    typedef boost::icl::interval_set<tKey> tInterKeySet;
    typedef tInterKeySet::interval_type    tInterval;

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
    void generateRecordings(int);
    void generateAlbums(int);

    void generateArtistComposedTitle();
    void generateTitleRecordedAsRecording();
    void generateAlbumContainsRecording();

private:
    void configure();
    bool exec(const tString& sql);

    void prepareGeneration();


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
    tKey generateRecording(tKey aAlbumKey, tKey aTitleKey);
    tKey generateAlbum();

    void makeComposersRange();
    void assignComposers(tKey aTitle);
    void addComposerToTitle(tKey aArtistKey, tKey aTitleKey);

    void assignTitle(tKey aRecordingKey);
    void assignAlbum(tKey aRecordingKey);
    tString makeRecordingName(tKey aAlbumKey, tKey aTitleKey);

private:
    int m_iArtists;
    int m_iTitles;
    int m_iAlbums;
    int m_iRecordings;

    QSqlDatabase  m_aDb;
    QSqlQuery     m_aQuery;
    QSqlError     m_aLastError;
    tString       m_aFailingSql;
    NameGenerator m_aSomeName;

    tInterKeySet  m_aArtists;
    tInterKeySet  m_aTitles;
    tInterKeySet  m_aRecordings;
    tInterKeySet  m_aAlbums;

    tInterval     m_aComposersRange;

    tKey2Keys     m_aComposer2Titles;
    tKey2Keys     m_aTitle2Composers;

    tKey2Name     m_aTitleNames;
    tKey2Name     m_aAlbumNames;
};

} // namespace data
