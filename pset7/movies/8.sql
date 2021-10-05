-- write a SQL query to list the names of all people who starred in Toy Story

select name from
people JOIN stars ON people.id = stars.person_id JOIN
movies ON stars.movie_id = movies.id
WHERE title = "Toy Story";