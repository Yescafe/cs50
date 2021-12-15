select distinct s.pname from stars
inner join (
  select id pid from people
  where name="Kevin Bacon" and birth=1958
) on pid=stars.person_id
inner join (
  select a.name pname, movie_id from stars
  inner join (
    select name, id pid from people
    where name!="Kevin Bacon" or birth!=1958
  ) a on pid=stars.person_id
) s on stars.movie_id=s.movie_id
