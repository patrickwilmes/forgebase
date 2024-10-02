/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once
#include <string>
#include <memory>
#include <vector>
#include <File.h>
#include <FileIndexer.h>

namespace LibRepository {
    class CodeRepository final : public LibIndexing::FileIndexer {
    public:
        explicit CodeRepository(const std::string & location);
        [[nodiscard]] std::shared_ptr<std::vector<AK::File>> get_files_to_index() const;
    };
}