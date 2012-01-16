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

-- The sequence of records is significant and represents in-order traversal
-- of the "expanded tree" of the Dag
insert into Dag values (0, 0); -- Nil group
insert into Dag values (0, 1); -- (0:ROOT,  1:Songs)
insert into Dag values (1, 2); -- (1:Songs, 2:Blues) 
insert into Dag values (2, 4); -- (2:Blues, 4:St.Louis Blues)
insert into Dag values (2, 6); -- (2:Blues, 6:Blue Bossa)
insert into Dag values (1, 3); -- (1:Songs, 3:Latin)
insert into Dag values (3, 5); -- (3:Latin, 5:Oye Come Va)
insert into Dag values (3, 6); -- (3:Latin, 6:Blue Bossa)

-- -----------------------------------------------------------------------------
select Objects.name as Object, Types.name as Type, Dag.Child as ChildId, Dag.Parent as PatentId, 
  (select Objects.name from Objects where Objects.id = Dag.Parent) as Parent
  from Dag
  inner join Objects on     Dag.Child = Objects.id
  inner join Types   on Objects.TypeOf = Types.id

-- -----------------------------------------------------------------------------
-- The Dag in orderly fashion (parent->chiled) starting from root
select Dag.Parent as ParentId, Dag.Child as ChildId, 
  (select Objects.name from Objects where Objects.id = Dag.Parent) as Parent,
  Objects.name as Child, Types.name as Type 
  from Dag
  inner join Objects on     Dag.Child = Objects.id
  inner join Types   on Objects.TypeOf = Types.id
  where Dag.Child <> 0


-- ----------------------------------------------------------------------------
create view Collections as
select Dag.Parent as ParentId, Dag.Child as ChildId, Types.Id as TypeId,
  (select Objects.name from Objects where Objects.id = Dag.Parent) as Parent,
  Objects.name as Child, Types.name as Type 
  from Dag
  inner join Objects on      Dag.Child = Objects.id
  inner join Types   on Objects.TypeOf = Types.id

