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
"create view EdgeTypeCheck as " 
"select "
"  (select ObjectType.name from ObjectType where ObjectType.key = EdgeType.refSourceType)   as SrcT, "
"  (select ObjectType.name from ObjectType where ObjectType.key = EdgeType.refRelationType) as RelT, "
"  ObjectType.name as TrgT, "
"  EdgeType.name "
"from EdgeType "
"  inner join ObjectType   on EdgeType.refTargetType   = ObjectType.key"
  
-- -----------------------------------------------------------------------------
-- Named Objects
create view NamedObjects as 
select Object.key as Obj, VarCharObject.value as Name
from Object
  inner join VarCharObject   on VarCharObject.refObject = Object.key

-- -----------------------------------------------------------------------------
-- Named Objects 1:1 Attributes joined horizontally.
select Object.key as Obj, Name.value as Name, YearOfCrea.value as YoC, Position.value as Pos, Duration.value as Dur 
from Object
  inner join VarCharObject      as Name       on Name.refObject       = Object.key and  Name.refAttribute = 1
  left outer join IntObject     as YearOfCrea on YearOfCrea.refObject = Object.key and  YearOfCrea.refAttribute = 2
  left outer join VarCharObject as Duration   on Duration.refObject   = Object.key and  Duration.refAttribute = 3  
  left outer join VarCharObject as Position   on Position.refObject   = Object.key and  Position.refAttribute = 4  
  -- and so on ...

-- -----------------------------------------------------------------------------
-- Named Objects and Types 1:1 Attributes joined horizontally.
select Object.key as Obj, Vertex.refObjectType as Type, Name.value as Name, YearOfCrea.value as YoC, Position.value as Pos, Duration.value as Dur 
from Object
  inner join Vertex on Vertex.refObject = Object.key and Type = 3
  inner join VarCharObject      as Name       on Name.refObject       = Object.key and  Name.refAttribute = 1
  left outer join IntObject     as YearOfCrea on YearOfCrea.refObject = Object.key and  YearOfCrea.refAttribute = 2
  left outer join VarCharObject as Duration   on Duration.refObject   = Object.key and  Duration.refAttribute = 3  
  left outer join VarCharObject as Position   on Position.refObject   = Object.key and  Position.refAttribute = 4  

  
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

  
-- -----------------------------------------------------------------------------
-- Fields


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
-- Recordings alias Tracks
select Object.key as Obj, Vertex.refObjectType as TKey, ObjectType.Name as Type, 
  Name.value as Name, YearOfCrea.value as YoC, Position.value as Pos, Duration.value as Dur 
from Object
  inner join Vertex on Vertex.refObject = Object.key
  inner join ObjectType on Vertex.refObjectType = ObjectType.key and ObjectType.key = 3
  inner join VarCharObject      as Name       on Name.refObject       = Object.key and  Name.refAttribute = 1
  left outer join IntObject     as YearOfCrea on YearOfCrea.refObject = Object.key and  YearOfCrea.refAttribute = 2
  left outer join VarCharObject as Duration   on Duration.refObject   = Object.key and  Duration.refAttribute = 3  
  left outer join VarCharObject as Position   on Position.refObject   = Object.key and  Position.refAttribute = 4  


-- -----------------------------------------------------------------------------
-- Tracks, incluing album attributes via sub-selects
select Object.key as Obj, Vertex.refObjectType as Tp, ObjectType.Name as Type, 
  Name.value as Name, YearOfCrea.value as YoC, Position.value as Pos, Duration.value as Dur,
  (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) as Alb,
  (select VarCharObject.value from VarCharObject where VarCharObject.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) and VarCharObject.refAttribute = 1) as Album,
  (select IntObject.value from IntObject where IntObject.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) and IntObject.refAttribute = 2) as YoC
from Object
  inner join Vertex on Vertex.refObject = Object.key
  inner join ObjectType on Vertex.refObjectType = ObjectType.key and ObjectType.key = 3
  inner join VarCharObject      as Name       on Name.refObject       = Object.key and  Name.refAttribute = 1
  left outer join IntObject     as YearOfCrea on YearOfCrea.refObject = Object.key and  YearOfCrea.refAttribute = 2
  left outer join VarCharObject as Duration   on Duration.refObject   = Object.key and  Duration.refAttribute = 3  
  left outer join VarCharObject as Position   on Position.refObject   = Object.key and  Position.refAttribute = 4  

-- -----------------------------------------------------------------------------
-- Tracks, incluing album attributes via joins
select Object.key as Obj, Vertex.refObjectType as Tp, ObjectType.Name as Type, 
  Name.value as Name, Position.value as Pos, Duration.value as Dur,
  (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) as Alb,
  Album_Name.value as Album, Album_Year.value as YoC
from Object
  inner join Vertex on Vertex.refObject = Object.key
  inner join ObjectType on Vertex.refObjectType = ObjectType.key and ObjectType.key = 3
  inner join VarCharObject      as Name       on Name.refObject       = Object.key and  Name.refAttribute = 1
  left outer join VarCharObject as Duration   on Duration.refObject   = Object.key and  Duration.refAttribute = 3  
  left outer join VarCharObject as Position   on Position.refObject   = Object.key and  Position.refAttribute = 4  
  left outer join VarCharObject as Album_Name       
    on Album_Name.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) 
	                      and Album_Name.refAttribute = 1
  left outer join IntObject as Album_Year       
    on Album_Year.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) 
	                      and Album_Year.refAttribute = 2

	
-- -----------------------------------------------------------------------------
-- Tracks, including album attributes via joins
select Object.key as Obj, Vertex.refObjectType as Tp, ObjectType.Name as Type
  , Name.value as Name, Position.value as Pos, Duration.value as Dur
  , (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) as Alb
  , Album_Name.value as Album, Album_Year.value as YoC
  , Performer_Name.value as Performer
from Object
  inner join Vertex on Vertex.refObject = Object.key
  inner join ObjectType on Vertex.refObjectType = ObjectType.key and ObjectType.key = 3
  inner join VarCharObject      as Name       on Name.refObject       = Object.key and  Name.refAttribute = 1
  left outer join VarCharObject as Duration   on Duration.refObject   = Object.key and  Duration.refAttribute = 3  
  left outer join VarCharObject as Position   on Position.refObject   = Object.key and  Position.refAttribute = 4  
  left outer join VarCharObject as Album_Name       
    on Album_Name.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) 
	                      and Album_Name.refAttribute = 1
  left outer join IntObject as Album_Year       
    on Album_Year.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) 
	                      and Album_Year.refAttribute = 2
  left outer join VarCharObject as Performer_Name 
    on Performer_Name.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = 12 and refEdgeType = 2) 


-- -----------------------------------------------------------------------------
-- Recordings alias Tracks, incluing album attributes via joins
(select Edge.refTargetVertex,  group_concat(VarCharObject.value) as Performers
  from Edge
  inner join VarCharObject on Edge.refSourceVertex = VarCharObject.refObject
  where refTargetVertex = 12 and refEdgeType = 2)
  
-- -----------------------------------------------------------------------------
-- Tracks, including album attributes via joins
select Object.key as Obj, Vertex.refObjectType as Tp, ObjectType.Name as Type
  , Name.value as Name, Position.value as Pos, Duration.value as Dur
  , (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) as Alb
  , Album_Name.value as Album, Album_Year.value as YoC
  , Performer_Name.value as Performer
  , (select Edge.refTargetVertex,  group_concat(VarCharObject.value) as Performers
     from Edge
     inner join VarCharObject on Edge.refSourceVertex = VarCharObject.refObject
     where refTargetVertex = 12 and refEdgeType = 2)

from Object
  inner join Vertex on Vertex.refObject = Object.key
  inner join ObjectType on Vertex.refObjectType = ObjectType.key and ObjectType.key = 3
  inner join VarCharObject      as Name       on Name.refObject       = Object.key and  Name.refAttribute = 1
  left outer join VarCharObject as Duration   on Duration.refObject   = Object.key and  Duration.refAttribute = 3  
  left outer join VarCharObject as Position   on Position.refObject   = Object.key and  Position.refAttribute = 4  
  left outer join VarCharObject as Album_Name       
    on Album_Name.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) 
	                      and Album_Name.refAttribute = 1
  left outer join IntObject as Album_Year       
    on Album_Year.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) 
	                      and Album_Year.refAttribute = 2
  left outer join VarCharObject as Performer_Name 
    on Performer_Name.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = 12 and refEdgeType = 2) 

	
-- -----------------------------------------------------------------------------
-- Tracks, including album attributes via joins (*)
select Object.key as Obj, Vertex.refObjectType as Tp, ObjectType.Name as Type
  , Name.value as Name, Position.value as Pos, Duration.value as Dur
  , (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) as Alb
  , Album_Name.value as Album, Album_Year.value as YoC
  , Performer_Name.value as Performer
  , (select group_concat(VarCharObject.value)
     from Edge
     inner join VarCharObject on Edge.refSourceVertex = VarCharObject.refObject
     where refTargetVertex = (select Edge.refSourceVertex from Edge 
                              where refTargetVertex = Object.key and refEdgeType = 5) 
           and refEdgeType = 2
	) as AlbumArtists
from Object
  inner join Vertex on Vertex.refObject = Object.key
  inner join ObjectType on Vertex.refObjectType = ObjectType.key and ObjectType.key = 3
  inner join VarCharObject      as Name       on Name.refObject       = Object.key and  Name.refAttribute = 1
  left outer join VarCharObject as Duration   on Duration.refObject   = Object.key and  Duration.refAttribute = 3  
  left outer join VarCharObject as Position   on Position.refObject   = Object.key and  Position.refAttribute = 4  
  left outer join VarCharObject as Album_Name       
    on Album_Name.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) 
	                      and Album_Name.refAttribute = 1
  left outer join IntObject as Album_Year       
    on Album_Year.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = Object.key and refEdgeType = 5) 
	                      and Album_Year.refAttribute = 2
  left outer join VarCharObject as Performer_Name 
    on Performer_Name.refObject = (select Edge.refSourceVertex from Edge where refTargetVertex = 12 and refEdgeType = 2) 


-- -----------------------------------------------------------------------------
-- Experimental views: Checking how we can structure selects based on Edges
--   using Sql-Views to make them more managable.
-- -----------------------------------------------------------------------------
-- View Album
create view Album as
select  -- Edge.refSourceVertex as ArtistKey, 
  Vertex.key as Key, AlbumTitle.value as Name, group_concat(Performer.value) as Artists, YearOfCreation.value as YoC
from Vertex
  inner join Edge on     Edge.refTargetVertex = Vertex.key  
                     and Edge.refEdgeType = 2 -- 2: Artist (performs on) Album
  left outer join VarCharObject as AlbumTitle on AlbumTitle.refObject = vertex.key and AlbumTitle.refAttribute = 1
  left outer join VarCharObject as Performer on Performer.refObject = Edge.refSourceVertex
  left outer join IntObject as YearOfCreation on YearOfCreation.refObject = Vertex.key
group by Vertex.key  

-- -----------------------------------------------------------------------------
-- View Track
-- create view Track as
select  -- Edge.refSourceVertex as ArtistKey, 
    Vertex.key as TrkKey, TrackName.value
  , MotherAlbum.refSourceVertex as MAlbKey, Album.Key as AlbKey
  , Album.Name as AlbumName, Album.Artists as AlbumArtists
from Vertex
  inner join VarCharObject as TrackName on     TrackName.refObject = Vertex.key 
                                           and TrackName.refAttribute = 1
                                           and Vertex.refObjectType = 3
  left outer join Edge as MotherAlbum on     MotherAlbum.refTargetVertex = Vertex.key  
                                         and MotherAlbum.refEdgeType = 5 -- 5: Album contains Recording
  left outer join Album on MotherAlbum.refSourceVertex = Album.Key 

