drop table Types;
drop table Objects;
drop table Groups;

-- -----------------------------------------------------------------------------
create table Types (id integer primary key, Name varchar);

insert into Types values (0, 'Nil');
insert into Types values (1, 'Collection');
insert into Types values (2, 'Object');

-- -----------------------------------------------------------------------------
create table Objects (id integer primary key, TypeOf integer, Name varchar);

insert into Objects values (0, 0, 'Nil');
insert into Objects values (1, 1, 'Songs');
insert into Objects values (2, 1, 'Blues');
insert into Objects values (3, 1, 'Latin');
insert into Objects values (4, 2, 'St. Louis Blues');
insert into Objects values (5, 2, 'Oye Come Va');
insert into Objects values (6, 2, 'Blue Bossa');

-- -----------------------------------------------------------------------------
--  This is a directed acyclic graph.  
create table Dag (Parent integer, Child integer, primary key (Parent, Child) );

insert into Dag values (0, 0); -- Nil group
insert into Dag values (0, 1); -- (0:ROOT,  1:Songs)
insert into Dag values (1, 2); -- (1:Songs, 2:Blues) 
insert into Dag values (1, 3); -- (1:Songs, 3:Latin)
insert into Dag values (2, 4); -- (2:Blues, 4:St.Louis Blues)
insert into Dag values (3, 5); -- (3:Latin, 4:Oye Come Va)
insert into Dag values (2, 6); -- (2:Blues, 4:Blue Bossa)
insert into Dag values (3, 6); -- (3:Latin, 4:Blue Bossa)

-- -----------------------------------------------------------------------------
select Objects.name as Object, Types.name as Type, Dag.Child as Chld, Dag.Parent as Prnt, 
  (select Objects.name from Objects where Objects.id = Dag.Parent) as Parent
  from Dag
  inner join Objects on     Dag.Child = Objects.id
  inner join Types   on Objects.TypeOf = Types.id

-- ----------------------------------------------------------------------------
