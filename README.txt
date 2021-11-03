** C based server-client grocery billing system **

The server for this system runs on Ubuntu using mysql to store data. The c server interacts with a locally hosted mysql server and acts an an intermediary between the client program(s) and the stored data. Stores run client programs to access the central database.



 *********** DEPENDENCIES *********** 

  mysql-server
  default-libmysqlclient-dev

 *********** MYSQL COMMANDS TO INITIALIZE DATA STRUCTURE *********** 

  CREATE DATABASE Store;
  USE Store;
  CREATE  TABLE Store_Inventory (
    product_id INT AUTO_INCREMENT PRIMARY KEY ,
    product_display_name VARCHAR(150) NOT NULL ,
    retail_price DECIMAL(19,4) NOT NULL ,
    wholesale_price DECIMAL(19,4) NOT NULL ,
    num_in_stock INT NOT NULL,
    num_sold INT NOT NULL
    net_profit DECIMAL(19,4) NOT NULL ,
    gross_profit DECIMAL(19,4) NOT NULL ,
    );

 *********** MYSQL TABLES AND FIELDS *********** 
  mysql> show columns from Store_Inventory;
  +----------------------+---------------+------+-----+---------+----------------+
  | Field                | Type          | Null | Key | Default | Extra          |
  +----------------------+---------------+------+-----+---------+----------------+
  | product_id           | int(11)       | NO   | PRI | NULL    | auto_increment |
  | product_display_name | varchar(150)  | NO   |     | NULL    |                |
  | retail_price         | decimal(19,4) | NO   |     | NULL    |                |
  | wholesale_price      | decimal(19,4) | NO   |     | NULL    |                |
  | num_in_stock         | int(11)       | NO   |     | NULL    |                |
  | num_sold             | int(11)       | NO   |     | NULL    |                |
  | net_profit           | double(19,4)  | NO   |     | NULL    |                |
  | gross_profit         | decimal(19,4) | NO   |     | NULL    |                |
  +----------------------+---------------+------+-----+---------+----------------+
  8 rows in set (0.01 sec)

 *********** COMPILING AND RUNNING C-MYSQL TEST SCRIPT ***********
 
   Example output:

  bigsley@localhost:/home/bigsley/data_structures_final# gcc server.c -o server  `mysql_config --cflags --libs` ; ./server
  1254 Trident Gum 1.9900
  12251 Granny Smith Apples 1.9900
  12252 Honey Nut Cheerios 5.2100
