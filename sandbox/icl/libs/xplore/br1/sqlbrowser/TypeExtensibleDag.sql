drop table TypeTraits;
drop table ObjectType;
drop table EdgeType;
drop table Vertex;
drop table Edge;
drop table Object;
drop table Attribute;
drop table VarCharObject;
drop table IntObject;

create table TypeTraits (key integer primary key, name varchar);
create table ObjectType (key integer primary key, traits integer, name varchar);
create table EdgeType (key integer primary key, refSourceType integer, refRelationType integer, refTargetType integer, name varchar);
create table Vertex (key integer primary key, refObjectType integer, refObject integer);
create table Edge (key integer primary key, refEdgeType integer, refSourceVertex integer, refTargetVertex integer, refObject integer);
create table Object (key integer primary key);
create table Attribute (key integer primary key, refObjectType integer, name varchar);

create table VarCharObject (refObject integer, refAttribute integer, value varchar, primary key (refObject, refAttribute));
create table IntObject (refObject integer, refAttribute integer, value integer, primary key (refObject, refAttribute));





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
select Vertex.key as TrackId
, TrackName.value as Name
, MotherAlbum.refSourceVertex as AlbId, AlbumName.value as Album, AlbumYear.value as AlbYr
, MotherTitle.refSourceVertex as TitId, TitleName.value as Title, TitleYear.value as TitYr
, Duration.value as Dur 
, Genre.value as Genre 
from Vertex
  inner join VarCharObject as TrackName on     TrackName.refObject = Vertex.key 
                                           and TrackName.refAttribute = 1
                                           and Vertex.refObjectType = 23 -- 23: Recording (aka. Track)
  left outer join Edge as MotherAlbum on     MotherAlbum.refTargetVertex = Vertex.key  
                                         and MotherAlbum.refEdgeType = 5 -- 5: Album contains Recording
  left outer join VarCharObject as AlbumName on AlbumName.refObject = MotherAlbum.refSourceVertex
  left outer join IntObject     as AlbumYear on AlbumYear.refObject = MotherAlbum.refSourceVertex
  left outer join Edge as MotherTitle on     MotherTitle.refTargetVertex = Vertex.key  
                                         and MotherTitle.refEdgeType = 3 -- 3: Title recoreded as Recording
  left outer join VarCharObject as TitleName on TitleName.refObject = MotherTitle.refSourceVertex
  left outer join IntObject     as TitleYear on TitleYear.refObject = MotherTitle.refSourceVertex
  left outer join VarCharObject as Duration  on Duration.refObject = Vertex.key and Duration.refAttribute = 2
  left outer join VarCharObject as Genre     on Genre.refObject = Vertex.key and Genre.refAttribute = 3
  
-- -----------------------------------------------------------------------------
  left outer join Edge as ArtComposedTit on     ArtComposedTit.refTargetVertex = MotherTitle.refTargetVertex  
                                            and ArtComposedTit.refEdgeType = 1 -- 1: Artist compsed Title
  
  
-- -----------------------------------------------------------------------------
-- Select from Edges
select refTargetVertex, group_concat(ArtistName.value) as Artist, ArtistYear.value as YoB, TitleName.value as Title
from Edge
  inner join VarCharObject as ArtistName on ArtistName.refObject = Edge.refSourceVertex
  left outer join IntObject as ArtistYear on ArtistYear.refObject = Edge.refSourceVertex
  left outer join VarCharObject as TitleName on TitleName.refObject = Edge.refTargetVertex
group by refTargetVertex
order by Title


-- -----------------------------------------------------------------------------
-- -----------------------------------------------------------------------------
-- View Track
-- create view Track as
select Vertex.key as TrackId
, TrackName.value as Name
, MotherAlbum.refSourceVertex as AlbId, AlbumName.value as Album, AlbumYear.value as AlbYr
, MotherTitle.refSourceVertex as TitId, TitleName.value as Title, TitleYear.value as TitYr
, Duration.value as Dur 
, Genre.value as Genre 
from Vertex
  inner join VarCharObject as TrackName on     TrackName.refObject = Vertex.key 
                                           and TrackName.refAttribute = 1
                                           and Vertex.refObjectType = 23 -- 23: Recording (aka. Track)
  left outer join Edge as MotherAlbum on     MotherAlbum.refTargetVertex = Vertex.key  
                                         and MotherAlbum.refEdgeType = 5 -- 5: Album contains Recording
  left outer join VarCharObject as AlbumName on AlbumName.refObject = MotherAlbum.refSourceVertex
  left outer join IntObject     as AlbumYear on AlbumYear.refObject = MotherAlbum.refSourceVertex
  left outer join Edge as MotherTitle on     MotherTitle.refTargetVertex = Vertex.key  
                                         and MotherTitle.refEdgeType = 3 -- 3: Title recorded as Recording
  left outer join VarCharObject as TitleName on TitleName.refObject = MotherTitle.refSourceVertex
  left outer join IntObject     as TitleYear on TitleYear.refObject = MotherTitle.refSourceVertex
  
  left outer join VarCharObject as Duration  on Duration.refObject = Vertex.key and Duration.refAttribute = 2
  left outer join VarCharObject as Genre     on Genre.refObject = Vertex.key and Genre.refAttribute = 3
  
-- -----------------------------------------------------------------------------
select Vertex.key as TrackId
, TrackName.value as Name
, Duration.value as Dur 
, Genre.value as Genre 
, BPM.value as BPM 
, MotherAlbum.refSourceVertex as AlbumKey
from Vertex
  inner join VarCharObject as TrackName on     TrackName.refObject = Vertex.key 
                                           and TrackName.refAttribute = 1
                                           and Vertex.refObjectType = 23 -- 23: Recording (aka. Track)
  left outer join VarCharObject as Duration  on Duration.refObject = Vertex.key and Duration.refAttribute = 2
  left outer join VarCharObject as Genre     on Genre.refObject = Vertex.key and Genre.refAttribute = 3
  left outer join IntObject     as BPM       on BPM.refObject = Vertex.key and BPM.refAttribute = 33
  left outer join Edge as MotherAlbum on     MotherAlbum.refTargetVertex = Vertex.key  
                                         and MotherAlbum.refEdgeType = 5 -- 5: Album contains Recording
  

-- -----------------------------------------------------------------------------
create index IdxSourceVertex on Edge (refSourceVertex)
create index IdxTargetVertex on Edge (refTargetVertex)
--SLOWER: create index IdxEdgeType     on Edge (refEdgeType)
--create index IdxVarCharValue on VarCharObject (value) : Bringt kaum was.
drop index IdxVarCharValue
drop index IdxVarChar_RefAndValue

--NOT HELPFUL:
--create index IdxVarChar_Obj_Att_Value on VarCharObject (refObject, refAttribute, value)

-- -----------------------------------------------------------------------------
-- -----------------------------------------------------------------------------
-- View Track
-- create view Track as
select 
  ConstTrackType.Name as TrackType, Vertex.key as TrackId, TrackName.value as Name
, Duration.value as Dur, Genre.refAttribute as Att3, Genre.value as Genre, BPM.value as BPM, Label.value as Label, Comment.value as Comment
, Playcount.value as Plyd, Rating.value as Rtd   
, ConstAlbumType.Name as AlbType, MotherAlbum.refSourceVertex as AlbId, AlbumName.value as Album, AlbumYear.value as AlbYr
, ConstTitleType.Name as TitType, MotherTitle.refSourceVertex as TitId, TitleName.value as Title, TitleYear.value as TitYr
, ConstArtistType.Name as ArtstType, ComposerOfTitle.refSourceVertex as CompId, ComposerName.value as Composer, ComposerYoBirth.value as Birth
from Vertex
  -- Track ---------------------------------------------------------------------
  inner join VarCharObject as TrackName on     TrackName.refObject = Vertex.key 
                                           and TrackName.refAttribute = 1
                                           and Vertex.refObjectType = 23 -- 23: Recording (aka. Track)
  left outer join VarCharObject as Duration  on Duration.refObject  = Vertex.key and Duration.refAttribute  =  2
  left outer join VarCharObject as Genre     on Genre.refObject     = Vertex.key and Genre.refAttribute     =  3
  left outer join VarCharObject as Label     on Label.refObject     = Vertex.key and Label.refAttribute     =  4
  left outer join VarCharObject as Comment   on Comment.refObject   = Vertex.key and Comment.refAttribute   =  5
  left outer join IntObject     as BPM       on BPM.refObject       = Vertex.key and BPM.refAttribute       = 33
  left outer join IntObject     as Playcount on Playcount.refObject = Vertex.key and Playcount.refAttribute = 34
  left outer join IntObject     as Rating    on Rating.refObject    = Vertex.key and Rating.refAttribute    = 35
  -- ObjectType(Track)
  left outer join ObjectType as ConstTrackType on 23 = ConstTrackType.key
  -- Album ---------------------------------------------------------------------
  left outer join Edge as MotherAlbum on     MotherAlbum.refTargetVertex = Vertex.key  
                                         and MotherAlbum.refEdgeType = 5 -- 5: Album contains Recording
  left outer join VarCharObject as AlbumName on     AlbumName.refObject = MotherAlbum.refSourceVertex
  left outer join IntObject     as AlbumYear on     AlbumYear.refObject = MotherAlbum.refSourceVertex
                                                and AlbumYear.refAttribute = 31
  -- ObjectType(Album)
  left outer join ObjectType as ConstAlbumType on 30 = ConstAlbumType.key
  -- Title ---------------------------------------------------------------------
  left outer join Edge as MotherTitle on     MotherTitle.refTargetVertex = Vertex.key  
                                         and MotherTitle.refEdgeType = 3 -- 3: Title recorded as Recording
  left outer join VarCharObject as TitleName on TitleName.refObject = MotherTitle.refSourceVertex
  left outer join IntObject     as TitleYear on TitleYear.refObject = MotherTitle.refSourceVertex
  -- ObjectType(Title)
  left outer join ObjectType as ConstTitleType on 22 = ConstTitleType.key
  -- Composer
  left outer join Edge as ComposerOfTitle       on     ComposerOfTitle.refTargetVertex = MotherTitle.refSourceVertex
  left outer join VarCharObject as ComposerName on     ComposerName.refObject    = ComposerOfTitle.refSourceVertex
  left outer join IntObject as ComposerYoBirth  on     ComposerYoBirth.refObject = ComposerOfTitle.refSourceVertex 
                                                   and ComposerYoBirth.refAttribute = 31 
  -- ObjectType(Artist)
  left outer join ObjectType as ConstArtistType on 21 = ConstArtistType.key

  -- TRIALS on general INDEXING
  order by Genre.refAttribute, Genre.value

-- -----------------------------------------------------------------------------
-- drop index IdxVarCharValue
select * from sqlite_master
create index Idx_Attr_Obj_val on VarCharObject (refAttribute, refObject, value)
-- -----------------------------------------------------------------------------

 
-- -----------------------------------------------------------------------------
-- View Track
-- create view Track as
select 
  Vertex.key as key, TrackName.value as Name
, Duration.value as Duration, Genre.value as Genre, BPM.value as BPM, Label.value as Label, Comment.value as Comment
, Playcount.value as Playcount, Rating.value as Rating   
from Vertex
  -- Track ---------------------------------------------------------------------
  inner join VarCharObject as TrackName on     TrackName.refObject = Vertex.key 
                                           and TrackName.refAttribute = 1
                                           and Vertex.refObjectType = 23 -- 23: Recording (aka. Track)
  left outer join VarCharObject as Duration  on Duration.refObject  = Vertex.key and Duration.refAttribute  =  2
  left outer join VarCharObject as Genre     on Genre.refObject     = Vertex.key and Genre.refAttribute     =  3
  left outer join VarCharObject as Label     on Label.refObject     = Vertex.key and Label.refAttribute     =  4
  left outer join VarCharObject as Comment   on Comment.refObject   = Vertex.key and Comment.refAttribute   =  5
  left outer join IntObject     as BPM       on BPM.refObject       = Vertex.key and BPM.refAttribute       = 33
  left outer join IntObject     as Playcount on Playcount.refObject = Vertex.key and Playcount.refAttribute = 34
  left outer join IntObject     as Rating    on Rating.refObject    = Vertex.key and Rating.refAttribute    = 35

  
-- -----------------------------------------------------------------------------
-- -----------------------------------------------------------------------------
-- View Track
-- create table Recording
create table Recording as
select 
  Vertex.key as key, TrackName.value as Name
, Duration.value as Duration, Genre.value as Genre, BPM.value as BPM, Label.value as Label, Comment.value as Comment
, Playcount.value as Playcount, Rating.value as Rating   
from Vertex
  inner join VarCharObject as TrackName on     TrackName.refObject = Vertex.key 
                                           and TrackName.refAttribute = 1
                                           and Vertex.refObjectType = 23 -- 23: Recording (aka. Track)
  left outer join VarCharObject as Duration  on Duration.refObject  = Vertex.key and Duration.refAttribute  =  2
  left outer join VarCharObject as Genre     on Genre.refObject     = Vertex.key and Genre.refAttribute     =  3
  left outer join VarCharObject as Label     on Label.refObject     = Vertex.key and Label.refAttribute     =  4
  left outer join VarCharObject as Comment   on Comment.refObject   = Vertex.key and Comment.refAttribute   =  5
  left outer join IntObject     as BPM       on BPM.refObject       = Vertex.key and BPM.refAttribute       = 33
  left outer join IntObject     as Playcount on Playcount.refObject = Vertex.key and Playcount.refAttribute = 34
  left outer join IntObject     as Rating    on Rating.refObject    = Vertex.key and Rating.refAttribute    = 35

-- -----------------------------------------------------------------------------
create unique index IdxRecordingKey on Recording (Key)
create index IdxRecordingGenre on Recording (Genre)
create index IdxRecordingLabel on Recording (Label)
create index IdxRecording_Genre_Label on Recording (Genre, Label)

-- -----------------------------------------------------------------------------
-- -----------------------------------------------------------------------------
-- View Track
-- create table Album
create table Album as
select 
  Vertex.key as key, AlbumName.value as Name, AlbumYear.value as Year
from Vertex
  inner join VarCharObject as AlbumName on      AlbumName.refObject = Vertex.key 
                                            and AlbumName.refAttribute = 1
                                            and Vertex.refObjectType = 30 -- 30: Album
  left outer join IntObject as AlbumYear on     AlbumYear.refObject = Vertex.key
                                            and AlbumYear.refAttribute = 31
										   

-- -----------------------------------------------------------------------------
create unique index IdxAlbumKey on Album (Key)
create index IdxRecordingGenre on Recording (Genre)
create index IdxRecordingLabel on Recording (Label)
create index IdxRecording_Genre_Label on Recording (Genre, Label)


-- -----------------------------------------------------------------------------
-- View Track
-- create view Track as
select 
  Recording.key as TrackId, Recording.Name
, Recording.Duration, Recording.Genre, Recording.BPM, Recording.Label, Recording.Comment
, Recording.Playcount, Recording.Rating   
, ConstAlbumType.Name as AlbType, MotherAlbum.refSourceVertex as AlbId, AlbumName.value as Album, AlbumYear.value as AlbYr
, ConstTitleType.Name as TitType, MotherTitle.refSourceVertex as TitId, TitleName.value as Title, TitleYear.value as TitYr
, ConstArtistType.Name as ArtstType, ComposerOfTitle.refSourceVertex as CompId, ComposerName.value as Composer, ComposerYoBirth.value as Birth
from Vertex
  -- Track ---------------------------------------------------------------------
  inner join Recording                  on     Recording.key = Vertex.key 
  -- Album ---------------------------------------------------------------------
  left outer join Edge as MotherAlbum on     MotherAlbum.refTargetVertex = Vertex.key  
                                         and MotherAlbum.refEdgeType = 5 -- 5: Album contains Recording
  left outer join VarCharObject as AlbumName on     AlbumName.refObject = MotherAlbum.refSourceVertex
  left outer join IntObject     as AlbumYear on     AlbumYear.refObject = MotherAlbum.refSourceVertex
                                                and AlbumYear.refAttribute = 31
  -- ObjectType(Album)
  left outer join ObjectType as ConstAlbumType on 30 = ConstAlbumType.key
  -- Title ---------------------------------------------------------------------
  left outer join Edge as MotherTitle on     MotherTitle.refTargetVertex = Vertex.key  
                                         and MotherTitle.refEdgeType = 3 -- 3: Title recorded as Recording
  left outer join VarCharObject as TitleName on TitleName.refObject = MotherTitle.refSourceVertex
  left outer join IntObject     as TitleYear on TitleYear.refObject = MotherTitle.refSourceVertex
  -- ObjectType(Title)
  left outer join ObjectType as ConstTitleType on 22 = ConstTitleType.key
  -- Composer
  left outer join Edge as ComposerOfTitle       on     ComposerOfTitle.refTargetVertex = MotherTitle.refSourceVertex
  left outer join VarCharObject as ComposerName on     ComposerName.refObject    = ComposerOfTitle.refSourceVertex
  left outer join IntObject as ComposerYoBirth  on     ComposerYoBirth.refObject = ComposerOfTitle.refSourceVertex 
                                                   and ComposerYoBirth.refAttribute = 31 
  -- ObjectType(Artist)
  left outer join ObjectType as ConstArtistType on 21 = ConstArtistType.key
  

-- -----------------------------------------------------------------------------
-- View Track
-- create view Track as
select 
  Recording.key as TrackId, Recording.Name
, Recording.Duration, Recording.Genre, Recording.BPM, Recording.Label, Recording.Comment
, Recording.Playcount, Recording.Rating   
, ConstAlbumType.Name as AlbType, Album.key as AlbId, Album.Name as Album, Album.Year as AlbYr
, ConstTitleType.Name as TitType, MotherTitle.refSourceVertex as TitId, TitleName.value as Title, TitleYear.value as TitYr
, ConstArtistType.Name as ArtstType, ComposerOfTitle.refSourceVertex as CompId, ComposerName.value as Composer, ComposerYoBirth.value as Birth
from Vertex
  -- Track ---------------------------------------------------------------------
  inner join Recording                  on     Recording.key = Vertex.key 
  -- Album ---------------------------------------------------------------------
  left outer join Edge as MotherAlbum on     MotherAlbum.refTargetVertex = Vertex.key  
                                         and MotherAlbum.refEdgeType = 5 -- 5: Album contains Recording
  left outer join Album on  Album.key = MotherAlbum.refSourceVertex
  left outer join IntObject     as AlbumYear on     AlbumYear.refObject = MotherAlbum.refSourceVertex
                                                and AlbumYear.refAttribute = 31
  -- ObjectType(Album)
  left outer join ObjectType as ConstAlbumType on 30 = ConstAlbumType.key
  -- Title ---------------------------------------------------------------------
  left outer join Edge as MotherTitle on     MotherTitle.refTargetVertex = Vertex.key  
                                         and MotherTitle.refEdgeType = 3 -- 3: Title recorded as Recording
  left outer join VarCharObject as TitleName on TitleName.refObject = MotherTitle.refSourceVertex
  left outer join IntObject     as TitleYear on TitleYear.refObject = MotherTitle.refSourceVertex
  -- ObjectType(Title)
  left outer join ObjectType as ConstTitleType on 22 = ConstTitleType.key
  -- Composer
  left outer join Edge as ComposerOfTitle       on     ComposerOfTitle.refTargetVertex = MotherTitle.refSourceVertex
  left outer join VarCharObject as ComposerName on     ComposerName.refObject    = ComposerOfTitle.refSourceVertex
  left outer join IntObject as ComposerYoBirth  on     ComposerYoBirth.refObject = ComposerOfTitle.refSourceVertex 
                                                   and ComposerYoBirth.refAttribute = 31 
  -- ObjectType(Artist)
  left outer join ObjectType as ConstArtistType on 21 = ConstArtistType.key
  
