drop table StructType;
drop table ObjectType;
drop table RelationType;
drop table EdgeType;
drop table Vertex;
drop table Edge;
drop table Object;
drop table Relation;

create table StructType (id integer primary key, Name varchar);
create table ObjectType (id integer primary key, refStructType integer, Name varchar);
create table RelationType (id integer primary key, Name varchar);
create table EdgeType (id integer primary key, refSourceObjectType integer, refRelationType integer, refTargetObjectType integer, Name varchar);
create table Vertex (id integer primary key, refObjectType integer);
create table Edge (id integer primary key, refSourceVertex integer, refEdgeType integer, refTargetVertex integer);
create table Object (id integer primary key, refVertex integer);
create table Relation (id integer primary key, refEdge integer);



-- -----------------------------------------------------------------------------
insert into StructType values (0, 'Nil');
insert into StructType values (1, 'atom');
insert into StructType values (2, 'composite');

insert into ObjectType values (0, 0, 'Nil');
insert into ObjectType values (1, 1, 'artist');
insert into ObjectType values (2, 1, 'title');
insert into ObjectType values (3, 1, 'recording');
insert into ObjectType values (4, 2, 'artists');
insert into ObjectType values (5, 2, 'genre');

insert into RelationType values (0, 'Nil');
insert into RelationType values (1, 'composed');
insert into RelationType values (2, 'performed');
insert into RelationType values (3, 'recorded as');
insert into RelationType values (4, 'located');

insert into EdgeType values (1, 1, 1, 2, 'artist composed title'   );
insert into EdgeType values (2, 1, 2, 3, 'artist performed record' );
insert into EdgeType values (3, 2, 3, 3, 'title recorded as record');
insert into EdgeType values (4, 3, 4, 4, 'record located at url'   );

insert into Vertex values (0, 0);
insert into Vertex values (1, 1);
insert into Vertex values (2, 1);
insert into Vertex values (3, 1);
insert into Vertex values (4, 2);
insert into Vertex values (5, 2);

insert into Edge values (0, 0, 0, 0);
insert into Edge values (1, 1, 1, 4);

insert into Object values (0, 0);
insert into Object values (1, 1);
insert into Object values (2, 2);
insert into Object values (3, 3);
insert into Object values (4, 4);
insert into Object values (5, 5);

insert into Relation values (0, 0);
insert into Relation values (1, 1);

-- -------------------------------------
-- Dag Related Architecture Linking All 
-- D   R       A      C U   L       A

create view EdgeSignature as 
select
  (select StructType.Name from ObjectType as ObjT2
     inner join ObjectType on ObjT2.id = EdgeType.refSourceObjectType
     inner join StructType on StructType.id = ObjT2.refStructType) as SrcS,
  (select ObjectType.Name from ObjectType where ObjectType.id = EdgeType.refSourceObjectType) as SrcT,
  RelationType.Name as RelT,
  StructType.Name as TrgS,
  ObjectType.Name as TrgT,
  EdgeType.Name
from EdgeType
  inner join ObjectType   on EdgeType.refTargetObjectType = ObjectType.id
  inner join RelationType on EdgeType.refRelationType     = RelationType.id
  inner join StructType   on ObjectType.refStructType     = StructType.id
  

insert into Vertex values (0, 0);
insert into Vertex values (1, 1);
insert into Vertex values (2, 1);
insert into Vertex values (3, 1);
insert into Vertex values (4, 2);
insert into Vertex values (5, 2);

-- ------------------------------
1(artist) 1(Name)  1(Text)
1(artist) 2(Birth) 7(Date)

