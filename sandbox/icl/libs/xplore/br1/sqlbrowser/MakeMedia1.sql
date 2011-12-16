drop table Albums;
drop table Tracks;
drop table AlbumsByTracks;

create table Albums (id integer primary key, Title varchar, Artist varchar, Genre varchar, Rating number);

insert into Albums values (1, 'Kind of Blue', 'Miles Davis', 'Jazz', '9.3');
insert into Albums values (2, 'Nefertiti',    'Miles Davis', 'Jazz', '9.1');

create table Tracks (id integer primary key, Album integer, Pos integer, Title varchar, Artist varchar, Genre varchar, Rating number, Duration varchar, BPM number);

insert into Tracks values (1, 1, 1, 'So What', 'Miles Davis', 'Jazz', '9.6', '09:05', '80');
insert into Tracks values (2, 1, 2, 'Freddie Freeloader', 'Miles Davis', 'Jazz', '9.3', '09:35', '');

create table AlbumsByTracks (id integer primary key, Album integer, Track integer, Pos integer);

-- ----------------------------------------------------------------------------
-- select .. from Refering inner join Target on Refering.Pointer = Target.Id
-- ----------------------------------------------------------------------------
select Albums.Title, Albums.Genre, Tracks.Title, Tracks.Duration, Tracks.Artist
from Tracks
inner join Albums on Tracks.Album = Albums.Id
order by Albums.Title, Tracks.Pos

