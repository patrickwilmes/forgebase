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
#include <Logging.h>

#define FILE_TABLE_SQL "Resources/DB/file_table.sql"
#define SQLITE_DB "sqlite.db"

LibStorage::SQLiteFileIndexStore::SQLiteFileIndexStore() {
    _user_space = std::make_unique<AK::UserSpace>();
    const int rc = sqlite3_open(SQLITE_DB, &_db);
    check_sqlite_error(rc);
}

LibStorage::SQLiteFileIndexStore::~SQLiteFileIndexStore() {
    if (_db) {
        sqlite3_close(_db);
    }
}

void LibStorage::SQLiteFileIndexStore::write_to_index(
    // TODO - check if table exists beforehand and quit if not
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

std::shared_ptr<std::vector<LibStorage::IndexFile>> LibStorage::SQLiteFileIndexStore::search(
    const std::string &keyword) {
    const std::string query = "SELECT * FROM files WHERE name LIKE ? COLLATE NOCASE";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(_db, query.c_str(), -1, &stmt, nullptr);
    check_sqlite_error(rc);
    std::string pattern = "%" + keyword + "%";
    rc = sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot bind parameter: " << sqlite3_errmsg(_db) << std::endl;
        sqlite3_finalize(stmt);
        return {nullptr};
    }

    auto results = std::make_shared<std::vector<IndexFile>>();
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* path = sqlite3_column_text(stmt, 1);
        const unsigned char* name = sqlite3_column_text(stmt, 2);
        int type = sqlite3_column_int(stmt, 3);

        results->emplace_back(std::string(reinterpret_cast<const char*>(path)), std::string(reinterpret_cast<const char*>(name)), static_cast<AK::FileType>(type));
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(_db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return results;
}

void LibStorage::SQLiteFileIndexStore::initialize() {
    char *err_msg = nullptr;
    std::string sql_file = _user_space->get_config_home() + FILE_TABLE_SQL;
    AK::debug("Using sql file at " + sql_file + " for db initialization");
    const auto content = AK::read_file(sql_file);
    if (const int rc = sqlite3_exec(_db, content.c_str(), nullptr, nullptr, &err_msg);
        rc != SQLITE_OK) {
        std::cerr << "SQLite error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    }
}

void LibStorage::SQLiteFileIndexStore::check_sqlite_error(const int rc) const {
    if (rc != SQLITE_OK && _db != nullptr) {
        AK::error(sqlite3_errmsg(_db));
    }
}
