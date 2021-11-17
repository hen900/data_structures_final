#include <mysql.h>

#include <stdio.h>

#include <string.h>


void insert_int(MYSQL * conn, int id, int val, char * field) {

        char command[512];
        snprintf(command, 512, "UPDATE Store_Inventory SET %s = %d WHERE product_id = %d", field, val, id);
        //    printf("%s\n",command);
        mysql_query(conn, command);

}

void insert_double(MYSQL * conn, int id, float val, char * field) {

        char command[512];
        snprintf(command, 512, "UPDATE Store_Inventory SET %s = %f WHERE product_id = %d", field, val, id);
        //  printf("%s\n",command);
        mysql_query(conn, command);

}

int get_int(MYSQL * conn, int id, char * field) {
        char command[512];
        snprintf(command, 512, "SELECT %s FROM Store_Inventory WHERE product_id = %d", field, id);
        // printf("%s\n",command);
        mysql_query(conn, command);
        MYSQL_RES * result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        return atoi(row[0]);

}

double get_double(MYSQL * conn, int id, char * field) {
        char command[512];
        snprintf(command, 512, "SELECT %s FROM Store_Inventory WHERE product_id = %d", field, id);
        //printf("%s\n",command);
        mysql_query(conn, command);
        MYSQL_RES * result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        return atof(row[0]);

}

int findItem(MYSQL * conn, int id) {

        char * row1[] = {
                "product_id",
                "product_display_name",
                "retail_price",
                "wholesale_price",
                "num_in_stock",
                "num_sold",
                "net_profit",
                "gross_profit"
        };
        char command[512];
        snprintf(command, 512, "SELECT * FROM Store_Inventory WHERE product_id = %d", id);
        // printf("%s\n",command);
        mysql_query(conn, command);
        MYSQL_RES * result = mysql_store_result(conn);
        MYSQL_ROW record = mysql_fetch_row(result);
        if (record == NULL) {
                printf("\nItem not Found!\n");
                return 1;
        }
        printf("\n\n************** ITEM SEARCH FOR ID #%d ************** \n\n", id);
        printf("%-10s | %-35s | %15s | %15s | %15s | %15s | %15s | %15s\n", row1[0], row1[1], row1[2], row1[3], row1[4], row1[5], row1[6], row1[7]);
        printf("%-10s | %-35s | %15s | %15s | %15s | %15s | %15s | %15s\n", record[0], record[1], record[2], record[3], record[4], record[5], record[6], record[7]);

        return 0;
}

int dumpInventory(MYSQL * conn, MYSQL_ROW record) {

        char * row1[] = {
                "product_id",
                "product_display_name",
                "retail_price",
                "wholesale_price",
                "num_in_stock",
                "num_sold",
                "net_profit",
                "gross_profit"
        };

        if (mysql_query(conn, "SELECT * FROM Store_Inventory")) {
                printf("Unable to connect with MySQL server 1 \n");
                mysql_close(conn);
                return 1;
        }

        MYSQL_RES * rs = mysql_store_result(conn);

        if (rs == NULL) {
                printf("Unable to compile SQL statement\n");
                mysql_close(conn);
                return 1;
        }

        printf("\n\n************** STORE INVENTORY ************** \n\n");

        printf("%-10s | %-35s | %15s | %15s | %15s | %15s | %15s | %15s\n", row1[0], row1[1], row1[2], row1[3], row1[4], row1[5], row1[6], row1[7]);

        for (int i = 0; i < 156; i++) {
                printf("*");
        }
        printf("\n");

        while (record = mysql_fetch_row(rs)) {
                printf("%-10s | %-35s | %15s | %15s | %15s | %15s | %15s | %15s\n", record[0], record[1], record[2], record[3], record[4], record[5], record[6], record[7]);
        }

        return 0;

}

int sellItem(MYSQL * conn, int id, int n) {

        int numStock = get_int(conn, id, "num_in_stock");

        if (n > numStock) {
                printf("\n **** ERROR : Cannot sell %d items, exceeds the %d in stock... **** \n", n, numStock);
                return 1;
        }

        numStock = numStock - n;

        int numSold = get_int(conn, id, "num_sold");
        numSold = numSold + n;

        double retailPrice = get_double(conn, id, "retail_price");

        double wholesalePrice = get_double(conn, id, "wholesale_price");

        double grossProfit = numSold * retailPrice;

        double netProfit = grossProfit - (wholesalePrice * numSold);

        insert_int(conn, id, numSold, "num_sold");
        insert_int(conn, id, numStock, "num_in_stock");

        insert_double(conn, id, netProfit, "net_profit");
        insert_double(conn, id, grossProfit, "gross_profit");

}

int main() {
        char server[16] = "localhost";
        char username[16] = "root";
        char password[16] = "THEbomb.com1234!";
        char database[16] = "Store";

        MYSQL * conn = mysql_init(NULL);
        MYSQL_ROW record;

        if (conn == NULL) {
                printf("MySQL initialization failed");
                return 1;
        }

        if (mysql_real_connect(conn, server, username, password, database, 0, NULL, 0) == NULL) {
                printf("Unable to connect with MySQL server\n");
                mysql_close(conn);
                return 1;
        }

        printf(" *** Connected to Mysql database at  %s...  *** \n\n", server);

        int choice, id, n;
        unsigned long int fact;

        while (1) {

                printf("\n\n\t\t ********** Store Inventory Management System ********** \n\n\n");
                printf("1. Print Store Inventory \n");
                printf("2. Search for Item\n");
                printf("3. Sell Item\n");
                printf("4. Exit\n\n\n");
                printf("Enter your choice :  ");
                scanf("%d", & choice);

                switch (choice) {
                case 1:
                        dumpInventory(conn, record);
                        break;

                case 2:
                        printf("Enter item Product ID: ");
                        scanf("%d", & id);
                        findItem(conn, id);
                        break;

                case 3:
                        printf("Enter Product ID of Sold Item: ");
                        scanf("%d", & id);
                        if (findItem(conn, id) == 0) {
                                printf("Enter number of items sold: ");
                                scanf("%d", & n);
                                sellItem(conn, id, n);

                        }
                        break;

                case 4:
                        printf("\n\n\t\t\tExiting...\n\n\n");
                        exit(0); // terminates the complete program execution
                }
        }
        printf("\n\n\t\t\tExited.\n\n\n");
        return 0;

}
