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
create table EdgeType (id integer primary key, refSourceObjectType integer, refTargetObjectType integer, refRelationType integer, Name varchar);
create table Vertex (id integer primary key, refObjectType integer);
create table Edge (id integer primary key, refEdgeType integer, refSourceVertex integer, refTargetVertex integer);
create table Object (id integer primary key, refVertex integer);
create table Relation (id integer primary key, refEdge integer);



-- Dag Related Architecture Linking All 
-- D   R       A      C U   L       A
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

insert into EdgeType values (1, 1, 2, 1, 'artist composed title'   );
insert into EdgeType values (2, 1, 3, 2, 'artist performed record' );
insert into EdgeType values (3, 2, 3, 3, 'title recorded as record');
insert into EdgeType values (4, 3, 4, 4, 'record located at url'   );

insert into Vertex values (0, 0);
insert into Vertex values (1, 1);   -- artists 
insert into Vertex values (2, 1);
insert into Vertex values (3, 1);
insert into Vertex values (4, 2);   -- titles
insert into Vertex values (5, 2);

insert into Edge values (0, 0, 0, 0);
insert into Edge values (1, 1, 1, 4);   -- artist:1 composed(1) title:4 

insert into Object values (0, 0);
insert into Object values (1, 1);
insert into Object values (2, 2);
insert into Object values (3, 3);
insert into Object values (4, 4);
insert into Object values (5, 5);

insert into Relation values (0, 0);
insert into Relation values (1, 1);
