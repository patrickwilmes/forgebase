/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "IO.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

std::string AK::read_file(const std::string &path) {
    if (!fs::exists(path)) {
        throw std::runtime_error("File not found!");
    }

    std::ifstream file_stream(path);
    if (!file_stream.is_open()) {
        throw std::runtime_error("Unable to open file!");
    }

    std::ostringstream string_stream;
    string_stream << file_stream.rdbuf();

    return string_stream.str();
}
