USE ods;

DROP TABLE order_details, customer;

CREATE TABLE Customer (
cust_id INT PRIMARY KEY,
cname VARCHAR(255),
gender VARCHAR(2)
);

CREATE TABLE Order_details (
order_id INT,
delivery_date DATE,
ref_cust_id INT,
PRIMARY KEY(order_id),
FOREIGN KEY (ref_cust_id)
    REFERENCES Customer(cust_id)
);

INSERT INTO Customer
VALUES (1, 'Aaryan', 'M'), (2, 'Fake', 'F');

INSERT INTO Order_details
VALUES (1, '2024-04-03', 1),
    (2, '2024-04-04', 1),
    (3, '2024-04-03', 2);

SELECT * FROM Customer;
SELECT * FROM Order_details;

-- Inner join, match cust_id column with ref_cust_id
SELECT c.*, o.* FROM Customer AS c INNER JOIN Order_details AS o
ON c.cust_id=o.ref_cust_id;

-- select specific columns
SELECT o.*, c.cust_id, c.cname FROM Customer AS c INNER JOIN Order_details AS o
ON c.cust_id=o.ref_cust_id;

-- use of alias
SELECT * FROM Customer AS c;

-- left join
INSERT INTO Customer
VALUES (3, 'Fake1', 'M'), (4, 'Fake2', 'F');
SELECT c.*, o.* FROM Customer AS c LEFT JOIN Order_details AS o
ON c.cust_id=o.ref_cust_id;

-- right join
SELECT o.*, c.* FROM Customer AS c RIGHT JOIN Order_details AS o
ON (c.cust_id=o.ref_cust_id);

-- full join
SELECT * FROM Customer AS c LEFT JOIN Order_details AS o
ON c.cust_id=o.ref_cust_id
UNION
SELECT * FROM Customer AS c RIGHT JOIN Order_details AS o
ON c.cust_id=o.ref_cust_id;

-- cross join
SELECT * FROM Customer AS c CROSS JOIN Order_details AS o;

-- self join
SELECT * FROM Customer AS c1 INNER JOIN Customer as c2
ON c1.cust_id=c2.cust_id;

-- inner join without join
SELECT c.*, o.* FROM Customer AS c, Order_details AS o
WHERE c.cust_id=o.ref_cust_id;

-- For testing set operations
CREATE TABLE table1 (
    id INT,
    ename VARCHAR(255),
    post VARCHAR(255)
);

CREATE TABLE table2 (
    id INT,
    ename VARCHAR(255),
    post VARCHAR(255)
);

INSERT INTO table1 VALUES
(1, 'A', 'P1'),
(2, 'B', 'P2'),
(3, 'C', 'P3');

INSERT INTO table2 VALUES
(1, 'A', 'P1'),
(2, 'B', 'P2'),
(4, 'D', 'P4');

-- union
SELECT * FROM table1
UNION
SELECT * FROM table2;

-- intersection
INSERT INTO table2 VALUES
(2, 'B', 'P2');
SELECT table1.* FROM table1 INNER JOIN table2 USING (id); -- will be incorrect
SELECT DISTINCT table1.* FROM table1 INNER JOIN table2 USING (id); -- correct

-- Minus
SELECT table1.* FROM table1 LEFT JOIN table2 USING(id)
WHERE table2.id IS NULL;

-- Sub queries

CREATE TABLE employee (
    id INT,
    ename VARCHAR(255),
    age INT NOT NULL DEFAULT 18
);

TRUNCATE employee;

SELECT * FROM employee;

INSERT INTO employee VALUES
(1, 'A', 25),
(2, 'B', 26),
(3, 'C', 23),
(4, 'D', 32);

-- 3rd oldest employee
SELECT * FROM employee AS e1
WHERE 3 = (
	SELECT COUNT(e2.age)
	FROM employee AS e2
	WHERE e2.age >= e1.age
);

-- Another method
TRUNCATE employee;
INSERT INTO employee VALUES
(1, 'A', 25),
(2, 'B', 26),
(3, 'C', 23),
(4, 'D', 32),
(5, 'E', 25);

-- All employees whose age is that of 3rd oldest
SELECT * FROM employee as e1
WHERE 3 = (
    SELECT COUNT(e2.age)
    FROM (SELECT DISTINCT age FROM employee) AS e2
    WHERE e2.age >= e1.age
);

-- Views
CREATE VIEW name_view AS SELECT id, ename FROM employee;

SELECT * FROM name_view;

-- Alter view
ALTER VIEW name_view AS SELECT ename, age FROM employee;

-- Drop view
DROP VIEW IF EXISTS name_view;






