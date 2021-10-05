/* write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
Your query should output a table with a single column for the name of each person. */

select distinct name FROM
people JOIN directors ON people.id = directors.person_id JOIN
movies ON movies.id = directors.movie_id JOIN
ratings ON movies.id = ratings.movie_id
WHERE people.id = directors.person_id and rating >= 9.0;