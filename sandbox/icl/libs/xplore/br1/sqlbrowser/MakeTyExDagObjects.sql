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
--   add John Lennon T(1) v(15)
--     add Obj(15), Vtx(15,1,15), VarCharObject(15, 1, J.L)
--                                    IntObject(15, 2,1940)
--   add Paul McCartney
--     add Obj(16), Vtx(16,1,16), VarCharObject(16, 1, P.McC)
--                                    IntObject(16, 2,  1942)
--   add Geroge Harrison
--     add Obj(17), Vtx(17,1,17), VarCharObject(17, 1, G.H.)
--                                    IntObject(17, 2, 1943)
--   add Ringo Starr
--     add Obj(18), Vtx(18,1,18), VarCharObject(18, 1, R.S.)
--                                    IntObject(18, 2, 1940)

-- add titles
--   add Come Together
--     add Obj(19), Vtx(19,2,19), VarCharObject(19,1,C.T.), 
--                                YoC:IntObject(19,2,1969)
--   add Something
--     add Obj(20), Vtx(20,2,20), VarCharObject(20,1,Sth.), 
--                                YoC:IntObject(20,2,1968)

-- add album
--   add Obj(21), Vtx(21,10,21),  VarCharObject(21,1,Abbey Rd.),
--                                IntObject(21,2,1969)

-- add recordings
--   add Obj(22), Vtx(22,3,22),  VarCharObject(22,1,Aby.Rd: Come Together),
--                               VarCharObject(22,4,#1),
--                               VarCharObject(22,3,"04:20"),

-- add recordings
--   add Obj(23), Vtx(23,3,23),  VarCharObject(23,1,Aby.Rd: Something),
--                               VarCharObject(23,4,#2),
--                               VarCharObject(23,3,"03:03"),

-- === EDGES
-- add artist composed title relation
--   add Obj(24)
--     add Edge(24): composed(ET:1(VT:1,RT:6,VT:2)), J.L.(15), C.T.(19), obj(24)
--       = Edge(24,1,15,19,24)
--   add Obj(25)
--     add Edge(25): composed(ET:1(VT:1,RT:6,VT:2)), P.McC.(16), C.T.(19), obj(25)
--       = Edge(25,1,16,19,25)

-- add album contains recording
--   add Obj(26)
--     add Edge(26): contains(ET:5(VT:10,RT:11,VT:3)), AbyRd(21), AbR:C.T.(22), obj(26)
--       = Edge(26,5,21,22,26)
--   add Obj(27)
--     add Edge(27): contains(ET:5(VT:10,RT:11,VT:3)), AbyRd(21), AbR:S.th.(23), obj(27)
--       = Edge(27,5,21,23,27)

-- add title recorded as recording
--   add Obj(28)
--     add Edge(28): recorded_as(ET:3(VT:2,RT:8,VT:3)), AbR:C.T.(22), ComeTgthr(19), obj(28)
--       = Edge(28,3,22,19,28)
--   add Obj(29)
--     add Edge(29): recorded_as(ET:3(VT:2,RT:8,VT:3)), AbR:C.T.(22), Someth.(20), obj(29)
--       = Edge(29,3,22,20,29)

-- add artist performed on album
--   add Obj(30)
--     add Edge(30): performed_on(ET:2(VT:1,RT:7,VT:10)), J.L.(15), AbyRd(21), obj(30)
--       = Edge(30,2,15,21,30)
--   add Obj(31)
--     add Edge(31): performed_on(ET:2(VT:1,RT:7,VT:10)), P.McC(16), AbyRd(21), obj(31)
--       = Edge(31,2,16,21,31)


