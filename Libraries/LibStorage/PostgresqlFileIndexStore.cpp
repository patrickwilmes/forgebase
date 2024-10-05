/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "PostgresqlFileIndexStore.h"
#include "IO.h"
#include "IndexFile.h"
#include "Logging.h"
#include <exception>
#include <memory>
#include <stdexcept>

#define POSTGRES_INIT_SQL "Resources/DB/file_table.sql"

LibStorage::PostgresqlFileIndexStore::PostgresqlFileIndexStore(): _connection("host=127.0.0.1 port=5433 dbname=forgebase user=root password=123") {
    _user_space = std::make_unique<AK::UserSpace>();
    try {
        if (!_connection.is_open()) {
            AK::error("Failed to connect to database locally!");
            throw std::runtime_error("Failed to connect to database locally!");
        }
    } catch (const pqxx::broken_connection &e) {
        AK::error(e.what());
    } catch (const std::exception &e) {
        AK::error(e.what());
    }
}

LibStorage::PostgresqlFileIndexStore::~PostgresqlFileIndexStore() {
    if (_connection.is_open()) {
        _connection.close();
    }
}

void LibStorage::PostgresqlFileIndexStore::write_to_index(const std::shared_ptr<std::vector<IndexFile> > &files) {
    if (_connection.is_open()) {
        _connection.prepare("insert_file", "INSERT INTO files (path, type, name) values ($1, $2, $3);");
        pqxx::work txn(_connection);
        for (auto file : *files) {
            txn.exec_prepared("insert_file", file.get_path(), 0, file.get_name());
        }
        txn.commit();
    } else {
        AK::warn("Can't insert into database. Connection is closed!");
    }
}

std::shared_ptr<std::vector<LibStorage::IndexFile>> LibStorage::PostgresqlFileIndexStore::search(const std::string & keyword) {
    return {nullptr};
}

void LibStorage::PostgresqlFileIndexStore::initialize() {
    auto init_sql_file = _user_space->get_config_home() + POSTGRES_INIT_SQL;
    auto contents = AK::read_file(init_sql_file);
    pqxx::work txn(_connection);
    txn.exec(contents);
    txn.commit();
}
