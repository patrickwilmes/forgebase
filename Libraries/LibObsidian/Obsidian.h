/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <File.h>
#include <FileIndexer.h>

namespace LibObsidian {
    class Obsidian final : public LibIndexing::FileIndexer {
    public:
        explicit Obsidian(const std::string & vault_location);
        [[nodiscard]] std::shared_ptr<std::vector<AK::File>> get_files_to_index() const;
    };
}
