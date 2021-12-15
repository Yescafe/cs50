select title from movies
inner join (
  select a.movie_id from (
    select movie_id from stars
    inner join (
      select people.id pid from people
      where name="Johnny Depp"
  ) on stars.person_id=pid) a,
  (
    select movie_id from stars
    inner join (
      select people.id pid from people
      where name="Helena Bonham Carter"
  ) on stars.person_id=pid) b
  where a.movie_id=b.movie_id
) s on movies.id=s.movie_id
