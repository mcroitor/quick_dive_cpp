#include "sqlite3.h"

int main() {
    sqlite3 * db;

    sqlite3_open("sample.db", &db);

    sqlite3_stmt * stmt;

// create table
    sqlite3_prepare_v2(db, "CREATE TABLE sample (id INTEGER, name TEXT)", 255, &stmt, nullptr);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

// insert data
    sqlite3_prepare_v2(db, "INSERT INTO sample VALUES (10, 'Gicu')", 255, &stmt, nullptr);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sqlite3_close(db);
    return 0;
}