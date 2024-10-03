/*
 * Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include <string>
#include <vector>

namespace AK {
    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
}
