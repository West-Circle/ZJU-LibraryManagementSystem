IDE : Qt Creator 5.15.2 (MSVC2019 64bit)
Language : C++
Database : MySQL Database (You have to insert your MySQL password in connectdatabase.cpp)

When creating MySQL database , you need to set charset to UTF8 and Collation to utf8_general_ci
Create table :
create table admin (adminid varchar(10), password char(20), name varchar(10), contact_no char(20), primary key(adminid));
create table book (bno char(8), category char(10), title varchar(40), press varchar(30), year int, author varchar(20), price decimal(7,2), total int, stock int, primary key(bno));
create table card (cno char(10),password char(20),name varchar(10),department varchar(40),type char(1) check (type = ‘T’ OR type = ‘S’), primary key(cno));
create table borrow (cno char(10), bno char(8), adminid varchar(10), borrow_date date, return_date date, foreign key (cno) references card(cno), foreign key (bno) references book(bno), foreign key (adminid) references admin(adminid));
