/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once

#include <memory>
#include <vector>
#include "IndexFile.h"

namespace LibStorage {
    class FileIndexStore {
    public:
        FileIndexStore() = default;
        virtual ~FileIndexStore();
        virtual void initialize();
        virtual void write_to_index(const std::shared_ptr<std::vector<IndexFile>>& files);
        virtual std::shared_ptr<std::vector<IndexFile>> search(const std::string & keyword);
    };

    std::shared_ptr<FileIndexStore> default_file_index_store();
}
