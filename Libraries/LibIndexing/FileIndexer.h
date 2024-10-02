/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once

#include <string>

namespace LibIndexing {
    class FileIndexer {
    protected:
        explicit FileIndexer(const std::string& location);
        std::string _location;
    };
}