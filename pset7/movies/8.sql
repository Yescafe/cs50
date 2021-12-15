select people.name from people
inner join (
  select stars.person_id pid from stars
  inner join movies on movies.id=stars.movie_id
  where movies.title="Toy Story"
) on people.id=pid
