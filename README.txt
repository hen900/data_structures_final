** C based server-client grocery billing system **


CREATE DATABASE Store;
USE Store;
CREATE  TABLE Store_Inventory (
  product_id INT AUTO_INCREMENT PRIMARY KEY ,
  product_display_name VARCHAR(150) NOT NULL ,
  retail_price INT NOT NULL,
  wholesale_price DECIMAL(19,4) NOT NULL ,
  num_in_stock INT NOT NULL
  );



mysql> show columns from Store_Inventory;
+----------------------+---------------+------+-----+---------+----------------+
| Field                | Type          | Null | Key | Default | Extra          |
+----------------------+---------------+------+-----+---------+----------------+
| product_id           | int(11)       | NO   | PRI | NULL    | auto_increment |
| product_display_name | varchar(150)  | NO   |     | NULL    |                |
| retail_price         | int(11)       | NO   |     | NULL    |                |
| wholesale_price      | decimal(19,4) | NO   |     | NULL    |                |
| num_in_stock         | int(11)       | NO   |     | NULL    |                |
+----------------------+---------------+------+-----+---------+----------------+
5 rows in set (0.00 sec)

