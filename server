#include <mysql.h>
#include <stdio.h>
#include <string.h>


int getInventory( MYSQL* conn) {

    if (mysql_query(conn, "SELECT * FROM Store_Inventory")) { // grab data from store inventory
        printf("Unable to complete quereyr\n");
        mysql_close(conn);

    }

}

int addInventory(MYSQL* conn,


int main()
{
   // params for connecting to locally hosted server
    char server[16] = "127.0.0.1";
    char username[16] = "root";
    char password[16] = "password";
    char database[16] = "Store";

    MYSQL* conn = mysql_init(NULL);
    MYSQL_ROW record;

    if (conn == NULL) {
        printf("MySQL initialization failed");
        return 1;
    }

    if (mysql_real_connect(conn, server, username, password, database, 0, NULL, 0) == NULL) { //establish connection with mysql server
        printf("Unable to connect with MySQL server\n");
        mysql_close(conn);
        return 1;
    }


        getInventory(conn);


    MYSQL_RES* rs = mysql_store_result(conn);

    if (rs == NULL) {
        printf("Unable to compile SQL statement\n");
        mysql_close(conn);
        return 1;
    }

    while (record = mysql_fetch_row(rs)) {
        printf("%s %s %s\n", record[0], record[1], record[2]); // display data from table
    }
    mysql_close(conn);

    return 0;
}
