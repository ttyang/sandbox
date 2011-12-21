drop table Albums;
drop table Tracks;
drop table AlbumsByTracks;

create table Albums (id integer primary key, Title varchar, Artist varchar, Genre varchar, Rating number);

insert into Albums values (1, 'Kind of Blue', 'Miles Davis', 'Jazz', '9.3');
insert into Albums values (2, 'Nefertiti',    'Miles Davis', 'Jazz', '9.1');

create table Tracks (id integer primary key, Title varchar, Artist varchar, Genre varchar, Rating number, Duration varchar, BPM number);

-- Kind of Blue
insert into Tracks values (1, 'So What', 'Miles Davis', 'Jazz', '9.6', '09:05', '80');
insert into Tracks values (2, 'Freddie Freeloader', 'Miles Davis', 'Jazz', '9.3', '09:35', '');
-- Nefertiti
insert into Tracks values (3, 'Nefertiti', 'Wayne Shorter', 'Jazz', '9.0', '07:52', '80');
insert into Tracks values (4, 'Fall',      'Wayne Shorter', 'Jazz', '9.3', '06:39', '');


create table AlbumsByTracks (Album integer, Track integer, Pos integer);

insert into AlbumsByTracks values (1, 1, 1);
insert into AlbumsByTracks values (1, 2, 2);
insert into AlbumsByTracks values (2, 3, 1);
insert into AlbumsByTracks values (2, 4, 2);


-- ----------------------------------------------------------------------------
select Albums.Title, Albums.Genre, Tracks.Title, Tracks.Duration, Tracks.Artist
from AlbumsByTracks, Albums, Tracks
where AlbumsByTracks.Album = Albums.Id and AlbumsByTracks.Track = Tracks.Id

-- ----------------------------------------------------------------------------
select Albums.Title, Albums.Genre, Tracks.Title, Tracks.Duration, Tracks.Artist
from AlbumsByTracks
inner join Albums on AlbumsByTracks.Album = Albums.Id
inner join Tracks on AlbumsByTracks.Track = Tracks.Id

-- ----------------------------------------------------------------------------
create view TracksInAlbums as
  select Albums.Title, Albums.Genre, Tracks.Title, Tracks.Duration, Tracks.Artist
  from AlbumsByTracks
    inner join Albums on AlbumsByTracks.Album = Albums.Id
    inner join Tracks on AlbumsByTracks.Track = Tracks.Id


-- ----------------------------------------------------------------------------
-- Grouping
select AlbumsByTracks.Album, Albums.Title, Albums.Genre, Tracks.Title, Tracks.Artist, 
    sum(Tracks.Duration) as SumDur
from AlbumsByTracks
inner join Albums on AlbumsByTracks.Album = Albums.Id
inner join Tracks on AlbumsByTracks.Track = Tracks.Id
where AlbumsByTracks.Album = Albums.Id and AlbumsByTracks.Track = Tracks.Id
group by AlbumsByTracks.Album

-- ----------------------------------------------------------------------------
-- ----------------------------------------------------------------------------
-- select .. from Refering inner join Target on Refering.Pointer = Target.Id
-- ----------------------------------------------------------------------------
select Albums.Title, Albums.Genre, Tracks.Title, Tracks.Duration, Tracks.Artist
from Tracks
inner join Albums on Tracks.Album = Albums.Id
order by Albums.Title, Tracks.Pos

