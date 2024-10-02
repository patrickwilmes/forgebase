/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "SQLiteFileIndexStore.h"
#include <IO.h>
#include <string>
#include <iostream>

#define FILE_TABLE_SQL "Resources/DB/file_table.sql"
#define SQLITE_DB "sqlite.db"

LibStorage::SQLiteFileIndexStore::SQLiteFileIndexStore() {
    const int rc = sqlite3_open(SQLITE_DB, &_db);
    check_sqlite_error(rc);
}

LibStorage::SQLiteFileIndexStore::~SQLiteFileIndexStore() {
    if (_db) {
        sqlite3_close(_db);
    }
}

void LibStorage::SQLiteFileIndexStore::write_to_index(
    const std::shared_ptr<std::vector<IndexFile> > &files) {
    const std::string sql = "INSERT OR IGNORE INTO files (path, name, type) VALUES (?, ?, ?)";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(_db, sql.c_str(), -1, &stmt, nullptr);
    check_sqlite_error(rc);

    for (const auto &file: *files) {
        rc = sqlite3_bind_text(stmt, 1, file.get_path().c_str(), -1, SQLITE_TRANSIENT);
        check_sqlite_error(rc);
        rc = sqlite3_bind_text(stmt, 2, file.get_name().c_str(), -1, SQLITE_TRANSIENT);
        check_sqlite_error(rc);
        rc = sqlite3_bind_int(stmt, 3, file.get_type());
        check_sqlite_error(rc);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            check_sqlite_error(rc);
        }
        rc = sqlite3_reset(stmt);
        check_sqlite_error(rc);
    }

    rc = sqlite3_finalize(stmt);
    check_sqlite_error(rc);
}

void LibStorage::SQLiteFileIndexStore::initialize() {
    char *err_msg = nullptr;
    const auto content = AK::read_file(FILE_TABLE_SQL);
    if (const int rc = sqlite3_exec(_db, content.c_str(), nullptr, nullptr, &err_msg);
        rc != SQLITE_OK) {
        std::cerr << "SQLite error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    }
}

void LibStorage::SQLiteFileIndexStore::check_sqlite_error(const int rc) const {
    if (rc != SQLITE_OK && _db != nullptr) {
        std::cerr << "SQLite error: " << rc << std::endl;
    }
}
