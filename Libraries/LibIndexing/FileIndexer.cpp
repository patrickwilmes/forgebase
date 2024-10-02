/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "FileIndexer.h"
#include <filesystem>

namespace fs = std::filesystem;

LibIndexing::FileIndexer::FileIndexer(const std::string &location) {
    if (!fs::exists(location) || !fs::is_directory(location)) {
        throw std::invalid_argument("Invalid directory! Location doesn't exist or is not a valid directory!");
    }
    this->_location = location;
}
