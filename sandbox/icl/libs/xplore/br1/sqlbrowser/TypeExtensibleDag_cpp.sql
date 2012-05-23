drop table TypeTraits;
drop table ObjectType;
drop table EdgeType;
drop table Vertex;
drop table Edge;
drop table Object;
drop table Attribute;
drop table VarCharObject;
drop table IntObject;

exec("create table TypeTraits (key integer primary key, name varchar)");
exec("create table ObjectType (key integer primary key, traits integer, name varchar)");
exec("create table EdgeType (key integer primary key, refSourceType integer, refRelationType integer, refTargetType integer, name varchar)");
exec("create table Vertex (key integer primary key, refObjectType integer, refObject integer)");
exec("create table Edge (key integer primary key, refEdgeType integer, refSourceVertex integer, refTargetVertex integer, refObject integer)");
exec("create table Object (key integer primary key)");
exec("create table Attribute (key integer primary key, refObjectType integer, name varchar)");
exec("create table VarCharObject (refObject integer, refAttribute integer, value varchar, primary key (refObject, refAttribute))");
exec("create table IntObject (refObject integer, refAttribute integer, value integer, primary key (refObject, refAttribute))");

-- -----------------------------------------------------------------------------
exec("insert into TypeTraits values (0, 'atom obj')");
exec("insert into TypeTraits values (1, 'comp obj')");
exec("insert into TypeTraits values (2, 'atom rel')");

-- -----------------------------------------------------------------------------
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

exec("insert into EdgeType values (1, 21, 26, 22, 'artist composed title'   )");
exec("insert into EdgeType values (2, 21, 27, 23, 'artist performed record' )");
exec("insert into EdgeType values (3, 22, 28, 23, 'title recorded as record')");
exec("insert into EdgeType values (4, 23, 29, 24, 'record located at url'   )");
exec("insert into EdgeType values (5, 30, 31, 23, 'album contains record' )");

exec("insert into Attribute values (1, 1, 'Name')"    );
exec("insert into Attribute values (2, 1, 'Duration')");
exec("insert into Attribute values (31, 2, 'Year')"   );
exec("insert into Attribute values (32, 2, 'Position')");


-- -----------------------------------------------------------------------------
-- 1.000 Artist, 10.000 Titles with Names and YoCs
-- ca. 01:50 h time of generation
-- Final size: 1.215 kB. 1,215 MB
-- 111 Bytes per object.