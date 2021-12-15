select distinct people.name from people
inner join (
  select person_id pid from stars
  inner join (select id mid from movies where year=2004)
  on mid=stars.movie_id
) on people.id=pid
order by people.birth
