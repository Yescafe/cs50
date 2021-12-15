select avg(rating) from ratings
inner join movies on movies.id=ratings.movie_id where movies.year=2012
