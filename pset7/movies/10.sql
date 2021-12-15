select distinct people.name from people
inner join (
  select directors.person_id pid from directors
  inner join (
    select movies.id mid from movies
    inner join (
      select ratings.movie_id rmid from ratings
      where rating>=9.0
    ) on mid=rmid
  ) on directors.movie_id=mid
) on people.id=pid
