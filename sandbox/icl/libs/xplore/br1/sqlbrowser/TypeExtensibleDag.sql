drop table StructType;
drop table ObjectType;
drop table RelationType;
drop table EdgeType;
drop table Vertex;
drop table Edge;
drop table Object;

create table TypeTraits (key integer primary key, name varchar);
create table ObjectType (key integer primary key, traits integer, name varchar);
create table EdgeType (key integer primary key, refSourceType integer, refRelationType integer, refTargetType integer, name varchar);
create table Vertex (key integer primary key, refObjectType integer, refObject integer);
create table Edge (key integer primary key, refEdgeType integer, refSourceVertex integer, refTargetVertex integer, refObject integer);

-- Object is hardly a new entity of its own. It builds the disjoint union of
-- Vertex and Edge Key. 
-- {Object.keys} == {V.keys} + {E,keys}  +:set union
--            {} == {V.keys} & {E,keys}  &:set intersection
create table Object (key integer primary key);

create table Attribute (key integer primary key, refObjectType integer, name varchar);
create table IntObject (refObject integer, refAttribute integer, value integer, primary key (refObject, refAttribute));
create table VarCharObject (refObject integer, refAttribute integer, value varchar, primary key (refObject, refAttribute));


-- The creation sequence and systematics for generating example entities:

-- To add an album with titles, recordings and locations
-- we proceed from elemetal, independent, not refering entities
-- to those that contain references to other entities

-- Example Album: Abbey Road.

-- add genre ...
--   add Beat
--     add Obj, Vtx, Name

-- add artists
--   add John Lennon
--     add Obj, Vtx, Name, [...]
--   add Paul McCartney
--   add Geroge Harrison
--   add Ringo Starr

-- add titles
--   add Come Together
--     add Obj, Vtx, Name, YoC
--   add Something
--   ...

-- add artist composed title relation
--   
