/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once
#include "FileIndexStore.h"
#include <sqlite3.h>

namespace LibStorage {
    class SQLiteFileIndexStore final : public FileIndexStore {
    public:
        SQLiteFileIndexStore();

        ~SQLiteFileIndexStore() override;

        void write_to_index(const std::shared_ptr<std::vector<IndexFile> > &files) override;

        void initialize() override;

    private:
        void check_sqlite_error(int rc) const;

        sqlite3 *_db{};
    };
}
