-- Q-1. Write an SQL query to fetch “FIRST_NAME” from Worker table using the alias name as <WORKER_NAME>.
SELECT FIRST_NAME AS WORKER_NAME FROM Worker;

-- Q-2. Write an SQL query to fetch “FIRST_NAME” from Worker table in upper case.
SELECT ucase(FIRST_NAME) FROM Worker;
-- another
SELECT UPPER(FIRST_NAME) FROM Worker;

-- Q-3. Write an SQL query to fetch unique values of DEPARTMENT from Worker table.
SELECT DISTINCT DEPARTMENT FROM Worker;
-- another approach
SELECT DEPARTMENT FROM Worker GROUP BY DEPARTMENT;

-- Q-4. Write an SQL query to print the first three characters of FIRST_NAME from Worker table.
SELECT substring(FIRST_NAME, 1, 3) FROM Worker;
-- string, start_pos, length
-- If length is more than the number of characters possible, then only the possible characters are returned
SELECT substring(FIRST_NAME, 1, 100) AS fname FROM Worker;

-- Q-5. Write an SQL query to find the position of the alphabet (‘b’) in the first name column ‘Amitabh’ from Worker table.
SELECT INSTR(first_name, 'b') FROM Worker WHERE first_name='Amitabh';

-- Q-6. Write an SQL query to print the FIRST_NAME from Worker table after removing white spaces from the right side.
SELECT RTRIM(first_name) FROM Worker;

-- Q-7. Write an SQL query to print the DEPARTMENT from Worker table after removing white spaces from the left side.
SELECT LTRIM(first_name) FROM Worker;

-- Remove white spaces from both side
SELECT RTRIM(LTRIM(first_name)) FROM Worker;

-- Q-8. Write an SQL query that fetches the unique values of DEPARTMENT from Worker table and prints its string length.
SELECT DISTINCT department, length(department) AS str_len FROM Worker;

-- Q-9. Write an SQL query to print the FIRST_NAME from Worker table after replacing ‘a’ with ‘A’.
SELECT REPLACE(first_name, 'a', 'A') FROM Worker;

-- Q-10. Write an SQL query to print the FIRST_NAME and LAST_NAME from Worker table into a single column COMPLETE_NAME.
-- A space char should separate them.
SELECT CONCAT(first_name, ' ', last_name) as COMPLETE_NAME FROM Worker;

-- Q-11. Write an SQL query to print all Worker details from the Worker table order by FIRST_NAME Ascending.
SELECT * FROM Worker ORDER BY first_name ASC;

-- Q-12. Write an SQL query to print all Worker details from the Worker table order by 
-- FIRST_NAME Ascending and DEPARTMENT Descending.
SELECT * FROM Worker ORDER BY first_name ASC, department DESC;

-- Q-13. Write an SQL query to print details for Workers with the first name as “Vipul” and “Satish” from Worker table.
SELECT * FROM Worker WHERE first_name IN ('Vipul', 'Satish');

-- Q-14. Write an SQL query to print details of workers excluding first names, “Vipul” and “Satish” from Worker table.
SELECT * FROM Worker WHERE first_name NOT IN ('Vipul', 'Satish');

-- Q-15. Write an SQL query to print details of Workers with DEPARTMENT name as “Admin*”.
SELECT * FROM Worker WHERE department LIKE 'Admin%';

-- Q-16. Write an SQL query to print details of the Workers whose FIRST_NAME contains ‘a’.
SELECT * FROM Worker WHERE first_name LIKE '%a%';

-- Q-17. Write an SQL query to print details of the Workers whose FIRST_NAME ends with ‘a’.
SELECT * FROM Worker WHERE first_name LIKE '%a';

-- Q-18. Write an SQL query to print details of the Workers whose FIRST_NAME ends with ‘h’ and contains six alphabets.
SELECT * FROM Worker WHERE first_name LIKE '%h' AND LENGTH(first_name)=6;
-- alternate, use 5 underscores
SELECT * FROM Worker WHERE first_name LIKE '_____h';

-- Q-19. Write an SQL query to print details of the Workers whose SALARY lies between 100000 and 500000.
SELECT * FROM Worker WHERE salary BETWEEN 100000 AND 500000;

-- Q-20. Write an SQL query to print details of the Workers who have joined in Feb’2014.
SELECT * FROM Worker WHERE joining_date LIKE '2014-02%';
-- good approach
SELECT * FROM Worker WHERE YEAR(joining_date)=2014 AND MONTH(joining_date)=2;

-- Q-21. Write an SQL query to fetch the count of employees working in the department ‘Admin’.
SELECT COUNT(department) as admin_len FROM Worker WHERE department='Admin';

-- Q-22. Write an SQL query to fetch worker full names with salaries >= 50000 and <= 100000.
SELECT concat(first_name, ' ', last_name) AS worker_full_name, salary FROM Worker
WHERE salary BETWEEN 50000 AND 100000;

-- Q-23. Write an SQL query to fetch the no. of workers for each department in the descending order.
SELECT department, COUNT(department) FROM Worker GROUP BY department ORDER BY COUNT(department) DESC;
-- alternate
SELECT department, COUNT(worker_id) as count_worker FROM Worker GROUP BY department
ORDER BY count_worker DESC;

-- Q-24. Write an SQL query to print details of the Workers who are also Managers.
SELECT w.* FROM Worker as w INNER JOIN
(SELECT * FROM Title WHERE worker_title='Manager') AS t ON w.worker_id=t.worker_ref_id;

-- alternate
SELECT w.* FROM Worker as w INNER JOIN Title AS t ON w.worker_id=t.worker_ref_id WHERE t.worker_title='Manager';

-- Q-25. Write an SQL query to fetch number (more than 1) of same titles in the ORG of different types.
SELECT worker_title, COUNT(worker_title) AS num_workers FROM title GROUP BY worker_title
HAVING num_workers > 1;

-- Q-26. Write an SQL query to show only odd rows from a table.
SELECT * FROM Worker WHERE MOD (worker_id, 2) != 0;
-- alternate
SELECT * FROM Worker WHERE MOD (worker_id, 2) <> 0;

-- Q-27. Write an SQL query to show only even rows from a table. 
SELECT * FROM Worker WHERE MOD (worker_id, 2) = 0;

-- Q-28. Write an SQL query to clone a new table from another table.
CREATE TABLE Worker_clone LIKE Worker;
INSERT INTO Worker_clone SELECT * FROM Worker;
SELECT * FROM Worker_clone;

-- Q-29. Write an SQL query to fetch intersecting records of two tables.
-- Basically intersection
SELECT DISTINCT w.* FROM Worker AS w
INNER JOIN Worker_clone AS wc ON w.worker_id=wc.worker_id;

-- Q-30. Write an SQL query to show records from one table that another table does not have.
-- minus
SELECT w.* FROM Worker AS w
LEFT JOIN Worker_clone AS wc USING(worker_id) WHERE wc.worker_id IS NULL;

-- Q-31. Write an SQL query to show the current date and time.
SELECT now() AS ctime;

-- Q-32. Write an SQL query to show the top n (say 5) records of a table order by descending salary.
SELECT * FROM Worker ORDER BY salary DESC LIMIT 5;

-- Q-33. Write an SQL query to determine the nth (say n=5) highest salary from a table.
-- using limit
SELECT * FROM Worker ORDER BY salary DESC LIMIT 4, 1;

-- Q-34. Write an SQL query to determine the 5th highest salary without using LIMIT keyword.
-- using subquery
-- select those salaries which are more than or equal to the current salary
-- if we take distinct salaries out of them and count it, then it should be 5
-- there can be multiple such values (which will be of same value) of salaries which satisfy this condition, so take distinct
SELECT DISTINCT salary FROM Worker AS w1
WHERE 1 = (
SELECT Count(DISTINCT w2.salary)
FROM Worker AS w2
WHERE w2.salary >= w1.salary
);
 
-- Q-35. Write an SQL query to fetch the list of pair of employees with the same salary.
SELECT * FROM Worker AS w1, Worker AS w2 WHERE w1.salary = w2.salary AND w1.worker_id != w2.worker_id;

-- Q-36. Write an SQL query to show the second highest salary from a table using sub-query.
SELECT DISTINCT w1.salary FROM Worker AS w1
WHERE 2 = (
SELECT COUNT(DISTINCT w2.salary)
FROM Worker AS w2
WHERE w2.salary >= w1.salary
);

-- Q-37. Write an SQL query to show one row twice in results from a table.
SELECT * FROM Worker
UNION ALL
SELECT * FROM Worker
ORDER BY worker_id;

-- Q-38. Write an SQL query to list worker_id who does not get bonus.
SELECT worker_id FROM Worker WHERE worker_id NOT IN (SELECT DISTINCT worker_ref_id FROM Bonus);

-- Q-39. Write an SQL query to fetch the first 50% records from a table.
SELECT * FROM Worker WHERE worker_id <= (SELECT max(worker_id)/2 FROM Worker);

-- Q-40. Write an SQL query to fetch the departments that have less than 4 people in it.
SELECT department, count(worker_id) AS num_workers FROM Worker GROUP BY department HAVING num_workers < 4;

-- Q-41. Write an SQL query to show all departments along with the number of people in there.
SELECT department, count(worker_id) AS num_workers FROM Worker GROUP BY department;

-- Q-42. Write an SQL query to show the last record from a table.
SELECT * FROM Worker WHERE worker_id = (SELECT max(worker_id) FROM Worker);

-- Q-43. Write an SQL query to fetch the first row of a table.
SELECT * FROM Worker WHERE worker_id = (SELECT min(worker_id) FROM Worker);

-- Q-44. Write an SQL query to fetch the last five records from a table.
(SELECT * FROM Worker ORDER BY worker_id DESC LIMIT 5) ORDER BY worker_id;

-- Q-45. Write an SQL query to print the name of employees having the highest salary in each department.
SELECT w.department, concat(w.first_name, ' ', w.last_name) AS full_name, w.salary FROM Worker AS w INNER JOIN
(SELECT department, max(salary) AS max_salary FROM Worker GROUP BY department) AS d
ON w.department = d.department AND w.salary = d.max_salary;

-- Q-46. Write an SQL query to fetch three max salaries from a table using co-related subquery
-- co-related subquery is sort-of nested loops
(SELECT * FROM (SELECT DISTINCT salary FROM Worker) AS w1
WHERE 3 >= (SELECT COUNT(w2.salary) FROM (SELECT DISTINCT salary FROM Worker) AS w2
WHERE w1.salary <= w2.salary)) ORDER BY w1.salary DESC;

-- Q-47. Write an SQL query to fetch three min salaries from a table using co-related subquery
(SELECT * FROM (SELECT DISTINCT salary FROM Worker) AS w1
WHERE 3 >= (SELECT COUNT(w2.salary) FROM (SELECT DISTINCT salary FROM Worker) AS w2
WHERE w2.salary <= w1.salary)) ORDER BY w1.salary ASC;

-- Q-48. Write an SQL query to fetch n max salaries from a table.
-- without limit
-- let n = 5
(SELECT * FROM (SELECT DISTINCT salary FROM Worker) AS w1
WHERE 5 >= (SELECT COUNT(w2.salary) FROM (SELECT DISTINCT salary FROM Worker) AS w2
WHERE w1.salary <= w2.salary)) ORDER BY w1.salary DESC;

-- Q-49. Write an SQL query to fetch departments along with the total salaries paid for each of them.
SELECT department, SUM(salary) as total_salary FROM Worker GROUP BY department;

-- Q-50. Write an SQL query to fetch the names of workers who earn the highest salary.
SELECT first_name, last_name, salary FROM Worker WHERE salary = (SELECT max(salary) FROM Worker);

