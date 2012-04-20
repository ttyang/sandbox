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
insert into ObjectType values (10, 0, 'c:album');
insert into ObjectType values (11, 2, 'r:contains');

insert into EdgeType values (1, 1, 6, 2, 'artist composed title'   );
insert into EdgeType values (2, 1, 7, 3, 'artist performed record' );
insert into EdgeType values (3, 2, 8, 3, 'title recorded as record');
insert into EdgeType values (4, 3, 9, 4, 'record located at url'   );
insert into EdgeType values (5, 10, 11, 3, 'album contains record' );

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
insert into VarCharObject values (6, 1, "composed in 1995");

insert into Object values (7);
insert into VarCharObject values (7, 1, "composed in 1930");

insert into Object values (8);
insert into VarCharObject values (8, 1, "N&tC: Twighlight Song");

insert into Object values (9);
insert into VarCharObject values (9, 1, "N&tC: Body & Soul");

insert into Object values (10);
insert into VarCharObject values (10, 1, "Night & the City");


insert into Vertex values (0, 0, 0);
insert into Vertex values (1, 1, 1);  
insert into Vertex values (2, 1, 2);
insert into Vertex values (3, 1, 3);
insert into Vertex values (4, 2, 4);
insert into Vertex values (5, 2, 5);
insert into Vertex values (8, 3, 8);
insert into Vertex values (9, 3, 9);
insert into Vertex values (10, 3, 10);

insert into Edge values (1, 1, 1, 4, 6);
-- 2:key 1:composed 3:J.Green 5:Body&Soul 7:comp1930
insert into Edge values (2, 1, 3, 5, 7);

-- 3:key 2:performed 2:K.Barron 10:N&tC 11:rec1996
insert into Edge values (3, 2, 2, 10, 11);
-- 4:key 7:performed 1:C.Haden 10:N&tC
insert into Edge values (4, 2, 1, 10, 11);

insert into Object values (11);
insert into VarCharObject values (11, 1, "recoreded 1996");


-- -------------------------------------
-- Dag Related Architecture Linking All 
-- D   R       A      C U   L       A
-- -------------------------------------------------------
-- Dag Related Architecture Using Links All over the place 
-- D   R       A      C     U     L     A

-- -----------------------------------------------------------------------------
-- Check for EdgeTypes
create view EdgeTypeCheck as 
select
  (select ObjectType.name from ObjectType where ObjectType.key = EdgeType.refSourceType)   as SrcT,
  (select ObjectType.name from ObjectType where ObjectType.key = EdgeType.refRelationType) as RelT,
  ObjectType.name as TrgT,
  EdgeType.name
from EdgeType
  inner join ObjectType   on EdgeType.refTargetType   = ObjectType.key
  
-- -----------------------------------------------------------------------------
-- Named Objects
create view NamedObjects as 
select Object.key as Obj, VarCharObject.value as Name
from Object
  inner join VarCharObject   on VarCharObject.refObject = Object.key
  

  
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
select Edge.key as Edg, Object.key as Obj, EdgeType.Name as Type, 
  VarCharObject.value as Name, IntObject.value as Year
from Object
  inner join Edge           on Edge.refObject             = Object.key 
  inner join EdgeType       on Edge.refEdgeType           = EdgeType.key
  inner join VarCharObject  on VarCharObject.refObject    = Object.key
  left outer join IntObject on IntObject.refObject        = Object.key  
  
-- -----------------------------------------------------------------------------
-- EdgesMinimal
create view EdgesMinimal as
select SrcName.Value as Source, EdgeType.Name as Type, TrgName.Value as Target
from Object
  inner join Edge           on Edge.refObject             = Object.key 
  inner join EdgeType       on Edge.refEdgeType           = EdgeType.key
  inner join VarCharObject  on VarCharObject.refObject    = Object.key
  inner join VarCharObject as SrcName on Edge.refSourceVertex = SrcName.refObject
  inner join VarCharObject as TrgName on Edge.refTargetVertex = TrgName.refObject
  
-- -----------------------------------------------------------------------------
-- EdgesComplete
select Edge.key as Edg, Object.key as Obj, EdgeType.Name as Type, 
  VarCharObject.value as Name, IntObject.value as Year,
  Edge.refSourceVertex as Src, SrcName.Value,
  Edge.refTargetVertex as Trg, TrgName.Value
from Object
  inner join Edge           on Edge.refObject             = Object.key 
  inner join EdgeType       on Edge.refEdgeType           = EdgeType.key
  inner join VarCharObject  on VarCharObject.refObject    = Object.key
  inner join VarCharObject as SrcName on Edge.refSourceVertex = SrcName.refObject
  inner join VarCharObject as TrgName on Edge.refTargetVertex = TrgName.refObject
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



  