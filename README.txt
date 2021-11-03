** C based server-client grocery billing system **


The 
CREATE DATABASE Store;
USE Store;
CREATE  TABLE Store_Inventory (
  product_id INT AUTO_INCREMENT PRIMARY KEY ,
  product_display_name VARCHAR(150) NOT NULL ,
  retail_price INT NOT NULL,
  wholesale_price DECIMAL(19,4) NOT NULL ,
  num_in_stock INT NOT NULL
  );



