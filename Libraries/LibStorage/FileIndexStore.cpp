/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "FileIndexStore.h"

#include "SQLiteFileIndexStore.h"

LibStorage::FileIndexStore::~FileIndexStore() = default;

void LibStorage::FileIndexStore::initialize() {
}

void LibStorage::FileIndexStore::write_to_index(
    const std::shared_ptr<std::vector<IndexFile>> &files) {
}

std::shared_ptr<LibStorage::FileIndexStore> LibStorage::default_file_index_store() {
    return std::make_shared<SQLiteFileIndexStore>();
}
