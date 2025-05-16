-- Online delivery system
CREATE DATABASE ods;
USE ods;

CREATE TABLE Customer (
cust_id INT PRIMARY KEY,
cname VARCHAR(255),
gender VARCHAR(2)
);

CREATE TABLE Order_details (
order_id INT,
delivery_date DATE,
cust_id INT,
PRIMARY KEY(order_id),
FOREIGN KEY (cust_id)
    REFERENCES Customer(cust_id)
);

CREATE TABLE fun (
id INT PRIMARY KEY,
fname VARCHAR(255) UNIQUE,
balance INT,
CONSTRAINT bal_check CHECK (balance > 1000)
);

INSERT INTO fun (id, fname, balance)
VALUES (1, 'aaryan', 500); -- Won't work

INSERT INTO fun (id, fname, balance)
VALUES (1, 'aaryan', 5000); -- works

INSERT INTO fun (id, fname, balance)
VALUES (2, 'aaryan', 50000); -- Wont' work

DROP TABLE fun;

CREATE TABLE fun (
    id INT,
	balance INT DEFAULT 0
);

INSERT INTO fun (id)
VALUES (1);

SELECT * FROM fun;

CREATE TABLE Account (
    id INT PRIMARY KEY NOT NULL,
    canme VARCHAR(250),
    balance INT NOT NULL DEFAULT 0
);

INSERT INTO Account (id, canme, balance)
VALUES (1, 'Aaryan', 1000);

-- add column interest_rate
ALTER TABLE Account ADD interest_rate FLOAT NOT NULL DEFAULT 4.5;

SELECT * FROM Account;

-- change dtype of interest_rate to DOUBLE
ALTER TABLE Account MODIFY interest_rate DOUBLE NOT NULL DEFAULT 5.5;

INSERT INTO Account (id, canme, balance)
VALUES (2, 'Fake', 10000);

-- get name and dtype of all the columns
DESC Account;

-- Rename the column
ALTER TABLE Account
CHANGE COLUMN interest_rate savings_interest FLOAT NOT NULL DEFAULT 4.5;

-- Delete this column
ALTER TABLE Account DROP COLUMN savings_interest;

-- Rename table
ALTER TABLE Account RENAME TO account_details;

SELECT * FROM account_details;

-- INSERT only the values inside some columns, rest are default
INSERT INTO Customer (cust_id, cname) VALUES (1, 'Aaryan');

SELECT * FROM Customer;

-- UPDATE gender and name
UPDATE Customer SET cname='Aaryan Kaushik', gender='M' WHERE cust_id=1;

-- update all rows
-- disable security
SET SQL_SAFE_UPDATES = 0;
UPDATE Customer SET cust_id = cust_id + 1;

-- enable security
SET SQL_SAFE_UPDATES = 1;

-- delete row
DELETE FROM Customer WHERE cust_id=2;

-- delete all rows
SET SQL_SAFE_UPDATES = 0;
DELETE FROM Customer;

DESC Order_details;


-- delete and create tables again
DROP TABLE Order_details;
DROP TABLE Customer;
CREATE TABLE Customer (
cust_id INT PRIMARY KEY,
cname VARCHAR(255),
gender VARCHAR(2)
);

CREATE TABLE Order_details (
order_id INT,
delivery_date DATE,
cust_id INT,
PRIMARY KEY(order_id),
FOREIGN KEY (cust_id)
    REFERENCES Customer(cust_id)
);
-- insert some values in customer and order_details
INSERT INTO Customer
VALUES (1, 'Aaryan', 'M');

INSERT INTO Order_details
VALUES (1, '2024-04-03', 1);

SELECT * FROM Customer;
SELECT * FROM Order_details;

-- Try to delete from customer, foreign key constraint violation
DELETE FROM Customer WHERE cust_id=1;

-- on delete cascade
DROP TABLE Order_details;
CREATE TABLE Order_details (
order_id INT,
delivery_date DATE,
cust_id INT,
PRIMARY KEY(order_id),
FOREIGN KEY (cust_id)
    REFERENCES Customer(cust_id)
    ON DELETE CASCADE
);
INSERT INTO Order_details
VALUES (1, '2024-04-03', 1), (2, '2024-04-04', 1);

DELETE FROM Customer WHERE cust_id=1; -- Deleted from customer and orders

-- on delete set null
DROP TABLE Order_details;
CREATE TABLE Order_details (
order_id INT,
delivery_date DATE,
cust_id INT,
PRIMARY KEY(order_id),
FOREIGN KEY (cust_id)
    REFERENCES Customer(cust_id)
    ON DELETE SET NULL
);
INSERT INTO Customer
VALUES (1, 'Aaryan', 'M');
INSERT INTO Order_details
VALUES (1, '2024-04-03', 1), (2, '2024-04-04', 1);

DELETE FROM Customer WHERE cust_id=1; -- Deleted from customer, not from orders

SELECT * FROM Customer;

-- replace
REPLACE INTO Customer (cust_id, cname)
VALUES (1, 'Aaryan'); -- inserts row

REPLACE INTO Customer (cust_id, cname, gender)
VALUES (1, 'Kaushik', 'M'); -- updates row

-- other syntax
REPLACE INTO Customer SET cust_id=2, cname='Lol';
REPLACE INTO Customer(cust_id, cname)
    SELECT cust_id, cname
    FROM Customer WHERE cust_id=2;


