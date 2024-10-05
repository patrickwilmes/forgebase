/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once

#include "FileIndexStore.h"
#include <UserSpace.h>
#include <memory>
#include <pqxx/pqxx>

namespace LibStorage {
    class PostgresqlFileIndexStore : public FileIndexStore {
    public:
        PostgresqlFileIndexStore();

        ~PostgresqlFileIndexStore() override;

        void write_to_index(const std::shared_ptr<std::vector<IndexFile> > &files) override;

        std::shared_ptr<std::vector<IndexFile>> search(const std::string & keyword) override;

        void initialize() override;
    private:
        std::unique_ptr<AK::UserSpace> _user_space{};
        pqxx::connection _connection;
    };
}
