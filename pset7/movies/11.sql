select title from movies
inner join (
  select stars.movie_id smid from stars
  inner join (
    select id pid from people where name="Chadwick Boseman"
  ) on pid=stars.person_id
) on movies.id=smid
inner join ratings on ratings.movie_id=movies.id
order by rating desc
limit 5
