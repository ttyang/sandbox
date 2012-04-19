drop table StructType;
drop table ObjectType;
drop table RelationType;
drop table EdgeType;
drop table Vertex;
drop table Edge;
drop table Object;
drop table Relation;

create table TypeTraits (key integer primary key, name varchar);
create table ObjectType (key integer primary key, traits integer, name varchar);
create table EdgeType (key integer primary key, refSourceType integer, refRelationType integer, refTargetType integer, name varchar);
create table Vertex (key integer primary key, refObjectType integer, refObject integer);
create table Edge (key integer primary key, refEdgeType integer, refSourceVertex integer, refTargetVertex integer, refObject integer);
create table Object (key integer primary key);
create table Attribute (key integer primary key, name varchar);
create table IntObject (refObject integer, refAttribute integer, value integer, primary key (refObject, refAttribute));
create table VarCharObject (refObject integer, refAttribute integer, value varchar, primary key (refObject, refAttribute));




-- -----------------------------------------------------------------------------
insert into TypeTraits values (0, 'atom obj');
insert into TypeTraits values (1, 'comp obj');
insert into TypeTraits values (2, 'atom rel');

insert into ObjectType values (0, 0, 'Nil');
insert into ObjectType values (1, 0, 'a:artist');
insert into ObjectType values (2, 0, 'a:title');
insert into ObjectType values (3, 0, 'a:recording');
insert into ObjectType values (4, 0, 'c:artists');
insert into ObjectType values (5, 1, 'c:genre');
insert into ObjectType values (6, 2, 'r:composed');
insert into ObjectType values (7, 2, 'r:performed');
insert into ObjectType values (8, 2, 'r:recorded as');
insert into ObjectType values (9, 2, 'r:located at');

insert into EdgeType values (1, 1, 6, 2, 'artist composed title'   );
insert into EdgeType values (2, 1, 7, 3, 'artist performed record' );
insert into EdgeType values (3, 2, 8, 3, 'title recorded as record');
insert into EdgeType values (4, 3, 9, 4, 'record located at url'   );

insert into Object values (0);

insert into Object values (1);
insert into Attribute values (1, "Name");
insert into VarCharObject values (1, 1, "Charlie Haden");

insert into Object values (2);
insert into VarCharObject values (2, 1, "Kenny Barron");

insert into Object values (3);
insert into VarCharObject values (3, 1, "Jonny Green");

insert into Object values (4);
insert into VarCharObject values (4, 1, "Twighlight Song");

insert into Object values (5);
insert into VarCharObject values (5, 1, "Body & Soul");

insert into Object values (6);
insert into VarCharObject values (6, 1, "composed in 2001");

insert into Object values (7);
insert into VarCharObject values (7, 1, "composed in 1930");

insert into Vertex values (0, 0, 0);
insert into Vertex values (1, 1, 1);  
insert into Vertex values (2, 1, 2);
insert into Vertex values (3, 1, 3);
insert into Vertex values (4, 2, 4);
insert into Vertex values (5, 2, 5);

insert into Edge values (1, 1, 1, 4, 6);
insert into Edge values (2, 2, 2, 4, 0);


-- -------------------------------------
-- Dag Related Architecture Linking All 
-- D   R       A      C U   L       A
-- -------------------------------------------------------
-- Dag Related Architecture Using Links All over the place 
-- D   R       A      C     U     L     A

create view EdgeTypeCheck as 
select
  (select ObjectType.name from ObjectType where ObjectType.key = EdgeType.refSourceType)   as SrcT,
  (select ObjectType.name from ObjectType where ObjectType.key = EdgeType.refRelationType) as RelT,
  ObjectType.name as TrgT,
  EdgeType.name
from EdgeType
  inner join ObjectType   on EdgeType.refTargetType   = ObjectType.key
  

  
-- -----------------------------------------------------------------------------
-- Vertexes
select Vertex.key as Vtx, Object.key as Obj, ObjectType.Name as Type , Attribute.Name as Attr, 
  VarCharObject.Value as Name, IntObject.value as Year
from Object
  inner join Vertex         on Vertex.refObject           = Object.key 
  inner join ObjectType     on Vertex.refObjectType       = ObjectType.key
  inner join Attribute      on VarCharObject.refAttribute = Attribute.key 
  inner join VarCharObject  on VarCharObject.refObject    = Object.key
  left outer join IntObject on IntObject.refObject        = Object.key  

-- -----------------------------------------------------------------------------
-- Edge-Objects and associated values
select Edge.key as Edg, Object.key as Obj, EdgeType.Name as Type , Attribute.Name as Attr, 
  VarCharObject.Value as Name, IntObject.value as Year
from Object
  inner join Edge           on Edge.refObject             = Object.key 
  inner join EdgeType       on Edge.refEdgeType           = EdgeType.key
  inner join Attribute      on VarCharObject.refAttribute = Attribute.key 
  inner join VarCharObject  on VarCharObject.refObject    = Object.key
  left outer join IntObject on IntObject.refObject        = Object.key  

-- -----------------------------------------------------------------------------
-- Edges
select Edge.key as Edg, Object.key as Obj, EdgeType.Name as Type 
  VarCharObject.Value as Name, IntObject.value as Year
from Object
  inner join Edge           on Edge.refObject             = Object.key 
  inner join EdgeType       on Edge.refEdgeType           = EdgeType.key
  inner join VarCharObject  on VarCharObject.refObject    = Object.key
  left outer join IntObject on IntObject.refObject        = Object.key  
  

-- -----------------------------------------------------------------------------
-- Artists
select Vertex.key as Vtx, Object.key as Obj, VarCharObject.value as Name, IntObject.value as YoBirth
from Vertex
  inner join Object        on Object.key = Vertex.refObject
  inner join VarCharObject on Object.key = VarCharObject.refObject and VarCharObject.refAttribute = 1  
  inner join IntObject     on Object.key = IntObject.refObject     and IntObject.refAttribute = 2 
where
  Vertex.refObjectType = 1

  
-- -----------------------------------------------------------------------------
-- Edges 2.
-- 
select refSourceVertex as Src, VarCharObject.value as Source,
  (select EdgeType.name from EdgeType where EdgeType.key = Edge.refEdgeType) as Relation,
  (select IntObject.value
    from Edge
    inner join Object on Object.key = Edge.refObject
    inner join IntObject on Object.key = IntObject.refObject
  ) as Year,
  (select VarCharObject.value
    from Edge
    inner join Vertex on Vertex.key = Edge.refTargetVertex
    inner join Object on Object.key = Vertex.refObject
    inner join VarCharObject on Object.key = VarCharObject.refObject
  ) as Target
from Edge
  inner join Vertex on Vertex.key = Edge.refSourceVertex
  inner join Object on Object.key = Vertex.refObject
  inner join VarCharObject on Object.key = VarCharObject.refObject



  