select title from movies,ratings where movies.id=ratings.movie_id
and movies.id in
(select movie_id from stars where person_id in
    (select id from people where name="Chadwick Boseman"))
order by ratings.rating desc
limit 5;
