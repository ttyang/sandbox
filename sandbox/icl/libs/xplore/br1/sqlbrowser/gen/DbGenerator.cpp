/****************************************************************************
**
**
****************************************************************************/

#include <QtGui>
#include <QString>
#include <QMessageBox>
#include "gen/NumberGenerator.h"
#include "gen/DbGenerator.h"

using namespace gen;
using namespace boost::icl;


void DbGenerator::configure()
{
    m_iArtists = 1000;
    m_iTitles  = 10000;
}

void DbGenerator::clear()
{
    m_aFailingSql = tString();
    m_aArtists.clear();
    m_aTitles.clear();
}

bool DbGenerator::generate()
{

    if(!m_aDb.open())
    {
        m_aFailingSql = tString("m_aDb.open()");
        return false;
    }

    //------------------------------------------
    clearDb();
    generateTables();
    generateTypeData();

    generateObjects();
    generateRelationships();
    //------------------------------------------

    if(m_aFailingSql.isEmpty())
        return true;
    else
        return false;
}


bool DbGenerator::exec(const tString& sql)
{
    if(!m_aQuery.exec(sql))
    {
        m_aFailingSql = sql;
        m_aLastError  = m_aQuery.lastError();
        return false;
    }
    return true;
}


void DbGenerator::generateTypeData()
{
    generateTypeTraits();
    generateObjectTypes();
    generateEdgeTypes();
    generateAttributes();

    generateTypeViews();
}



void DbGenerator::clearDb()
{

    exec("drop view Album"        );
    exec("drop view EdgesMinimal" );
    exec("drop view NamedObjects" );
    exec("drop view EdgeTypeCheck");

    exec("drop table TypeTraits"   );
    exec("drop table ObjectType"   );
    exec("drop table EdgeType"     );
    exec("drop table Vertex"       );
    exec("drop table Edge"         );
    exec("drop table Object"       );
    exec("drop table Attribute"    );
    exec("drop table VarCharObject");
    exec("drop table IntObject"    );
}

void DbGenerator::generateTables()
{
    exec("create table TypeTraits (key integer primary key, name varchar)");
    exec("create table ObjectType (key integer primary key, traits integer, name varchar)");
    exec("create table EdgeType (key integer primary key, refSourceType integer, refRelationType integer, refTargetType integer, name varchar)");
    exec("create table Vertex (key integer primary key, refObjectType integer)");
    exec("create table Edge (key integer primary key, refEdgeType integer, refSourceVertex integer, refTargetVertex integer)");
    exec("create table Object (key integer primary key)");
    exec("create table Attribute (key integer primary key, refObjectType integer, name varchar)");
    exec("create table VarCharObject (refObject integer, refAttribute integer, value varchar, primary key (refObject, refAttribute))");
    exec("create table IntObject (refObject integer, refAttribute integer, value integer, primary key (refObject, refAttribute))");
}

void DbGenerator::generateTypeTraits()
{
    exec("insert into TypeTraits values (0, 'atom obj')");
    exec("insert into TypeTraits values (1, 'comp obj')");
    exec("insert into TypeTraits values (2, 'atom rel')");
}

void DbGenerator::generateObjectTypes()
{
    exec("insert into ObjectType values (1, 0, 'a:text')");
    exec("insert into ObjectType values (2, 0, 'a:integer')");
    exec("insert into ObjectType values (3, 0, 'a:real')");

    exec("insert into ObjectType values (21, 0, 'a:artist')");
    exec("insert into ObjectType values (22, 0, 'a:title')");
    exec("insert into ObjectType values (23, 0, 'a:recording')");
    exec("insert into ObjectType values (24, 0, 'c:artists')");
    exec("insert into ObjectType values (25, 1, 'c:genre')");
    exec("insert into ObjectType values (26, 2, 'r:composed')");
    exec("insert into ObjectType values (27, 2, 'r:performed')");
    exec("insert into ObjectType values (28, 2, 'r:recorded as')");
    exec("insert into ObjectType values (29, 2, 'r:located at')");
    exec("insert into ObjectType values (30, 0, 'c:album')");
    exec("insert into ObjectType values (31, 2, 'r:contains')");
}

void DbGenerator::generateEdgeTypes()
{
    exec("insert into EdgeType values (1, 21, 26, 22, 'artist composed title'   )");
    exec("insert into EdgeType values (2, 21, 27, 23, 'artist performed record' )");
    exec("insert into EdgeType values (3, 22, 28, 23, 'title recorded as record')");
    exec("insert into EdgeType values (4, 23, 29, 24, 'record located at url'   )");
    exec("insert into EdgeType values (5, 30, 31, 23, 'album contains record' )");
}

void DbGenerator::generateAttributes()
{
    exec("insert into Attribute values (1,  1, 'Name')"    );
    exec("insert into Attribute values (2,  1, 'Duration')");
    exec("insert into Attribute values (31, 2, 'Year')"    );
    exec("insert into Attribute values (32, 2, 'Pos')"     );

}

void DbGenerator::generateTypeViews()
{
    exec
    (
        "create view EdgeTypeCheck as "
        "select "
        "  (select ObjectType.name from ObjectType where ObjectType.key = EdgeType.refSourceType)   as SrcT, "
        "  (select ObjectType.name from ObjectType where ObjectType.key = EdgeType.refRelationType) as RelT, "
        "  ObjectType.name as TrgT, "
        "  EdgeType.name "
        "from EdgeType "
        "  inner join ObjectType   on EdgeType.refTargetType   = ObjectType.key"
    );
}

void DbGenerator::generateObjects()
{
    generateArtists(m_iArtists);
    generateTitles(m_iTitles);
}

void DbGenerator::generateRelationships()
{
    generateArtistComposedTitle();
}


dag::db::tKey DbGenerator::insertObject()
{
    exec("insert into Object values (NULL)");
    return m_aQuery.lastInsertId().toInt();
}

void DbGenerator::insertVertex(tKey aKey, tObjectType eType)
{
    exec(tString("insert into Vertex values (%1, %2)").arg(aKey).arg(eType));
}

void DbGenerator::insertEdge(tKey aEdgeKey, tKey aEdgeTypeKey, tKey aSrcKey, tKey aTrgKey)
{
    exec(tString("insert into Edge values (%1, %2, %3, %4)")
         .arg(aEdgeKey).arg(aEdgeTypeKey).arg(aSrcKey).arg(aTrgKey));
}

void DbGenerator::insertVarCharObject(tKey aKey, tAttribute eAttr, const tString& value)
{
    exec(tString("insert into VarCharObject values (%1, %2, '%3')").arg(aKey).arg(eAttr).arg(value));
}

void DbGenerator::insertIntObject(tKey aKey, tAttribute eAttr, int value)
{
    exec(tString("insert into IntObject values (%1, %2, %3)").arg(aKey).arg(eAttr).arg(value));
}

dag::db::tKey DbGenerator::generateArtist()
{
    tKey aKey = insertObject();
    insertVertex(aKey, a_artist);
    insertVarCharObject(aKey, A_Name, m_aSomeName("A_"));
    insertIntObject(aKey, A_Year, gen::IntGenerator(1940, 1990)());
    return aKey;
}


dag::db::tKey DbGenerator::generateTitle()
{
    tKey aKey = insertObject();
    insertVertex(aKey, a_title);
    insertVarCharObject(aKey, A_Name, m_aSomeName("T_"));
    insertIntObject(aKey, A_Year, gen::IntGenerator(1960, 2012)());
    return aKey;
}

void DbGenerator::generateArtists(int count)
{
    for(int idx=0; idx<count; idx++)
        m_aArtists.add(generateArtist());
}

void DbGenerator::generateTitles(int count)
{
    for(int idx=0; idx<count; idx++)
        m_aTitles.add(generateTitle());
}


void DbGenerator::generateArtistComposedTitle()
{
    tKey aKey = insertObject();
    makeComposersRange();

    //Every title needs at least one composer.
    for(  tKeySet::element_iterator it = elements_begin(m_aTitles)
        ; it != elements_end(m_aTitles); ++it)
    {
        assignComposers(*it);
    }

}

void DbGenerator::makeComposersRange()
{
    //Not all artists are composers
    tInterval artistsRange = hull(m_aArtists);
    tKey fst = first(artistsRange);
    tKey lst = fst + size(artistsRange)/2;
    m_aComposersRange = tInterval::closed(fst, lst);
}

void DbGenerator::assignComposers(tKey aTitle)
{
    gen::IntGenerator someArtist(m_aComposersRange);
    tKey aArtist1 = someArtist();

    tKey aEdgeKey1 = insertObject();
    insertEdge(aEdgeKey1, R_artist_composed_title, aArtist1, aTitle);

    if(IntGenerator(1,3)() == 3)
    {
        tKey aArtist2 = someArtist();
        if(aArtist2 != aArtist1)
        {
            tKey aEdgeKey2 = insertObject();
            insertEdge(aEdgeKey2, R_artist_composed_title, aArtist2, aTitle);
            if(IntGenerator(1,3)() == 3)
            {
                tKey aEdgeKey3 = insertObject();
                tKey aArtist3 = someArtist();
                if(aArtist3 != aArtist1 && aArtist3 != aArtist2)
                    insertEdge(aEdgeKey3, R_artist_composed_title, aArtist3, aTitle);
            }

        }
    }
}


