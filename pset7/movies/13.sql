--write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

select name from people
JOIN movies ON movies.id = stars.movie_id
JOIN stars ON people.id = stars.person_id
where movies.id in
(SELECT movie_id FROM stars
JOIN people ON people.id = stars.person_id
WHERE name = "Kevin Bacon" and birth=1958) and
not name="Kevin Bacon";