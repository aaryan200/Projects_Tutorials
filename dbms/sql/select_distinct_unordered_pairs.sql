CREATE TABLE pairs (
A INT,
B INT);

INSERT INTO pairs VALUES (1, 2), (2, 4), (3, 2), (2, 1), (4, 2), (3, 3), (3, 3);

SELECT * FROM pairs;

-- left join, join the same unordered pairs
SELECT * FROM pairs AS lt LEFT JOIN pairs AS rt
ON lt.A = rt.B AND lt.B = rt.A;

SELECT DISTINCT lt.* FROM pairs AS lt LEFT JOIN pairs AS rt
ON lt.A = rt.B AND lt.B = rt.A
WHERE rt.A IS NULL OR lt.A <= rt.A;

-- Using co-related subqueries
-- For every pair p1 in the first table, if there exists any pair p2 in the second table
-- which is a flipped pair of p1, and the first element of p1 is more than the second element of p1,
-- then don’t take that pair.
SELECT DISTINCT * FROM pairs p1 WHERE NOT EXISTS (SELECT
* FROM pairs p2 WHERE p1.A = p2.B AND p1.B = p2.A AND p1.A > p1.B);