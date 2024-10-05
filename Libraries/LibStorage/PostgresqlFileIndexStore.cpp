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
#include "UserSpace.h"
#include <exception>
#include <memory>
#include <stdexcept>

#define POSTGRES_INIT_SQL "Resources/DB/file_table.sql"

static std::string build_connection_string() {
    AK::UserSpace user_space;
    auto host = user_space.get_property("db_host");
    auto port = user_space.get_property("db_port");
    auto user = user_space.get_property("db_user");
    auto password = user_space.get_property("db_password");
    auto name = user_space.get_property("db_name");
    AK::debug("DB Host: " + host);
    AK::debug("DB Port: " + port);
    AK::debug("DB User: " + user);
    AK::debug("DB Password: " + password);
    AK::debug("DB Name: " + name);
    return "host=" + host + " port=" + port + " dbname=" + name + " user=" + user + " password=" + password;
}

LibStorage::PostgresqlFileIndexStore::PostgresqlFileIndexStore(): _connection(build_connection_string()) {
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
        _connection.prepare("insert_file", 
                "INSERT INTO files (path, type, name) values ($1, $2, $3)"
                "ON CONFLICT (path) "
                "DO UPDATE SET type=EXCLUDED.type, name=EXCLUDED.name;"
            );
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
