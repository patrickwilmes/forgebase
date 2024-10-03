/*
 * Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "Strings.h"

std::vector<std::string> AK::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t pos = 0;
    size_t end = 0;
    while ((end = str.find(delimiter, pos)) != std::string::npos) {
        result.push_back(str.substr(pos, end - pos));
        pos = end + delimiter.length();
    }
    result.push_back(str.substr(pos, end));
    return result;
}
