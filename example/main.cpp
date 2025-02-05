#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;
    char* errMsg = 0;
    int rc;

    // 打开数据库连接
    rc = sqlite3_open("library.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }
    else {
        std::cout << "Opened database successfully" << std::endl;
    }

    // 创建图书表
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS BOOKS("
        "ID INT PRIMARY KEY NOT NULL,"
        "TITLE TEXT NOT NULL,"
        "AUTHOR TEXT NOT NULL,"
        "YEAR INT NOT NULL);";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Table created successfully" << std::endl;
    }

    // 插入数据
    const char* insertSQL = "INSERT INTO BOOKS (ID, TITLE, AUTHOR, YEAR) "
        "VALUES (1, 'The Great Gatsby', 'F. Scott Fitzgerald', 1925);"
        "INSERT INTO BOOKS (ID, TITLE, AUTHOR, YEAR) "
        "VALUES (2, 'To Kill a Mockingbird', 'Harper Lee', 1960);";

    rc = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Records inserted successfully" << std::endl;
    }

    // 查询数据
    const char* selectSQL = "SELECT * FROM BOOKS;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* title = sqlite3_column_text(stmt, 1);
            const unsigned char* author = sqlite3_column_text(stmt, 2);
            int year = sqlite3_column_int(stmt, 3);

            std::cout << "ID: " << id << ", Title: " << title << ", Author: " << author << ", Year: " << year << std::endl;
        }
    }
    sqlite3_finalize(stmt);

    // 关闭数据库连接
    sqlite3_close(db);
    return 0;
}